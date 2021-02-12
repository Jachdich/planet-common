#ifndef __SURFACELOCATOR_H
#define __SURFACELOCATOR_H
#include <jsoncpp/json/json.h>

struct SurfaceLocator {
	uint8_t planetPos;
	uint8_t starPos;
	int32_t sectorX;
	int32_t sectorY;

    bool operator==(const SurfaceLocator& other) {
        return sectorX == other.sectorX &&
               sectorY == other.sectorY &&
               starPos == other.starPos &&
               planetPos == other.planetPos;
    }
};

inline SurfaceLocator getSurfaceLocatorFromJson(Json::Value root) {
	int32_t secX, secY;
    uint8_t starPos, planetPos;
	secX = root.get("secX", 0).asInt();
	secY = root.get("secY", 0).asInt();
	starPos = root.get("starPos", 0).asInt();
	planetPos = root.get("planetPos", 0).asInt();
	return {planetPos, starPos, secX, secY};
}

inline void getJsonFromSurfaceLocator(SurfaceLocator loc, Json::Value& root) {
	root["secX"] = loc.sectorX;
	root["secY"] = loc.sectorY;
	root["starPos"] = loc.starPos;
	root["planetPos"] = loc.planetPos;
}
#endif
