#include "planetdata.h"
#include "enums.h"
#include "tile.h"

class PlanetSurface;
PlanetData::PlanetData() {}
PlanetData::PlanetData(PlanetSurface * surface) {
	this->surface = surface;
}

bool PlanetData::dipatchTask(TaskType type, Tile * target) {
	for (Person &p : this->people) {
		if (p.job == nullptr && p.task == nullptr) {
			p.task = new Task(type, target);
			return true;
		}
	}
	return false;
}

std::vector<TaskType> PlanetData::getPossibleTasks(Tile * target) {
	std::vector<TaskType> v;
	if (isTree(target->type)) {
		v.push_back(TaskType::FELL_TREE);
	}
	if (isMineral(target->type)) {
		v.push_back(TaskType::GATHER_MINERALS);
	}
	if (isClearable(target->type)) {
		v.push_back(TaskType::CLEAR);
	}
	return v;
}
