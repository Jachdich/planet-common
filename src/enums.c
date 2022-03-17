#include "../include/enums.h"

struct ErrorCode err_new(const enum ErrorType type, const char *message) {
    return (struct ErrorCode){type, strdup(message)};
}

struct TileMinerals getTileMinerals(uint32_t colour) {
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

bool isTree(enum TileType type) {
	switch (type) {
		case TILE_TREE:
		case TILE_PINE:
		case TILE_PINEFOREST:
		case TILE_FOREST:
		return true;
		default: return false;
	}
}

bool isMineral(enum TileType type) {
	switch (type) {
		case TILE_ROCK:
		return true;
		default:
		return false;
	}
}

bool isClearable(enum TileType type) {
	switch (type) {
		case TILE_BUSH:
		return true;
		default:
		return false;
	}
}

const char *getTileTypeName(enum TileType t) {
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

const char *getTaskTypeName(enum TaskType t) {
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
