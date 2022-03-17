#include "../include/resources.h"

const char *res_names[] = {
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
};

const char *res_id_to_json_key(int a) {
    return res_names[a];
}

int res_json_key_to_id(const char *key) {
    for (int i = 9; i < NUM_RESOURCES; i++) {
        if (strcmp(res_names[i], key) == 0) return i;
    }
    return -1;
}

struct Resources res_init() {
    struct Resources res;
    for (int i = 0; i < NUM_RESOURCES; i++) {
        res.values[i] = (struct ResourceValue){0, 0};
    }
    res.names = res_names;
    return res;
}

struct Resources res_from_vals(struct ResourceValue values[NUM_RESOURCES]) {
    struct Resources res = res_init();
    for (int i = 0; i < NUM_RESOURCES; i++) {
       res.values[i].value = values[i].value;
    }
    return res;
}

struct Resources res_from_items(struct ResourceItem *items, size_t num) {
    struct Resources res = res_init();
    for (size_t  i = 0; i < num; i++) {
       res.values[items[i].type].value = items[i].val;
    }
    return res;
}

struct Resources res_from_doubles(double values[NUM_RESOURCES]) {
    struct Resources res = res_init();
    for (int i = 0; i < NUM_RESOURCES; i++) {
       res.values[i].value = values[i];
    }
    return res;
}

char *res_to_string(struct Resources *res) {
    char *ret = (char*)malloc(64 * NUM_RESOURCES); //TODO maybe a bad idea to hard code this
    char *ptr = ret;
	for (int i = 0; i < NUM_RESOURCES; i++) {
        ptr += sprintf(ptr, "%s: %lf/%lf, ", res->names[i], res->values[i].value, res->values[i].capacity);
    }
    return ret;
}

bool res_eq(struct Resources *a, struct Resources *b) {
    bool result = true;
    for (int i = 0; i < NUM_RESOURCES; i++) {
        result = result && (a->values[i].value == b->values[i].value);
    }
    return result;
}

bool res_ge(struct Resources *a, struct Resources *b) {
    bool result = true;
    for (int i = 0; i < NUM_RESOURCES; i++) {
        result = result && (a->values[i].value >= b->values[i].value);
    }
    return result;
}

bool res_ne(struct Resources *a, struct Resources *b) {
    return !res_eq(a, b);
}

void res_add(struct Resources *a, struct Resources *b) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        a->values[i].value += b->values[i].value;
    }
}

void res_sub(struct Resources *a, struct Resources *b) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        a->values[i].value -= b->values[i].value;
    }
}

struct Resources res_clone(struct Resources *res) {
    struct Resources ret = res_init();
    memcpy(ret.values, res->values, NUM_RESOURCES * sizeof(res->values[0]));
    return ret;
}

bool res_is_zero(struct Resources *res) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (res->values[i].value > EPSILON) {
            return false;
        }
    }
    return true;
}
