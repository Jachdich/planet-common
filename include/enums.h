#ifndef __ENUMS_H
#define __ENUMS_H
#include <string>
#include "common/stats.h"

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
	GATHER_MINERALS,
	CLEAR,
	PLANT_TREE,
	BUILD_HOUSE,
	BUILD_FARM,
	BUILD_GREENHOUSE,
	BUILD_WATERPUMP,
	BUILD_MINE,
	BUILD_BLASTFURNACE,
	BUILD_SMELTERY,
	BUILD_ALUMINIUM_FORGE,
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
	SMELTERY,
	ALUMINIUM_FORGE,
	WAREHOUSE,
	ROAD_NS,
	ROAD_EW,
	ROAD_NE,
	ROAD_NW,
	ROAD_SE,
	ROAD_SW,
    ROAD_NESW,
};

struct TaskTypeInfo {
    std::vector<TileType> expectedTileTypes;
    Stats cost;
    Stats gains;
    TileType tileType;
};

std::unordered_map<TaskType, TaskTypeInfo> taskTypeInfos;

inline void registerTaskTypeInfo() {
    taskTypeInfos[TaskType::FELL_TREE] = TaskTypeInfo{{TREE, FOREST, PINE, PINEFOREST}, }
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

inline int getTimeForTask(TaskType t) {
	switch (t) {
		case TaskType::FELL_TREE: return 6;
		case TaskType::GATHER_MINERALS: return 12;
		case TaskType::CLEAR: return 3;
		case TaskType::PLANT_TREE: return 5;
		case TaskType::BUILD_HOUSE: return 11; //Debug values
		case TaskType::BUILD_FARM: return 12;
		case TaskType::BUILD_GREENHOUSE: return 13;
		case TaskType::BUILD_WATERPUMP: return 14;
		case TaskType::BUILD_MINE: return 15;
		case TaskType::BUILD_BLASTFURNACE: return 16;
		case TaskType::BUILD_SMELTERY: return 17;
		case TaskType::BUILD_ALUMINIUM_FORGE: return 18;
		case TaskType::BUILD_WAREHOUSE: return 19;
		case TaskType::BUILD_ROAD: return 20;
	}
	return -1;
}

inline std::string getTaskTypeName(TaskType t) {
	switch (t) {
		case TaskType::FELL_TREE: return "Fell tree";
		case TaskType::GATHER_MINERALS: return "Mine minerals";
		case TaskType::CLEAR: return "Clear everything";
		case TaskType::PLANT_TREE: return "Plant a tree";
		case TaskType::BUILD_HOUSE: return "Build house";
		case TaskType::BUILD_FARM: return "Build farm";

		case TaskType::BUILD_WATERPUMP: return "Build water pump";
		default: return "INVALID VALUE";
	}
}

#endif
