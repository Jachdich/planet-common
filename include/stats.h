#ifndef __STATS_H
#define __STATS_H
#include <jsoncpp/json/json.h>

struct Stats {
	uint32_t wood = 0;
	uint32_t stone = 0;
	uint32_t iron = 0;
	uint32_t people = 0;
	uint32_t peopleIdle = 0;
	uint32_t houses = 0;
};

inline Stats getStatsFromJson(Json::Value root) {
    return {
        root["wood"].asUInt(),
        root["stone"].asUInt(),
        root["iron"].asUInt(),
        root["people"].asUInt(),
        root["peopleIdle"].asUInt(),
        root["houses"].asUInt(),        
    };
}

inline Json::Value getJsonFromStats(Stats stats) {
    Json::Value root;
    root["wood"] = stats.wood;
    root["stone"] = stats.stone;
    root["iron"] = stats.iron;
    root["people"] = stats.people;
    root["peopleIdle"] = stats.peopleIdle;
    root["houses"] = stats.houses;
    return root;
}

#endif