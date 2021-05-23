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
	VOID,
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
