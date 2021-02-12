#ifndef __STATS_H
#define __STATS_H
#include <jsoncpp/json/json.h>
#include <string>

struct Stats {
	uint32_t wood = 0;
	uint32_t stone = 0;
	double food = 0;
	uint32_t water = 0;
	uint32_t people = 0;
	uint32_t peopleIdle = 0;
	uint32_t peopleSlots = 0;

	uint32_t ironOre = 0;
	uint32_t copperOre = 0;
	uint32_t aluminiumOre = 0;
	uint32_t iron = 0;
	uint32_t copper = 0;
	uint32_t aluminium = 0;
	uint32_t silicon = 0;
	uint32_t oil = 0;
	uint32_t plastic = 0;
	
	inline std::string toString() {
		return
		"people: " + std::to_string(people) + ", " + 
		"peopleSlots: " + std::to_string(peopleSlots);
	}

	inline bool operator==(const Stats& other) const {
		return 
			wood == other.wood &&
			stone == other.stone &&
			food == other.food &&
			water == other.water &&
			people == other.people &&
			peopleIdle == other.peopleIdle &&
			peopleSlots == other.peopleSlots &&
			ironOre == other.ironOre &&
			copperOre == other.copperOre &&
			aluminiumOre == other.aluminiumOre &&
			iron == other.iron &&
            copper == other.copper &&
            aluminium == other.aluminium &&
            silicon == other.silicon &&
            oil == other.oil &&
            plastic == other.plastic;
	}

	inline bool operator!=(const Stats& other) const {
		return !(*this == other);
	}
};


inline Stats getStatsFromJson(Json::Value root) {
    return {
        root["wood"].asUInt(),
        root["stone"].asUInt(),
        root["food"].asDouble(),
        root["water"].asUInt(),
        root["people"].asUInt(),
        root["peopleIdle"].asUInt(),
        root["peopleSlots"].asUInt(),
        root["ironOre"].asUInt(),
        root["copperOre"].asUInt(),
        root["aluminiumOre"].asUInt(),
        root["iron"].asUInt(),
        root["copper"].asUInt(),
        root["aluminium"].asUInt(),
        root["silicon"].asUInt(),
        root["oil"].asUInt(),
        root["plastic"].asUInt(),
    };
}

inline Json::Value getJsonFromStats(Stats stats) {
    Json::Value root;
    root["wood"] = stats.wood;
    root["stone"] = stats.stone;
    root["food"] = stats.food;
    root["water"] = stats.water;
    root["people"] = stats.people;
    root["peopleIdle"] = stats.peopleIdle;
    root["peopleSlots"] = stats.peopleSlots;
    root["ironOre"] = stats.ironOre;
    root["copperOre"] = stats.copperOre;
    root["aluminiumOre"] = stats.aluminiumOre;
    root["iron"] = stats.iron;
    root["copper"] = stats.copper;
    root["aluminium"] = stats.aluminium;
    root["silicon"] = stats.silicon;
    root["oil"] = stats.oil;
    root["plastic"] = stats.plastic;
    
    return root;
}

#endif
