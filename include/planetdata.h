#ifndef __PLANETDATA_H
#define __PLANETDATA_H
#include <vector>
#include "enums.h"

class PlanetSurface;
struct Tile;

struct Task {
	Tile * target;
	TaskType type;
	double durationLeft;
	inline Task(TaskType type, Tile * target) {
		this->type = type;
		this->target = target;
		switch (type) {
			case TaskType::FELL_TREE:
				durationLeft = 60.0;
				break;
			case TaskType::CLEAR:
				durationLeft = 3.0;
				break;
			case TaskType::GATHER_MINERALS:
				durationLeft = 10.0;
				break;
		}
	}
};

struct Job {
	Tile * pos;
};

struct Person {
	Task * task = nullptr;
	Job  * job  = nullptr;
	int age;
	void tick(long elapsedTime);
};

class PlanetData {
public:
	std::vector<Person> people;
	std::vector<Task>   toDoTasks;
	std::vector<Task>   doingTasks;
	std::vector<Job>    unassignedJobs;
	std::vector<Job>    assignedJobs;
	PlanetSurface * surface;
	bool threadStopped = false;
	long lastTimeStamp;
	PlanetData();
	PlanetData(PlanetSurface * surface);
	std::vector<TaskType> getPossibleTasks(Tile * target);
	bool dispatchTask(TaskType type, Tile * target);
	void tick();
	void runLogic();
	void stopThread();

};

#endif
