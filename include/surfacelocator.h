#ifndef __SURFACELOCATOR_H
#define __SURFACELOCATOR_H
#include <jsoncpp/json/json.h>

extern "C" {
#include <stdint.h>
#include <stdbool.h>

struct SurfaceLocator {
	uint8_t planetPos;
	uint8_t starPos;
	int32_t sectorX;
	int32_t sectorY;
};

inline bool locator_eq(const struct SurfaceLocator *a, const struct SurfaceLocator *b) {
    return a->sectorX == b->sectorX &&
           a->sectorY == b->sectorY &&
           a->starPos == b->starPos &&
           a->planetPos == b->planetPos;
}
}

inline struct SurfaceLocator getSurfaceLocatorFromJson(Json::Value root) {
	int32_t secX, secY;
    uint8_t starPos, planetPos;
	secX = root.get("secX", 0).asInt();
	secY = root.get("secY", 0).asInt();
	starPos = root.get("starPos", 0).asInt();
	planetPos = root.get("planetPos", 0).asInt();
	return (struct SurfaceLocator){planetPos, starPos, secX, secY};
}

inline void getJsonFromSurfaceLocator(const struct SurfaceLocator *loc, Json::Value& root) {
	root["secX"] = loc->sectorX;
	root["secY"] = loc->sectorY;
	root["starPos"] = loc->starPos;
	root["planetPos"] = loc->planetPos;
}
#endif
