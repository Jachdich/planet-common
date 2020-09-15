#ifndef __PLANETDATA_H
#define __PLANETDATA_H
#include <vector>
#include "enums.h"

class PlanetSurface;
struct Tile;

struct Task {
	Tile * target;
	TaskType type;
	int durationLeft;
	inline Task(TaskType type, Tile * target) {
		this->type = type;
		this->target = target;
		durationLeft = 60;
	}
};

struct Job {
	Tile * pos;
};

struct Person {
	Task * task = nullptr;
	Job  * job  = nullptr;
	int age;
	void tick();
};

class PlanetData {
public:
	std::vector<Person> people;
	std::vector<Task>   toDoTasks;
	std::vector<Task>   doingTasks;
	std::vector<Job>    unassignedJobs;
	std::vector<Job>    assignedJobs;
	PlanetSurface * surface;
	PlanetData();
	PlanetData(PlanetSurface * surface);
	std::vector<TaskType> getPossibleTasks(Tile * target);
	bool dispatchTask(TaskType type, Tile * target);
	void tick();
	void runLogic();

};

#endif
