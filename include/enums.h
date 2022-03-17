#ifndef __ENUMS_H
#define __ENUMS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
    enum ErrorType type;
    char *message;
};

enum TaskType {
    TASK_NONE = 0,
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
    TASK_INVALID, //MUST BE LAST!
};

enum TileType {
	TILE_AIR = 0,
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

struct ErrorCode err_new(const enum ErrorType type, const char *message);
struct TileMinerals getTileMinerals(uint32_t colour);
bool isTree(enum TileType type);
bool isMineral(enum TileType type);
bool isClearable(enum TileType type);
const char *getTileTypeName(enum TileType t);
const char *getTaskTypeName(enum TaskType t);

#ifdef __cplusplus
}
#endif

#endif
