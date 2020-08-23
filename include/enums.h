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
};

inline bool isTree(TileType type) {
	switch (type) {
		case TileType::VOID:
		case TileType::GRASS:
	 	case TileType::BUSH:
		case TileType::WATER:
		case TileType::ROCK:
		case TileType::HOUSE:
		return false;
		case TileType::TREE:
		case TileType::PINE:
		return true;
	}
}

inline bool isMineral(TileType type) {
	switch (type) {
		case TileType::VOID:
		case TileType::GRASS:
		case TileType::BUSH:
		case TileType::WATER:
		case TileType::TREE:
		case TileType::HOUSE:
		case TileType::PINE:
		return false;
		case TileType::ROCK:
		return true;
	}
}

inline bool isClearable(TileType type) {
	switch (type) {
		case TileType::VOID:
		case TileType::GRASS:
		case TileType::ROCK:
		case TileType::WATER:
		case TileType::TREE:
		case TileType::HOUSE:
		case TileType::PINE:
		return false;
		case TileType::BUSH:
		return true;
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
