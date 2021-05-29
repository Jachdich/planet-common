#ifndef __ENUMS_H
#define __ENUMS_H
#include <string>
#include "common/resources.h"
#include <unordered_map>

enum class ErrorCode {
	OK = 0,
	MALFORMED_JSON = -1,
	INVALID_REQUEST = -2,
	OUT_OF_BOUNDS = -3,
	NO_PEOPLE_AVAILABLE = -4,
    INSUFFICIENT_RESOURCES = -5,
    TASK_ALREADY_STARTED = -6,
    TASK_ON_WRONG_TILE = -7,
};

enum class TaskType {
	FELL_TREE,
	MINE_ROCK,
	CLEAR,
	PLANT_TREE,
	BUILD_HOUSE,
	BUILD_FARM,
	BUILD_GREENHOUSE,
	BUILD_WATERPUMP,
	BUILD_MINE,
	BUILD_BLASTFURNACE,
	BUILD_WAREHOUSE,
	BUILD_ROAD,
};

enum class TileType {
	AIR,
	GRASS,
	BUSH,
	TREE,
	PINE,
	WATER,
	ROCK,
	HOUSE,
	PINEFOREST,
	FOREST,
	TONK,
	FARM,
	GREENHOUSE,
	WATERPUMP,
	MINE,
	BLASTFURNACE,
	WAREHOUSE,
};

struct TileMinerals {
    double sand;
    double copper;
    double iron;
    double aluminium;
};

inline TileMinerals getTileMinerals(uint32_t colour) {
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
    
    return {sand, copper, iron, aluminium};
}

inline bool isTree(TileType type) {
	switch (type) {
		case TileType::TREE:
		case TileType::PINE:
		case TileType::PINEFOREST:
		case TileType::FOREST:
		return true;
		default: return false;
	}
}

inline bool isMineral(TileType type) {
	switch (type) {
		case TileType::ROCK:
		return true;
		default:
		return false;
	}
}

inline bool isClearable(TileType type) {
	switch (type) {
		case TileType::BUSH:
		return true;
		default:
		return false;
	}
}

inline std::string getTileTypeName(TileType t) {
    switch (t) {
        case TileType::AIR : return "AIR";
        case TileType::GRASS : return "GRASS";
        case TileType::BUSH : return "BUSH";
        case TileType::TREE : return "TREE";
        case TileType::PINE : return "PINE";
        case TileType::WATER : return "WATER";
        case TileType::ROCK : return "ROCK";
        case TileType::HOUSE : return "HOUSE";
        case TileType::PINEFOREST : return "PINEFOREST";
        case TileType::FOREST : return "FOREST";
        case TileType::TONK : return "TONK";
        case TileType::FARM : return "FARM";
        case TileType::GREENHOUSE : return "GREENHOUSE";
        case TileType::WATERPUMP : return "WATERPUMP";
        case TileType::MINE : return "MINE";
        case TileType::BLASTFURNACE : return "BLASTFURNACE";
        case TileType::WAREHOUSE : return "WAREHOUSE";
        default: return "INVALID_NAME";
    }
}

inline std::string getTaskTypeName(TaskType t) {
	switch (t) {
		case TaskType::FELL_TREE: return "Fell tree";
		case TaskType::MINE_ROCK: return "Mine minerals";
		case TaskType::CLEAR: return "Clear everything";
		case TaskType::PLANT_TREE: return "Plant a tree";
		case TaskType::BUILD_HOUSE: return "Build house";
		case TaskType::BUILD_FARM: return "Build farm";
		case TaskType::BUILD_GREENHOUSE: return "Build greenhouse";
		case TaskType::BUILD_WATERPUMP: return "Build water pump";
		default: return "INVALID VALUE";
	}
}

#endif
