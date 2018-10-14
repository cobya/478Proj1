#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

class ScenarioB
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
    ScenarioB();
    std::vector<int> generateFrameVals(double frameTime, int lambda);
    void testRandomValues(double frameTime, int lambda);
	void runProtocol2(std::vector<int> Ca, std::vector<int> Cc);
    void runProtocol(std::vector<int> Ca, std::vector<int> Cc);
};

