#ifndef __SURFACELOCATOR_H
#define __SURFACELOCATOR_H
#include <jsoncpp/json/json.h>

struct SurfaceLocator {
	char planetPos;
	char starPos;
	int sectorX;
	int sectorY;
};

inline SurfaceLocator getSurfaceLocatorFromJson(Json::Value root) {
	int secX, secY;
    char starPos, planetPos;
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
