#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "neural.h"
//#include "midneuron.h"
//#include "inneuron.h"


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
	void loadInput(int inrow, int incoloumn, float value);
	void loadOutput(int inrow, int incolumn, float value);
	bool setConfig(std::string constname, float value);
	void displayVariables();
	void displayInput();
	//bool setInArrayNumbers(int inrow, int incolumn);
	void setInputRow(int num);
	int getInputRow();
	void setInputColumn(int num);
	//inNeuron * inptr;

protected:
	void inputLayer();
	//void outputLayer();
	//void middleLayer();
	//Neural ** neuronptr;
	Neural * nnptr; //has same name as a pointer in Neural, change it
	//inNeuron * inptr;
	int row;
	int column;
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
