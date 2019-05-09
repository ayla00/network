/*
Notes: cannot create a pointer to derived class here, compiler gives memory
access violation when it tries to run; if a pointer is created in cpp file, and the
pointer is declared as derived class, it won't grab the function from derived class

*/

#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <stdlib.h> //library where rand is located
#include <stdio.h>
#include <time.h> 


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
	//std::vector<float> randomWeights();
	virtual float randomWeights();
	void loadInput(int inrow, int incoloumn, float value);
	void loadOutput(int inrow, int incolumn, float value);
	bool setConfig(std::string constname, float value);
	void displayVariables();
	void displayInput();
	//bool setInArrayNumbers(int inrow, int incolumn);
	void setInputRow(int num);
	int getInputRow();
	void setInputColumn(int num);
	void loadLayers();
	int test;


protected:
	void inputLayer();
	//void outputLayer();
	//void middleLayer();
	//Network *neuronptr;
	//Neural * nnptr; //has same name as a pointer in Neural, change it
	int iopairs;
	int row = iopairs / 2;
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