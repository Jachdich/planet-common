#ifndef __STATS_H
#define __STATS_H
#include <jsoncpp/json/json.h>
#include <string>

struct Stats {
	uint32_t wood = 0;
	uint32_t stone = 0;
	uint32_t iron = 0;
	uint32_t food = 0;
	uint32_t water = 0;
	uint32_t people = 0;
	uint32_t peopleIdle = 0;
	uint32_t peopleSlots = 0;
	inline std::string toString() {
		return
		"people: " + std::to_string(people) + ", " + 
		"peopleSlots: " + std::to_string(peopleSlots);
	}

	inline bool operator==(const Stats& other) const {
		return 
			wood == other.wood &&
			stone == other.stone &&
			iron == other.iron &&
			food == other.food &&
			water == other.water &&
			people == other.people &&
			peopleIdle == other.peopleIdle &&
			peopleSlots == other.peopleSlots;
	}

	inline bool operator!=(const Stats& other) const {
		return !(*this == other);
	}
};


inline Stats getStatsFromJson(Json::Value root) {
    return {
        root["wood"].asUInt(),
        root["stone"].asUInt(),
        root["iron"].asUInt(),
        root["food"].asUInt(),
        root["water"].asUInt(),
        root["people"].asUInt(),
        root["peopleIdle"].asUInt(),
        root["peopleSlots"].asUInt(),
    };
}

inline Json::Value getJsonFromStats(Stats stats) {
    Json::Value root;
    root["wood"] = stats.wood;
    root["stone"] = stats.stone;
    root["iron"] = stats.iron;
    root["food"] = stats.food;
    root["water"] = stats.water;
    root["people"] = stats.people;
    root["peopleIdle"] = stats.peopleIdle;
    root["peopleSlots"] = stats.peopleSlots;
    return root;
}

#endif
