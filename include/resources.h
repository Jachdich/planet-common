#ifndef __RESOURCES_H
#define __RESOURCES_H
#include <jsoncpp/json/json.h>
#include <string>
#include <unordered_map>
#include <iostream>
#define EPSILON 0.00001
#define NUM_RESOURCES 17

extern "C" {
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct ResourceValue {
    double value;
    double capacity;
};


enum {
    RES_WOOD = 0,
    RES_STONE,
    RES_FOOD,
    RES_WATER,
    RES_PEOPLE,
    RES_PEOPLE_IDLE,
    RES_IRON_ORE,
    RES_COPPER_ORE,
    RES_ALUMINIUM_ORE,
    RES_IRON,
    RES_COPPER,
    RES_ALUMINIUM,
    RES_SILICON,
    RES_OIL,
    RES_PLASTIC,
    RES_GLASS,
    RES_SAND,
};

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

struct Resources {
	struct ResourceValue values[NUM_RESOURCES];
	const char **names;
};

inline struct Resources res_init() {
    struct Resources res;
    for (int i = 0; i < NUM_RESOURCES; i++) {
        res.values[i] = (ResourceValue){0, 0};
    }
    res.names = res_names;
    return res;
}

inline struct Resources res_from_vals(struct ResourceValue values[NUM_RESOURCES]) {
    struct Resources res = res_init();
    for (int i = 0; i < NUM_RESOURCES; i++) {
       res.values[i].value = values[i].value;
    }
    return res;
}

inline struct Resources res_from_doubles(double values[NUM_RESOURCES]) {
    struct Resources res = res_init();
    for (int i = 0; i < NUM_RESOURCES; i++) {
       res.values[i].value = values[i];
    }
    return res;
}

inline char *res_to_string(struct Resources *res) {
    char *ret = (char*)malloc(64 * NUM_RESOURCES); //TODO maybe a bad idea to hard code this
    char *ptr = ret;
	for (int i = 0; i < NUM_RESOURCES; i++) {
        ptr += sprintf(ptr, "%s: %lf/%lf, ", res->names[i], res->values[i].value, res->values[i].capacity);
    }
    return ret;
}

inline bool res_eq(struct Resources *a, struct Resources *b)  {
    bool result;
    for (int i = 0; i < NUM_RESOURCES; i++) {
        result = result && (a->values[i].value == b->values[i].value);
    }
    return result;
}

inline bool res_ge(struct Resources *a, struct Resources *b)  {
    bool result;
    for (int i = 0; i < NUM_RESOURCES; i++) {
        result = result && (a->values[i].value >= b->values[i].value);
    }
    return result;
}

inline bool res_ne(struct Resources *a, struct Resources *b)  {
    return !res_eq(a, b);
}

inline void res_add(struct Resources *a, struct Resources *b) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        a->values[i].value += b->values[i].value;
    }
}

inline void res_sub(struct Resources *a, struct Resources *b) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        a->values[i].value -= b->values[i].value;
    }
}

inline struct Resources res_clone(struct Resources *res) {
    struct Resources ret = res_init();
    memcpy(ret.values, res->values, NUM_RESOURCES * sizeof(res->values[0]));
    return ret;
}

inline bool res_is_zero(struct Resources *res) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (res->values[i].value > EPSILON) {
            return false;
        }
    }
    return true;
}

}

inline struct Resources res_from_json(Json::Value root) {
    struct Resources n = res_init();
    for (int i = 0; i < NUM_RESOURCES; i++) {
        std::string key(res_id_to_json_key(i));
	    n.values[i].value = root[key]["value"].asDouble();
	    n.values[i].capacity = root[key]["capacity"].asDouble();
	}
    return n;
}

inline void res_to_json_in_place(struct Resources *res, Json::Value& root) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        std::string key(res_id_to_json_key(i));
        root[key]["value"]    = res->values[i].value;
        root[key]["capacity"] = res->values[i].capacity;
    }
}

inline Json::Value res_to_json(struct Resources *res) {
    Json::Value root;
    res_to_json_in_place(res, root);
    return root;
}

#endif
