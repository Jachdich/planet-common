#include "planetdata.h"
#include "enums.h"
#include "tile.h"
#include <chrono>

class PlanetSurface;
PlanetData::PlanetData() {}
PlanetData::PlanetData(PlanetSurface * surface) {
	this->surface = surface;
	this->people.push_back(Person());
}

void Person::tick(long elapsedMs) {
	double elapsedS = elapsedMs / 1000.0;
	if (this->task != nullptr) {
		switch (this->task->type) {
			case TaskType::FELL_TREE:
				this->task->durationLeft -= elapsedS;
				std::cout << "time left: " << this->task->durationLeft << "\n";
				if (this->task->durationLeft <= 0) {
					this->task->target->type = TileType::GRASS;
					delete this->task;
					this->task = nullptr;
				}
				break;

			case TaskType::CLEAR:
				break;
			case TaskType::GATHER_MINERALS:
				break;
		}
	}
}

void PlanetData::tick() {
	long ms = std::chrono::duration_cast< std::chrono::milliseconds >(
		std::chrono::system_clock::now().time_since_epoch()).count();

	long elapsedTime = ms - this->lastTimeStamp;
	for (Person &p : this->people) {
		p.tick(elapsedTime);
	}

	this->lastTimeStamp = ms;
}

void PlanetData::runLogic() {
	while (!threadStopped) {
		unsigned long long startns = std::chrono::duration_cast< std::chrono::microseconds >(
	    	std::chrono::system_clock::now().time_since_epoch()).count();
		tick();

		unsigned long long endns = std::chrono::duration_cast< std::chrono::microseconds >(
	    	std::chrono::system_clock::now().time_since_epoch()).count();

		std::this_thread::sleep_for(std::chrono::microseconds(100000 - (endns - startns)));
	}
}

void PlanetData::stopThread() {
	this->threadStopped = true;
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
