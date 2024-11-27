#include "Cluster.h"

using namespace std;

Cluster::Cluster(int qSize, double taskIntensity) : q(qSize), taskStream(taskIntensity), stat({ 0,0,0,0 }) {
	if (qSize < 1) {
		throw invalid_argument("Queue size must be greater than zero.");
	}
	if (taskIntensity < 0.0 || taskIntensity > 1.0) {
		throw invalid_argument("Task intensity must be between 0 and 1.");
	}
}

void Cluster::RunSimulation(int numTicks) {
	if (numTicks <= 0) {
		throw invalid_argument("Number of ticks must be greater than zero.");
	}

	for (int tick = 0; tick < numTicks; tick++) {
		stat.total_ticks++;
		if (taskStream.GenerateTask()) {
			stat.total_tasks++;
			try {
				q.Push(taskStream.GetNextTask());
			}
			catch (const overflow_error& e) {
				stat.task_refusals++;
			}
		}
		proc.process(q, stat.downtime_ticks);
	}
}

SimulationStatistics Cluster::GetStatistics() const {
	return stat;
}

