#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

class ScenarioA
{
private:
	// keep track of successes and failures
	int nodeASuccesses;
	int nodeCSuccesses;
	int nodeACollisions;
	int nodeCCollisions;

	int numConcurrentColl;

	// global slot counter
	int slotCount;

	// keep a running backoff count for each channel
	int channelABackoffCount;
	int channelBBackoffCount;

public:
	ScenarioA();
	std::vector<int> generateFrameVals(double frameTime, int lambda);
	void testRandomValues(double frameTime, int lambda);
	void runProtocol(std::vector<int> Ca, std::vector<int> Cc);
};

