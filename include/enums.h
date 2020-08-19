#ifndef __ENUMS_H
#define __ENUMS_H

enum class ErrorCode {
	OK = 0,
	MALFORMED_JSON = -1,
	INVALID_REQUEST = -2,
	OUT_OF_BOUNDS = -3,
};

enum class TileType {
	VOID,
	GRASS,
	TREE,
	WATER,
	ROCK,
	HOUSE,
};

#endif
