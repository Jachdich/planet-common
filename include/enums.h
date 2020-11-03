#ifndef __ENUMS_H
#define __ENUMS_H
#include <string>

enum class ErrorCode {
	OK = 0,
	MALFORMED_JSON = -1,
	INVALID_REQUEST = -2,
	OUT_OF_BOUNDS = -3,
	NO_PEOPLE_AVAILABLE = -4
    INSUFFICIENT_RESOURCES = -5;
};

enum class TaskType {
	FELL_TREE,
	GATHER_MINERALS,
	CLEAR,
	PLANT_TREE,
	BUILD_HOUSE,
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
	PINEFOREST
};

inline bool isTree(TileType type) {
	switch (type) {
		case TileType::TREE:
		case TileType::PINE:
		case TileType::PINEFOREST:
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
	}
	return -1;
}

inline std::string getTaskTypeName(TaskType t) {
	switch (t) {
		case TaskType::FELL_TREE: return "Fell tree";
		case TaskType::GATHER_MINERALS: return "Mine minerals";
		case TaskType::CLEAR: return "Clear everything";
		case TaskType::PLANT_TREE: return "Plant a tree";
	}
	return "INVALID VALUE";
}

#endif
