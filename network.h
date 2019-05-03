#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <string>
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
	void middleLayer();

private:
	//void inputLayer();
	//void outputLayer();
	//void middleLayer();
	Neural ** neuronptr;


};

#endif  //NEURAL_H
