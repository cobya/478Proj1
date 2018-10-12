/*
	ECE 478 Project 1
	Coby Allred and Marc Gefrides
*/

#include <iostream>
#include <string>
#include <vector>
#include <time.h>


int main(int argc, char* argv[]) {
	// default simulation params
	int cwMin{ 4 };
	int cwMax{ 1024 };

	double simTime{ 10.0 };
	double slotDuration{ 20.0 / 100000.0 };

	int sifsSlots{ 1 };
	int difsSlots{ 2 };
	int dataFrameSlots{ 100 };
	int ackRtsCtsSlots{ 2 };

	std::vector<int> lambdaVals{ 50, 100, 200, 300 };

	// seed random values
	srand((unsigned)time(nullptr));

}

