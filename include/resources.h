#ifndef __RESOURCES_H
#define __RESOURCES_H
#include <jsoncpp/json/json.h>
#include <string>
#include <unordered_map>

struct Resources {
	std::unordered_map<std::string, double> data = {
	    {"wood", 0},
	    {"stone", 0},
	    {"food", 0},
	    {"water", 0},
 	    {"people", 0},
 	    {"peopleIdle", 0},
 	    {"peopleSlots", 0},
 	    {"ironOre", 0},
 	    {"copperOre", 0},
 	    {"aluminiumOre", 0},
 	    {"iron", 0},
 	    {"copper", 0},
 	    {"aluminium", 0},
 	    {"silicon", 0},
 	    {"oil", 0},
 	    {"plastic", 0},
 	    {"glass", 0},
 	    {"sand", 0},
	};

	inline Resources() {}

	inline Resources(std::unordered_map<std::string, double> binds) {
	    data.insert(binds.begin(), binds.end());
	}
	
    inline std::string toString() {
        std::string res;
    	for (const auto& [key, value]: data) {
            res += key + ": " + std::to_string(value) + ", ";
        }
        return res;
	}

	inline bool operator==(Resources& other) const {
	    bool result;
    	for (const auto& [key, value]: data) {
	        result = result && (value == other.data[key]);
	    }
	    return result;
	}

    inline bool operator>(Resources& other) const {
	    bool result;
    	for (const auto& [key, value]: data) {
	        result = result && (value > other.data[key]);
	    }
	    return result;
	}
	
	inline bool operator!=(Resources& other) const {
		return !(*this == other);
	}

	inline void operator+=(Resources& other) {
    	for (const auto& [key, value]: data) {
	        this->data[key] += other.data[key];
	    }   
	}
	
	inline void operator-=(Resources& other) {
    	for (const auto& [key, value]: data) {
	        this->data[key] -= other.data[key];
	    }
	}

	inline double& operator[](const std::string &key) {
	    return data[key];
	}

	inline Resources clone() {
	    Resources r;
	    r.data = std::unordered_map<std::string, double>(this->data);
	    return r;
	}
};


inline Resources getResourcesFromJson(Json::Value root) {
    Resources n;
    for (const auto& [key, value]: n.data) {
	    n.data[key] = root[key].asDouble();
	}
    return n;
}

inline Json::Value getJsonFromResources(Resources stats) {
    Json::Value root;
    	for (const auto& [key, value]: stats.data) {
        root[key] = value;
    }
    
    return root;
}

#endif
