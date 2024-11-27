#include <iostream>
#include "Cluster.h"
#include <stdexcept>

using namespace std;

int main()
{
	srand(time(0));
	try {
		Cluster cluster(15, 0.5);
		cluster.RunSimulation(1000);
		SimulationStatistics st = cluster.GetStatistics();
		cout << "Simulation completed.\n";
		cout << "Total tasks generated: " << st.total_tasks << '\n';
		cout << "Total task refusals: " << st.task_refusals << " (" << (100.0 * st.task_refusals / st.total_tasks) << "%)\n";
		cout << "Processor downtime ticks: " << st.downtime_ticks << " (" << (100.0 * st.downtime_ticks / st.total_ticks) << "%)\n";
		cout << "Total simulation ticks: " << st.total_ticks << '\n';
	}
	catch (const exception& e) {
		cout << e.what() << '\n';
	}
}
