#include "planetdata.h"
#include "enums.h"
class PlanetSurface;
PlanetData::PlanetData() {}
PlanetData::PlanetData(PlanetSurface * surface) {
	this->surface = surface;
}

bool PlanetData::dipatchTask(TaskType type, Tile * target) {
	for (Person &p * this->people) {
		if (p.job == nullptr && p.task == nullptr) {
			p.task = new Task(type, target);
			return true;
		}
	}
	return false;
}

std::vector<TileType> PlanetData::getPossibleTasks(Tile * target) {
	std::vector<TileType> v;
	switch (target->type) {
		case TileType::TREE: v.push_back(TaskType::GATHER_MATERIALS);
	}
}
