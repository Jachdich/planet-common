#ifndef __SURFACELOCATOR_H
#define __SURFACELOCATOR_H
#include <jsoncpp/json/json.h>

struct SurfaceLocator {
	char planetPos;
	char starPos;
	int sectorX;
	int sectorY;
};

void getJsonFromSurfaceLocator(SurfaceLocator loc, Json::Value& root);
SurfaceLocator getSurfaceLocatorFromJson(Json::Value root);

#endif
