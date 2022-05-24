use std::cmp::Ordering;
use std::option::Option;

const NUM_RESOURCES: usize = 19;
const EPSILON: f64 = 0.00001;

#[repr(C)]
#[derive(Debug)]
struct ResourceValue {
    value: f64,
    capacity: f64,
}

#[repr(C)]
struct ResourceItem {
    restype: i32,
    val: f64,
}

#[repr(C)]
#[derive(Debug)]
struct Resources {
    values: [ResourceValue; NUM_RESOURCES]
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

const RES_NAMES: [&str; NUM_RESOURCES] = [
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
fn res_is_zero(res: *const Resources) -> bool { unsafe { (&*res).is_zero() } }

#[no_mangle]
fn res_eq(a: *const Resources, b: *const Resources) -> bool { unsafe { (&*a) == (&*b) } }

#[no_mangle]
fn res_ge(a: *const Resources, b: *const Resources) -> bool { unsafe { (&*a) >= (&*b) } }

#[no_mangle]
fn res_ne(a: *const Resources, b: *const Resources) -> bool { unsafe { (&*a) != (&*b) } }

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

