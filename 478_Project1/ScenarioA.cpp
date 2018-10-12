#include "ScenarioA.h"



ScenarioA::ScenarioA()
{

}

std::vector<int> generateFrameVals(double frameTime, int lambda) {
	// random frame times
	std::vector<int> randomFrameVals;

	double totalMs{ 0 };
	int randFrame{ 0 };

	while (randFrame < 100000) {
		double randVal = ((double)rand() / (double)RAND_MAX);
		randVal = (-1.0 / (double)lambda) * log(1 - randVal); // get X values
		totalMs += randVal;
		randFrame = (totalMs / frameTime);
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
	while (!Ca.empty() && !Cc.empty() && this->slotCount < 100000);
	{
        if (Ca.at(0) < this->slotCount && Cc.at(0) < this->slotCount)
        {
            backOffA = backoffGen(4, 1024, this->numConcurrentColl);
            backOffC = backoffGen(4, 1024, this->numConcurrentColl);
            
            if (backOffA < backOffC)
            {
                backOffC = backOffC - backOffA;
                this->slotCount += DIFS + backOffA + dataNumSlots + SIFS + ACK;
                Ca.erase(Ca.begin());
                this->numConcurrentColl = 0;
            }
            else if (backOffA > backOffC)
            {
                backOffA = backOffA - backOffC;
                this->slotCount += + DIFS + backOffC + dataNumSlots + SIFS + ACK;
                Cc.erase(Cc.begin());
                this->numConcurrentColl = 0;
            }
            else
            {
                this->numConcurrentColl++;
                this->slotCount += backOffA;
            }
        }
		else if (Ca.at(0) < Cc.at(0))
		{
			this->slotCount = Ca.at(0);
			backOffA = backoffGen(4, 1024, this->numConcurrentColl);
			this->slotCount = this->slotCount + DIFS + backOffA + dataNumSlots + SIFS + ACK;
            Ca.erase(Ca.begin());
            this->numConcurrentColl = 0;
		}
		else if (Ca.at(0) > Cc.at(0))
		{
			this->slotCount = Cc.at(0);
			backOffC = backoffGen(4, 1024, this->numConcurrentColl);
			this->slotCount = this->slotCount + DIFS + backOffC + dataNumSlots + SIFS + ACK;
            Cc.erase(Cc.begin());
            this->numConcurrentColl = 0;
		}
		else
		{
			this->slotCount = Ca.at(0);
			backOffA = backoffGen(4, 1024, this->numConcurrentColl);
			backOffC = backoffGen(4, 1024, this->numConcurrentColl);

			if (backOffA < backOffC)
			{
				backOffC = backOffC - backOffA;
				this->slotCount += DIFS + backOffA + dataNumSlots + SIFS + ACK;
                Ca.erase(Ca.begin());
                this->numConcurrentColl = 0;
			}
			else if (backOffA > backOffC)
			{
				backOffA = backOffA - backOffC;
				this->slotCount += + DIFS + backOffC + dataNumSlots + SIFS + ACK;
                Cc.erase(Cc.begin());
                this->numConcurrentColl = 0;
			}
			else
			{
				this->numConcurrentColl++;
				this->slotCount += backOffA;
			}

		}
	}
}
