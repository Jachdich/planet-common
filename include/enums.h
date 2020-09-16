#ifndef __ENUMS_H
#define __ENUMS_H
#include <string>

enum class ErrorCode {
	OK = 0,
	MALFORMED_JSON = -1,
	INVALID_REQUEST = -2,
	OUT_OF_BOUNDS = -3,
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

enum class TaskType {
	FELL_TREE,
	GATHER_MINERALS,
	CLEAR,
};

inline std::string getTaskTypeName(TaskType t) {
	switch (t) {
		case TaskType::FELL_TREE: return "Fell tree";
		case TaskType::GATHER_MINERALS: return "Mine minerals";
		case TaskType::CLEAR: return "Clear everything";
	}
	return "INVALID VALUE";
}

#endif
