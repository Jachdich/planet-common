#include "planetdata.h"
#include "enums.h"
#include "tile.h"
#include "olcPixelGameEngine.h"
#include <chrono>
#include <string>

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

std::string pad(std::string str, int n = 2, char chr = '0') {
	return std::string(n - str.size(), chr) + str;
}

void PlanetData::draw(olc::PixelGameEngine * e, CamParams trx) {
	for (Person &p : this->people) {
		if (p.task != nullptr) {
			olc::vf2d pos = p.task->target->getTextureCoordinates(trx);
			olc::vf2d offset = {32 * trx.zoom, 64 * trx.zoom}; //TODO fractions of texture size not hardcoded values
			std::string txt = std::to_string((int)(p.task->durationLeft / 60)) + ":" + pad(std::to_string((int)(p.task->durationLeft) % 60));
			e->DrawStringDecal(pos + offset, txt, olc::WHITE, {trx.zoom * 3, trx.zoom * 3});
		}
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
