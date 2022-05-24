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
    "Electricity",
    "Research Points",
};

const char *res_id_to_json_key(int a) {
    return res_names[a];
}

int res_json_key_to_id(const char *key) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (strcmp(res_names[i], key) == 0) return i;
    }
    return -1;
}

struct Resources res_init() {
    struct Resources res;
    for (int i = 0; i < NUM_RESOURCES; i++) {
        res.values[i] = (struct ResourceValue){0, 0};
    }
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
        ptr += sprintf(ptr, "%s: %lf/%lf, ", res_names[i], res->values[i].value, res->values[i].capacity);
    }
    return ret;
}

struct Resources res_clone(struct Resources *res) {
    struct Resources ret = res_init();
    memcpy(ret.values, res->values, NUM_RESOURCES * sizeof(*res->values));
    return ret;
}
