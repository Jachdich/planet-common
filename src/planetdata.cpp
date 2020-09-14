#include "planetdata.h"
#include "enums.h"
#include "tile.h"

class PlanetSurface;
PlanetData::PlanetData() {}
PlanetData::PlanetData(PlanetSurface * surface) {
	this->surface = surface;
	this->people.push_back(Person());
}

void Person::tick() {
	if (this->task != nullptr) {
		switch (this->task->type) {
			case TaskType::FELL_TREE:
				this->task->durationLeft--;
				if (this->task->durationLeft <= 0) {
					this->task->target->type = TileType::GRASS;
					delete this->task;
					this->task = nullptr;
				}
				break;
		}
	}
}

void PlanetData::tick() {
	for (Person &p : this->people) {
		p.tick();
	}
}

bool PlanetData::dispatchTask(TaskType type, Tile * target) {
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
	//if (target->type == TileType::GRASS) {
	//	v.push_back(TaskType::)
	//}
	return v;
}
