#pragma once

#include <cstdlib>

using namespace std;

struct Task {
	int id;
	int remainingTicks;
	Task(int id_ = -1, int ticks_ = 0) : id(id_), remainingTicks(ticks_) {}
};

class Stream {
private:
	double intensity; // интенсивность потока задач
	int taskCounter; // номер текущего задания

public:
	Stream(double intensity_);

	bool GenerateTask();

	Task GetNextTask();
};