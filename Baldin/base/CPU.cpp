#include "CPU.h"

using namespace std;


CPU::CPU() : busy(false) {}

bool CPU::IsBusy() const { return busy; }

void CPU::process(TQueue<Task>& taskQueue, int& downtime_ticks) {
	if (IsBusy()) {
		if (curTask.remainingTicks <= 0) {
			busy = false;
		}
		else {
			curTask.remainingTicks--;
		}
	}

	if (!IsBusy() && !taskQueue.IsEmpty()) {
		curTask = taskQueue.Front();
		taskQueue.Pop();
		busy = true;
	}
	else if (!IsBusy() && taskQueue.IsEmpty()) {
		downtime_ticks++; // простой процессора
	}
}

int CPU::GetCurrentTaskId() const {
	return busy ? curTask.id : -1;
}

