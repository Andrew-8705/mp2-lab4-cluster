#include "Stream.h"

using namespace std;

Stream::Stream(double intensity_) : intensity(intensity_), taskCounter(0) {}

bool Stream::GenerateTask() {
	return static_cast<double>(rand()) / RAND_MAX < intensity;
}

Task Stream::GetNextTask() {
	return Task(++taskCounter, rand() % 10 + 1);
}
