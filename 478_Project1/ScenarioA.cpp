#include "ScenarioA.h"



ScenarioA::ScenarioA()
{

}

std::vector<int> generateCVals(double frameTime) {
	std::vector<double> randomUVals;
}

std::vector<double> generateRandomU() {
	std::vector<double> randVals;

	for (int i = 0; i < 5000; i++) {
		double randVal = ((double)rand() / (double)RAND_MAX);
		randVals.push_back(randVal);
	}

	return randVals;
}

std::vector<double> generateXFromU(int lambda, std::vector<double> U) {
	std::vector<double> xVals{ U };

	for (auto& elem : xVals) {
		elem = (-1.0 / (double)lambda) * log(1 - elem);
	}

	return xVals;
}

std::vector<int> generateCVals(std::vector<double> X, double frameTime) {
	double h = 0;
	std::vector<int> C(0, X.size());

	for (int i = 0; i < X.size(); i++)
	{
		h = X.at(i) + h;
		C.at(i) = int()(h / frameTime);
	}

	return C;
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

void ScenarioA::runProtocol(std::vector<int> Ca, std::vector<int> Cc) {

	int backOffA = 0;
	int backOffC = 0;
	int dataNumSlots = 100;
	int DIFS = 2;
	int SIFS = 1;
	int ACK = 2;

	this->slotCount;
	while (!Ca.empty() && !Cc.empty());
	{
		if (Ca.at(0) < Cc.at(0))
		{
			this->slotCount = Ca.at(0);
			backOffA = backoffGen(4, 1024, this->numConcurrentColl);
			this->slotCount = this->slotCount + DIFS + backOffA + dataNumSlots + SIFS + ACK;
		}
		else if (Ca.at(0) > Cc.at(0))
		{
			this->slotCount = Ca.at(0);
			backOffC = backoffGen(4, 1024, this->numConcurrentColl);
			this->slotCount = this->slotCount + DIFS + backOffC + dataNumSlots + SIFS + ACK;
		}
		else
		{
			this->slotCount = Ca.at(0);
			backOffA = backoffGen(4, 1024, this->numConcurrentColl);
			backOffC = backoffGen(4, 1024, this->numConcurrentColl);

			if (backOffA < backOffC)
			{
				backOffC = backOffC - backOffA;
				this->slotCount += backOffA;
			}
			else if (backOffA > backOffC)
			{
				backOffA = backOffA - backOffC;
				this->slotCount += backOffC;
			}
			else
			{
				this->numConcurrentColl++;
				this->slotCount += backOffA;
			}

		}
	}
}