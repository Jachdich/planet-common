#ifndef __RESOURCES_H
#define __RESOURCES_H
#define EPSILON 0.00001

#ifdef __cplusplus
#include <jsoncpp/json/json.h>
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

struct ResourceValue {
    double value;
    double capacity;
};

//when a type is needed
struct ResourceItem {
    int type;
    double val;
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
    NUM_RESOURCES
};


struct Resources {
	struct ResourceValue values[NUM_RESOURCES];
};


extern const char *res_names[];

const char *res_id_to_json_key(int a);
int res_json_key_to_id(const char *key);
struct Resources res_init();
struct Resources res_from_vals(struct ResourceValue values[NUM_RESOURCES]);
struct Resources res_from_items(struct ResourceItem *items, size_t num);
struct Resources res_from_doubles(double values[NUM_RESOURCES]);
char *res_to_string(struct Resources *res);
bool res_eq(struct Resources *a, struct Resources *b);
bool res_ge(struct Resources *a, struct Resources *b);
bool res_ne(struct Resources *a, struct Resources *b);
void res_add(struct Resources *a, struct Resources *b);
void res_sub(struct Resources *a, struct Resources *b);
struct Resources res_clone(struct Resources *res);
bool res_is_zero(struct Resources *res);

#ifdef __cplusplus
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

inline void res_to_json_in_place(const struct Resources *res, Json::Value& root) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        std::string key(res_id_to_json_key(i));
        root[key]["value"]    = res->values[i].value;
        root[key]["capacity"] = res->values[i].capacity;
    }
}

inline Json::Value res_to_json(const struct Resources *res) {
    Json::Value root;
    res_to_json_in_place(res, root);
    return root;
}
#endif //__cplusplus
#endif
