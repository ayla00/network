#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "neural.h"
#include "midneuron.h"


class Network
{
public:
	Network();
	~Network();
	//void train();
	//void test()
	//void weights();
	//void loadweights();
	//training data set
	//float *input;
	//float *output;
	//void layer();
	//void middleLayer();
	bool setConfig(std::string constname, float value);

private:
	//void inputLayer();
	//void outputLayer();
	//void middleLayer();
	//Neural ** neuronptr;
	float on;

};

#endif  //NEURAL_H
