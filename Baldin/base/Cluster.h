#pragma once

#include "CPU.h"
#include "Stream.h"
#include <iostream>

using namespace std;

struct SimulationStatistics {
	int total_tasks; // ����� ���������� ��������
	int task_refusals; // ���������� ������� ��-�� ������ �������
	int total_ticks; // ����� ���������� ������
	int downtime_ticks; // ���������� ������ �������
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
