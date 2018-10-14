/*
	ECE 478 Project 1
	Coby Allred and Marc Gefrides
*/

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include "ScenarioA.h"
#include "ScenarioB.h"

int main(int argc, char* argv[]) {
	// default simulation params
	int cwMin{ 4 };
	int cwMax{ 1024 };

	double simTime{ 10.0 };
	double slotDuration{ 20.0 / 1000000.0 };

	int sifsSlots{ 1 };
	int difsSlots{ 2 };
	int dataFrameSlots{ 100 };
	int ackRtsCtsSlots{ 2 };

	std::vector<int> lambdaVals{ 50, 100, 200, 300 };

	// seed random values
	srand((unsigned)time(nullptr));

	ScenarioA scenACSMA1;
	std::vector<int> Ca = scenACSMA1.generateFrameVals(slotDuration, 300);
	std::vector<int> Cc = scenACSMA1.generateFrameVals(slotDuration, 600);
	scenACSMA1.runProtocol(Ca, Cc);

	ScenarioB scenBCSMA1;
	Ca = scenBCSMA1.generateFrameVals(slotDuration, 600);
	Cc = scenBCSMA1.generateFrameVals(slotDuration, 300);
	scenBCSMA1.runProtocol(Ca, Cc);

	std::string asdf;
	std::cin >> asdf;
}

