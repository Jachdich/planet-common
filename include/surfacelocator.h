#ifndef __SURFACELOCATOR_H
#define __SURFACELOCATOR_H
#include <jsoncpp/json/json.h>
#include "planetsurface.h"
#include "planet.h"
#include "star.h"
#include "sector.h"

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

#ifdef __SERVER_H
#include "network.h"

PlanetSurface * getSurfaceFromLocator(SurfaceLocator loc) {
    Sector * sec = map.getSectorAt(loc.sectorX, loc.sectorY);
	if (loc.starPos < sec->numStars) {
		Star * s = &sec->stars[loc.starPos];
		if (loc.planetPos < s->num) {
			Planet * p = &s->planets[static_cast<int>(loc.planetPos)];
			PlanetSurface * surf = p->getSurface();
			return surf;
		} else {
			return nullptr;
		}
	} else {
		return nullptr;
	}
}

PlanetSurface * getSurfaceFromJson(Json::Value root) {
	SurfaceLocator loc = getSurfaceLocatorFromJson(root);
	return getSurfaceFromLocator(loc);
}
#endif //__SERVER_H

#ifdef __CLIENT_H
#include "sectorcache.h"
inline PlanetSurface * getSurfaceFromJson(Json::Value root, SectorCache * cache) {
	SurfaceLocator loc = getSurfaceLocatorFromJson(root);
	Sector * sec = cache->getSectorAt(loc.sectorX, loc.sectorY);
	if (loc.starPos < sec->numStars) {
		Star * s = &sec->stars[loc.starPos];
		if (loc.planetPos < s->num) {
			Planet * p = &s->planets[loc.planetPos];
			PlanetSurface * surf = p->surface;
			return surf;
		} else {
			return nullptr;
		}
	} else {
		return nullptr;
	}
}
#endif //CLIENT_H

#endif
