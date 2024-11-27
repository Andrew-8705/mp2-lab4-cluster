#pragma once

#include "queue.h"
#include "Stream.h"

using namespace std;

class CPU {
private:
	bool busy;
	Task curTask;
public:
	CPU();

	bool IsBusy() const;

	void process(TQueue<Task>& taskQueue, int& downtime_ticks);

	int GetCurrentTaskId() const;
};

