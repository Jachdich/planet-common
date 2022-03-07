#ifndef __ENUMS_H
#define __ENUMS_H

extern "C" {
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

enum ErrorType {
    ERR_OK = 0,
    ERR_MALFORMED_JSON = -1,
    ERR_INVALID_REQUEST = -2,
    ERR_OUT_OF_BOUNDS = -3,
    ERR_INVALID_ACTION = -4,
    ERR_INVALID_CREDENTIALS = -5,
    ERR_NOT_AUTHENTICATED = -6,
    ERR_NOT_AUTHORISED = -7,
};

struct ErrorCode {
    char *message;
    enum ErrorType type;
};

enum TaskType {
    TASK_NONE,
    TASK_FELL_TREE,
    TASK_MINE_ROCK,
    TASK_CLEAR,
    TASK_PLANT_TREE,
    TASK_BUILD_HOUSE,
    TASK_BUILD_FARM,
    TASK_BUILD_GREENHOUSE,
    TASK_BUILD_WATERPUMP,
    TASK_BUILD_MINE,
    TASK_BUILD_BLASTFURNACE,
    TASK_BUILD_WAREHOUSE,
    TASK_BUILD_FORESTRY,
    TASK_BUILD_CAPSULE,
    TASK_BUILD_ROAD,
    TASK_BUILD_PIPE,
    TASK_BUILD_CABLE,
    TASK_BUILD_POWERSTATION,
};

enum TileType {
	TILE_AIR,
	TILE_GRASS,
	TILE_BUSH,
	TILE_TREE,
	TILE_PINE,
	TILE_WATER,
	TILE_ROCK,
	TILE_HOUSE,
	TILE_PINEFOREST,
	TILE_FOREST,
	TILE_TONK,
	TILE_FARM,
	TILE_GREENHOUSE,
	TILE_WATERPUMP,
	TILE_MINE,
	TILE_BLASTFURNACE,
	TILE_WAREHOUSE,
	TILE_FORESTRY,
	TILE_CAPSULE,
	TILE_ROAD,
	TILE_PIPE,
	TILE_CABLE,
	TILE_POWERSTATION,
};

struct TileMinerals {
    double sand;
    double copper;
    double iron;
    double aluminium;
};

inline struct TileMinerals getTileMinerals(uint32_t colour) {
    uint8_t r = (colour >> 16) & 0xFF;
    uint8_t g = (colour >>  8) & 0xFF;
    uint8_t b = (colour >>  0) & 0xFF;
    
    double iron = r / 200.0 - g / 512.0 - b / 512.0;
    if (iron < 0) iron = 0;
    if (iron > 1) iron = 1;

    double copper = (1 - abs(g - 192) / 256.0) - abs(r - 64) / 256.0 - abs(b - 96) / 512.0;
    if (r > g) copper -= r / 128.0;
    if (copper < 0) copper = 0;
    if (copper > 1) copper = 1;

    double sand = (1 - abs(r - g) / 128) - abs(b - 96) / 256.0 - (512 - (r + g)) / 256.0;
    if (sand < 0) sand = 0;
    if (sand > 1) sand = 1;

    double aluminium = b / 200.0 - r / 512.0 - g / 512.0;
    if (aluminium < 0) aluminium = 0;
    if (aluminium > 1) aluminium = 1;
    
    return (struct TileMinerals){sand, copper, iron, aluminium};
}

inline bool isTree(enum TileType type) {
	switch (type) {
		case TILE_TREE:
		case TILE_PINE:
		case TILE_PINEFOREST:
		case TILE_FOREST:
		return true;
		default: return false;
	}
}

inline bool isMineral(enum TileType type) {
	switch (type) {
		case TILE_ROCK:
		return true;
		default:
		return false;
	}
}

inline bool isClearable(enum TileType type) {
	switch (type) {
		case TILE_BUSH:
		return true;
		default:
		return false;
	}
}

inline const char *getTileTypeName(enum TileType t) {
    switch (t) {
        case TILE_AIR : return "AIR";
        case TILE_GRASS : return "GRASS";
        case TILE_BUSH : return "BUSH";
        case TILE_TREE : return "TREE";
        case TILE_PINE : return "PINE";
        case TILE_WATER : return "WATER";
        case TILE_ROCK : return "ROCK";
        case TILE_HOUSE : return "HOUSE";
        case TILE_PINEFOREST : return "PINEFOREST";
        case TILE_FOREST : return "FOREST";
        case TILE_TONK : return "TONK";
        case TILE_FARM : return "FARM";
        case TILE_GREENHOUSE : return "GREENHOUSE";
        case TILE_WATERPUMP : return "WATERPUMP";
        case TILE_MINE : return "MINE";
        case TILE_BLASTFURNACE : return "BLASTFURNACE";
        case TILE_WAREHOUSE : return "WAREHOUSE";
        case TILE_FORESTRY : return "FORESTRY";
        case TILE_CAPSULE : return "CAPSULE";
        case TILE_ROAD : return "ROAD";
        case TILE_PIPE : return "PIPE";
        case TILE_CABLE : return "CABLE";
        case TILE_POWERSTATION : return "POWERSTATION";
        default: return "INVALID_NAME";
    }
}

inline const char *getTaskTypeName(enum TaskType t) {
	switch (t) {
		case TASK_FELL_TREE: return "Fell tree";
		case TASK_MINE_ROCK: return "Mine minerals";
		case TASK_CLEAR: return "Clear everything";
		case TASK_PLANT_TREE: return "Plant a tree";
		case TASK_BUILD_HOUSE: return "Build house";
		case TASK_BUILD_FARM: return "Build farm";
		case TASK_BUILD_GREENHOUSE: return "Build greenhouse";
		case TASK_BUILD_WATERPUMP: return "Build water pump";
		case TASK_BUILD_MINE: return "Build mine";
		case TASK_BUILD_BLASTFURNACE: return "Build blastfurnace";
		case TASK_BUILD_WAREHOUSE: return "Build warehouse";
		case TASK_BUILD_FORESTRY: return "Build forestry";
		case TASK_BUILD_CAPSULE: return "Build capsule";
		case TASK_BUILD_ROAD: return "Build road";
		case TASK_BUILD_PIPE: return "Build pipe";
		case TASK_BUILD_CABLE: return "Build cable";
		case TASK_BUILD_POWERSTATION: return "Build powerstation";
		default: return "INVALID VALUE";
	}
}
}
#endif
