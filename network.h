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
#include "inneuron.h"


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
	void inputLayer();
	//void outputLayer();
	//void middleLayer();
	//Neural ** neuronptr;
	//Neural *nptr; //has same name as a pointer in Neural, change it
	int inNodes;
	int midNodes;
	int outNodes;
	int maxEpoch;
	float on;
	float off;
	float offSoft;
	float onSoft;
	float lr;
	float ee;
	float **inputData;
	float **outputData;

};

#endif  //NEURAL_H
