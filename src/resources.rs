use serde::de::Error;
use serde::de::SeqAccess;
use serde::de::Visitor;
use serde::ser::SerializeTuple;
use serde::Deserialize;
use serde::Deserializer;
use serde::{Serialize, Serializer};
use std::cmp::Ordering;
use std::marker::PhantomData;
use std::option::Option;

const NUM_RESOURCES: usize = 19;
const EPSILON: f64 = 0.00001;

#[repr(C)]
#[derive(Debug, Clone, Copy, Default)]
pub struct ResourceValue {
    pub value: f64,
    pub capacity: f64,
}

#[repr(C)]
pub struct ResourceItem {
    pub restype: i32,
    pub val: f64,
}

#[repr(C)]
#[derive(Debug)]
pub struct Resources {
    pub values: [ResourceValue; NUM_RESOURCES],
}

impl Resources {
    pub fn new() -> Self {
        Self {
            values: [ResourceValue {
                value: 0.0,
                capacity: 0.0,
            }; NUM_RESOURCES],
        }
    }
}

impl Serialize for ResourceValue {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        let mut state = serializer.serialize_tuple(2)?;
        state.serialize_element(&self.value)?;
        state.serialize_element(&self.capacity)?;
        state.end()
    }
}

impl Serialize for Resources {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        let mut state = serializer.serialize_tuple(NUM_RESOURCES * 2)?;
        for i in 0..NUM_RESOURCES {
            state.serialize_element(&self.values[i])?;
        }
        state.end()
    }
}

struct ArrayVisitor<A> {
    marker: PhantomData<A>,
}

impl<A> ArrayVisitor<A> {
    fn new() -> Self {
        ArrayVisitor {
            marker: PhantomData,
        }
    }
}

impl<'de, T, const N: usize> Visitor<'de> for ArrayVisitor<[T; N]>
where
    T: Deserialize<'de> + Copy + Default,
{
    type Value = [T; N];

    fn expecting(&self, formatter: &mut std::fmt::Formatter) -> std::fmt::Result {
        formatter.write_str(&format!("an array of length {}", N))
    }

    #[inline]
    fn visit_seq<A>(self, mut seq: A) -> Result<Self::Value, A::Error>
    where
        A: SeqAccess<'de>,
    {
        let mut result: [T; N] = [Default::default(); N];
        for i in 0..N {
            result[i] = match seq.next_element()? {
                Some(val) => val,
                None => return Err(Error::invalid_length(i, &self)),
            };
        }
        Ok(result)
    }
}

impl<'de> Deserialize<'de> for ResourceValue {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: Deserializer<'de>,
    {
        let arr = deserializer.deserialize_tuple(2, ArrayVisitor::<[f64; 2]>::new())?;
        Ok(ResourceValue {
            value: arr[0],
            capacity: arr[1],
        })
    }
}

impl<'de> Deserialize<'de> for Resources {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: Deserializer<'de>,
    {
        let arr = deserializer.deserialize_tuple(
            NUM_RESOURCES,
            ArrayVisitor::<[ResourceValue; NUM_RESOURCES]>::new(),
        )?;
        Ok(Resources { values: arr })
    }
}

/*enum ResourceType {
    Wood,
    Stone,
    Food,
    Water,
    People,
    PeopleIdle,
    IronOre,
}*/

pub const RES_NAMES: [&str; NUM_RESOURCES] = [
    "Wood",
    "Stone",
    "Food",
    "Water",
    "People",
    "Idle People",
    "Iron Ore",
    "Copper Ore",
    "Aluminium Ore",
    "Iron",
    "Copper",
    "Aluminium",
    "Silicon",
    "Oil",
    "Plastic",
    "Glass",
    "Sand",
    "Electricity",
    "Research Points",
];

impl std::ops::AddAssign for Resources {
    fn add_assign(&mut self, other: Resources) {
        for i in 0..NUM_RESOURCES {
            self.values[i].value += other.values[i].value;
        }
    }
}

impl<'a, 'b> std::ops::AddAssign<&'b Resources> for &'a mut Resources {
    fn add_assign(&mut self, other: &'b Resources) {
        for i in 0..NUM_RESOURCES {
            self.values[i].value += other.values[i].value;
        }
    }
}

impl<'a, 'b> std::ops::SubAssign<&'b Resources> for &'a mut Resources {
    fn sub_assign(&mut self, other: &'b Resources) {
        for i in 0..NUM_RESOURCES {
            self.values[i].value -= other.values[i].value;
        }
    }
}

impl std::cmp::PartialEq for Resources {
    fn eq(&self, other: &Self) -> bool {
        for i in 0..NUM_RESOURCES {
            if self.values[i].value - other.values[i].value > EPSILON {
                return false;
            }
        }
        true
    }
}

impl PartialOrd for Resources {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        if self == other {
            Some(Ordering::Equal)
        } else {
            let mut less = true;
            let mut more = true;
            for i in 0..NUM_RESOURCES {
                less = less && (self.values[i].value < other.values[i].value);
                more = more && (self.values[i].value > other.values[i].value);
            }
            if less && more {
                None
            } else if less {
                Some(Ordering::Less)
            } else if more {
                Some(Ordering::Greater)
            } else {
                None
            }
        }
    }

    fn ge(&self, other: &Self) -> bool {
        for i in 0..NUM_RESOURCES {
            if self.values[i].value < other.values[i].value {
                return false;
            }
        }
        true
    }
}

impl Resources {
    fn is_zero(&self) -> bool {
        for i in 0..NUM_RESOURCES {
            if self.values[i].value > EPSILON {
                return false;
            }
        }
        true
    }
}

//C interface -----------------------------------------------
#[no_mangle]
fn res_is_zero(res: *const Resources) -> bool {
    unsafe { (&*res).is_zero() }
}

#[no_mangle]
fn res_eq(a: *const Resources, b: *const Resources) -> bool {
    unsafe { (&*a) == (&*b) }
}

#[no_mangle]
fn res_ge(a: *const Resources, b: *const Resources) -> bool {
    unsafe { (&*a) >= (&*b) }
}

#[no_mangle]
fn res_ne(a: *const Resources, b: *const Resources) -> bool {
    unsafe { (&*a) != (&*b) }
}

#[no_mangle]
fn res_add(a: *mut Resources, b: *const Resources) {
    unsafe {
        let mut a = &mut *a;
        a += &*b;
    }
}

#[no_mangle]
fn res_sub(a: *mut Resources, b: *const Resources) {
    unsafe {
        let mut a = &mut *a;
        a -= &*b;
    }
}
