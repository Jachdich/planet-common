#ifndef __RESOURCES_H
#define __RESOURCES_H
#include <jsoncpp/json/json.h>
#include <string>
#include <unordered_map>

struct ResourceValue {
    double value;
    double capacity;
    inline bool operator==(const ResourceValue &other) {
        return this->value == other.value && this->capacity == other.capacity;
    }
};

#define DEFAULT_CAPACITY 500

struct Resources {
	std::unordered_map<std::string, ResourceValue> data = {
	    {"wood",        {0, DEFAULT_CAPACITY}},
	    {"stone",       {0, DEFAULT_CAPACITY}},
	    {"food",        {0, DEFAULT_CAPACITY}},
	    {"water",       {0, DEFAULT_CAPACITY}},
 	    {"people",      {0, DEFAULT_CAPACITY}},
 	    {"peopleIdle",  {0, DEFAULT_CAPACITY}},
 	    {"peopleSlots", {0, DEFAULT_CAPACITY}},
 	    {"ironOre",     {0, DEFAULT_CAPACITY}},
 	    {"copperOre",   {0, DEFAULT_CAPACITY}},
 	    {"aluminiumOre",{0, DEFAULT_CAPACITY}},
 	    {"iron",        {0, DEFAULT_CAPACITY}},
 	    {"copper",      {0, DEFAULT_CAPACITY}},
 	    {"aluminium",   {0, DEFAULT_CAPACITY}},
 	    {"silicon",     {0, DEFAULT_CAPACITY}},
 	    {"oil",         {0, DEFAULT_CAPACITY}},
 	    {"plastic",     {0, DEFAULT_CAPACITY}},
 	    {"glass",       {0, DEFAULT_CAPACITY}},
 	    {"sand",        {0, DEFAULT_CAPACITY}},
	};

	inline Resources() {}

	inline Resources(std::unordered_map<std::string, double> binds) {
	    for (auto &[k, v]: binds) {
	        data[k].value = v;
	    }
	}

	inline Resources(std::unordered_map<std::string, ResourceValue> binds) {
        for (auto &[k, v]: binds) {
          data[k] = v;
        }
    }
	
    inline std::string toString() {
        std::string res;
    	for (const auto& [key, value]: data) {
            res += key + ": " + std::to_string(value.value) + "/" + std::to_string(value.capacity) + ", ";
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

    inline bool operator>=(Resources& other) const {
	    bool result = true;
    	for (const auto& [key, value]: data) {
	        result = result && (value.value >= other.data[key].value); //TODO use epsilon?
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

inline void getJsonFromResources(Resources stats, Json::Value& root) {
    for (const auto& [key, value]: stats.data) {
        root[key] = value;
    }
}

#endif
