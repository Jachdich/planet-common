#ifndef __SERIALISERS_H
#define __SERIALISERS_H
#include <jsoncpp/json/json.h>
#include "planetsurface.h"

Json::Value serialise(PlanetSurface &surf) {
    Json::Value res;
    for (unsigned int i = 0; i < surf.tiles.size(); i++) {
        res["tiles"].append((Json::Value::UInt64)surf.tiles[i]);
    }
    res["rad"] = surf.rad;
    return res;
}

#endif
