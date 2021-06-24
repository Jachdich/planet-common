#ifndef __RESOURCES_H
#define __RESOURCES_H
#include <jsoncpp/json/json.h>
#include <string>
#include <unordered_map>
#include <iostream>

struct ResourceValue {
    double value;
    double capacity;
    inline bool operator==(const ResourceValue &other) {
        return this->value == other.value && this->capacity == other.capacity;
    }
};

#define EPSILON 0.00001

struct Resources {
	std::unordered_map<std::string, ResourceValue> data = {
	    {"wood",        {0, 0}},
	    {"stone",       {0, 0}},
	    {"food",        {0, 0}},
	    {"water",       {0, 0}},
 	    {"people",      {0, 0}},
 	    {"peopleIdle",  {0, 0}},
 	    {"ironOre",     {0, 0}},
 	    {"copperOre",   {0, 0}},
 	    {"aluminiumOre",{0, 0}},
 	    {"iron",        {0, 0}},
 	    {"copper",      {0, 0}},
 	    {"aluminium",   {0, 0}},
 	    {"silicon",     {0, 0}},
 	    {"oil",         {0, 0}},
 	    {"plastic",     {0, 0}},
 	    {"glass",       {0, 0}},
 	    {"sand",        {0, 0}},
	};

	inline Resources() {}

	inline Resources(std::unordered_map<std::string, double> binds) {
	    for (auto entry: binds) {
           data[entry.first].value = entry.second;
         }
	}

	inline Resources(std::unordered_map<std::string, ResourceValue> binds) {
        for (auto entry: binds) {
          data[entry.first] = entry.second;
        }
    }
	
    inline std::string toString() {
        std::string res;
    	for (const auto& entry: data) {
            res += entry.first + ": " + std::to_string(entry.second.value) + "/" + std::to_string(entry.second.capacity) + ", ";
        }
        return res;
	}

	inline bool operator==(Resources& other) const {
	    bool result;
    	for (auto& entry: data) {
	        result = result && (entry.second.value == other.data[entry.first].value);
	    }
	    return result;
	}

    inline bool operator>=(Resources& other) const {
	    bool result = true;
    	for (auto& entry: data) {
	        result = result && (entry.second.value >= other.data[entry.first].value); //TODO use epsilon?
	    }
	    return result;
	}
	
	inline bool operator!=(Resources& other) const {
		return !(*this == other);
	}

	inline void operator+=(Resources& other) {
    	for (const auto& entry: data) {
	        this->data[entry.first].value += other.data[entry.first].value;
	    }   
	}
	
	inline void operator-=(Resources& other) {
    	for (const auto& entry: data) {
	        this->data[entry.first].value -= other.data[entry.first].value;
	    }
	}

	inline double& operator[](const std::string &key) {
	    return data[key].value;
	}

	inline double& getCapacity(const std::string &key) {
        return data[key].capacity;
	}

	inline Resources clone() {
	    Resources r;
	    r.data = std::unordered_map<std::string, ResourceValue>(this->data);
	    return r;
	}

	inline bool isZero() {
	    for (const auto& entry: data) {
 	        if (entry.second.value > EPSILON) {
 	            std::cout << entry.first << "\n";
 	            return false;
 	        }
 	    }
 	    return true;
	}
};


inline Resources getResourcesFromJson(Json::Value root) {
    Resources n;
    for (const auto& entry: n.data) {
	    n.data[entry.first].value = root[entry.first]["value"].asDouble();
	    n.data[entry.first].capacity = root[entry.first]["capacity"].asDouble();
	}
    return n;
}

inline Json::Value getJsonFromResources(Resources stats) {
    Json::Value root;
    for (const auto& entry: stats.data) {
        root[entry.first]["value"] = entry.second.value;
        root[entry.first]["capacity"] = entry.second.capacity;
    }
    
    return root;
}

inline void getJsonFromResources(Resources stats, Json::Value& root) {
    for (const auto& entry: stats.data) {
        root[entry.first]["value"] = entry.second.value;
        root[entry.first]["capacity"] = entry.second.capacity;
    }
}

#endif
