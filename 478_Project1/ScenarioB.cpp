#include "ScenarioB.h"



ScenarioB::ScenarioB()
{
    this->slotCount = 0;
    this->numConcurrentColl = 0;
    this->nodeACollisions = 0;
    this->nodeASuccesses = 0;
    this->nodeCCollisions = 0;
    this->nodeCSuccesses = 0;
}

std::vector<int> ScenarioB::generateFrameVals(double frameTime, int lambda) {
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

void ScenarioB::testRandomValues(double frameTime, int lambda) {
    printVec(generateFrameVals(frameTime, lambda));
}

void ScenarioB::runProtocol(std::vector<int> Ca, std::vector<int> Cc) {
    
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
        if(Ca.at(0) > Cc.at(0) && Ca.at(0) < Cc.at(0) + dataNumSlots + DIFS + SIFS + ACK + backOffC)
        {
            this->nodeACollisions++;
            this->nodeCCollisions++;
            Ca.erase(Ca.begin());
            Cc.erase(Cc.begin());
        }
        else if(Cc.at(0) > Ca.at(0) && Cc.at(0) < Ca.at(0) + dataNumSlots + DIFS + SIFS + ACK + backOffA)
        {
            this->nodeCCollisions++;
            this->nodeACollisions++;
            Ca.erase(Ca.begin());
            Cc.erase(Cc.begin());
        }
        else
        {
            if(Ca.at(0) < Cc.at(0))
            {
                this->nodeASuccesses++;
                Ca.erase(Ca.begin());
            }
            else
            {
                this->nodeCSuccesses++;
                Cc.erase(Cc.begin());
            }
        }
    }
}
