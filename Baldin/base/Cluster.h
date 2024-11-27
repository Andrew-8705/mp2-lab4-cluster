#pragma once

#include "CPU.h"
#include "Stream.h"
#include <iostream>

using namespace std;

struct SimulationStatistics {
	int total_tasks; // общее количество операций
	int task_refusals; // количество отказов из-за полной очереди
	int total_ticks; // общее количество тактов
	int downtime_ticks; // количество тактов простоя
};

class Cluster
{
private:
	TQueue<Task> q;
	Stream taskStream;
	CPU proc;
	SimulationStatistics stat;
public:
	Cluster(int qSize, double taskIntensity);

	void RunSimulation(int numTicks);

	SimulationStatistics GetStatistics() const;
};
