#ifndef __SURFACELOCATOR_TEST_H
#define __SURFACELOCATOR_TEST_H

#include "star.h"
#include "planetsurface.h"
#include "planet.h"
#include "sector.h"

#ifdef __SERVER_H
#include "network.h"

inline PlanetSurface *getSurfaceFromLocator(struct SurfaceLocator *loc) {
    Sector *sec = map.getSectorAt(loc->sectorX, loc->sectorY);
	if (loc.starPos < sec->numStars) {
		Star *s = &sec->stars[loc->starPos];
		if (loc.planetPos < s->num) {
			Planet *p = &s->planets[loc->planetPos];
			PlanetSurface *surf = p->getSurface();
			return surf;
		} else {
			return NULL;
		}
	} else {
		return NULL;
	}
}

inline PlanetSurface *getSurfaceFromJson(Json::Value root) {
	SurfaceLocator loc = getSurfaceLocatorFromJson(root);
	return getSurfaceFromLocator(loc);
}
#endif //__SERVER_H

#ifdef __CLIENT_H
#include "sectorcache.h"
inline PlanetSurface *getSurfaceFromJson(Json::Value root, SectorCache * cache) {
	SurfaceLocator loc = getSurfaceLocatorFromJson(root);
	Sector *sec = cache->getSectorAt(loc.sectorX, loc.sectorY);
	if (loc.starPos < sec->numStars) {
		Star *s = &sec->stars[loc.starPos];
		if (loc.planetPos < s->num) {
			Planet *p = &s->planets[loc.planetPos];
			PlanetSurface *surf = p->surface;
			return surf;
		} else {
			return NULL;
		}
	} else {
		return NULL;
	}
}
#endif //CLIENT_H

#endif
