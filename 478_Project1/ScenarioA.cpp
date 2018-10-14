#include "ScenarioA.h"



ScenarioA::ScenarioA()
{
	this->slotCount = 0;
	this->numConcurrentColl = 0;
	this->nodeACollisions = 0;
	this->nodeASuccesses = 0;
	this->nodeCCollisions = 0;
	this->nodeCSuccesses = 0;
}

std::vector<int> ScenarioA::generateFrameVals(double frameTime, int lambda) {
	// random frame times
	std::vector<int> randomFrameVals;

	int randFrame{ 0 };
	double randVal = 0;
	while (randFrame < 100000) {
		randVal = ((double)rand() / (double)RAND_MAX);
		randVal = (-1.0 / (double)lambda) * log(1 - randVal); // get X values
		randFrame += (randVal / frameTime);
		randomFrameVals.push_back(randFrame);
	}

	return randomFrameVals;
}

// generate a random backoff value
int backoffGen(int cw0, int cwMax, int numCollisions) {
	int backoffVal{ rand() % ((int)pow(2, numCollisions) * cw0) };

	return backoffVal < cwMax ? backoffVal : cwMax;
}

template <class T>
void printVec(std::vector<T> vec) {
	for (auto& elem : vec) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;
}

void ScenarioA::testRandomValues(double frameTime, int lambda) {
	printVec(generateFrameVals(frameTime, lambda));
}

void ScenarioA::runProtocol(std::vector<int> Ca, std::vector<int> Cc) {

	int backOffA = 0;
	int backOffC = 0;
	int dataNumSlots = 100;
	int DIFS = 2;
	int SIFS = 1;
	int ACK = 2;

	this->slotCount;
	while (!Ca.empty() && !Cc.empty() && this->slotCount < 100000)
	{
		backOffA = backoffGen(4, 1024, this->numConcurrentColl);
		backOffC = backoffGen(4, 1024, this->numConcurrentColl);
		if (Ca.at(0) < this->slotCount && Cc.at(0) < this->slotCount)
		{

			if (backOffA < backOffC)
			{
				backOffC = backOffC - backOffA;
				this->slotCount += DIFS + backOffA + dataNumSlots + SIFS + ACK;
				Ca.erase(Ca.begin());
				this->numConcurrentColl = 0;
				this->nodeASuccesses++;
			}
			else if (backOffA > backOffC)
			{
				backOffA = backOffA - backOffC;
				this->slotCount += +DIFS + backOffC + dataNumSlots + SIFS + ACK;
				Cc.erase(Cc.begin());
				this->numConcurrentColl = 0;
				this->nodeCSuccesses++;
			}
			else
			{
				this->numConcurrentColl++;
				this->slotCount += backOffA;
				this->nodeACollisions++;
				this->nodeCCollisions++;
			}
		}
		else if (Ca.at(0) + backOffA < Cc.at(0) + backOffC)
		{
			if (Ca.at(0) > this->slotCount)
			{
				this->slotCount = Ca.at(0);
			}

			this->slotCount = this->slotCount + DIFS + backOffA + dataNumSlots + SIFS + ACK;
			Ca.erase(Ca.begin());
			this->numConcurrentColl = 0;
			this->nodeASuccesses++;
		}
		else if (Ca.at(0) + backOffA > Cc.at(0) + backOffC)
		{
			if (Cc.at(0) > this->slotCount)
			{
				this->slotCount = Cc.at(0);
			}
			this->slotCount = this->slotCount + DIFS + backOffC + dataNumSlots + SIFS + ACK;
			Cc.erase(Cc.begin());
			this->numConcurrentColl = 0;
			this->nodeCSuccesses++;
		}
		else
		{
			if (Ca.at(0) > this->slotCount)
			{
				this->slotCount = Ca.at(0);
			}


			if (backOffA < backOffC)
			{
				backOffC = backOffC - backOffA;
				this->slotCount += DIFS + backOffA + dataNumSlots + SIFS + ACK;
				Ca.erase(Ca.begin());
				this->numConcurrentColl = 0;
				this->nodeASuccesses++;
			}
			else if (backOffA > backOffC)
			{
				backOffA = backOffA - backOffC;
				this->slotCount += +DIFS + backOffC + dataNumSlots + SIFS + ACK;
				Cc.erase(Cc.begin());
				this->numConcurrentColl = 0;
				this->nodeCSuccesses++;
			}
			else
			{
				this->numConcurrentColl++;
				this->slotCount += backOffA;
				this->nodeACollisions++;
				this->nodeCCollisions++;
			}

		}
	}

}

void ScenarioA::runProtocol2(std::vector<int> Ca, std::vector<int> Cc)
{

	int backOffA = 0;
	int backOffC = 0;
	int dataNumSlots = 100;
	int DIFS = 2;
	int SIFS = 1;
	int ACK = 2;
	int RTS = 2;
	int CTS = 2;

	this->slotCount;
	while (!Ca.empty() && !Cc.empty() && this->slotCount < 100000)
	{
		backOffA = backoffGen(4, 1024, this->numConcurrentColl);
		backOffC = backoffGen(4, 1024, this->numConcurrentColl);
		if (Ca.at(0) < this->slotCount && Cc.at(0) < this->slotCount)
		{

			if (backOffA < backOffC)
			{
				backOffC = backOffC - backOffA;
				this->slotCount += DIFS + backOffA + dataNumSlots + SIFS + ACK;
				Ca.erase(Ca.begin());
				this->numConcurrentColl = 0;
				this->nodeASuccesses++;
			}
			else if (backOffA > backOffC)
			{
				backOffA = backOffA - backOffC;
				this->slotCount += +DIFS + backOffC + dataNumSlots + SIFS + ACK;
				Cc.erase(Cc.begin());
				this->numConcurrentColl = 0;
				this->nodeCSuccesses++;
			}
			else
			{
				this->numConcurrentColl++;
				this->slotCount += backOffA;
				this->nodeACollisions++;
				this->nodeCCollisions++;
			}
		}
		else if (Ca.at(0) + backOffA < Cc.at(0) + backOffC)
		{
			if (Ca.at(0) > this->slotCount)
			{
				this->slotCount = Ca.at(0);
			}

			this->slotCount = this->slotCount + DIFS + backOffA + dataNumSlots + SIFS + ACK;
			Ca.erase(Ca.begin());
			this->numConcurrentColl = 0;
			this->nodeASuccesses++;
		}
		else if (Ca.at(0) + backOffA > Cc.at(0) + backOffC)
		{
			if (Cc.at(0) > this->slotCount)
			{
				this->slotCount = Cc.at(0);
			}
			this->slotCount = this->slotCount + DIFS + backOffC + dataNumSlots + SIFS + ACK;
			Cc.erase(Cc.begin());
			this->numConcurrentColl = 0;
			this->nodeCSuccesses++;
		}
		else
		{
			if (Ca.at(0) > this->slotCount)
			{
				this->slotCount = Ca.at(0);
			}


			if (backOffA < backOffC)
			{
				backOffC = backOffC - backOffA;
				this->slotCount += DIFS + backOffA + dataNumSlots + SIFS + ACK;
				Ca.erase(Ca.begin());
				this->numConcurrentColl = 0;
				this->nodeASuccesses++;
			}
			else if (backOffA > backOffC)
			{
				backOffA = backOffA - backOffC;
				this->slotCount += +DIFS + backOffC + dataNumSlots + SIFS + ACK;
				Cc.erase(Cc.begin());
				this->numConcurrentColl = 0;
				this->nodeCSuccesses++;
			}
			else
			{
				this->numConcurrentColl++;
				this->slotCount += backOffA;
				this->nodeACollisions++;
				this->nodeCCollisions++;
			}

		}
	}
}