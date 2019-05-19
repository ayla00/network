/*
Name: Astrid Lozano
Assignment: fINAL pROJECT

NOTES:
//reading any file assumes the format is the same for all incoming files (including variable names)
// the weights are from current layer to next layer
// it is assumed that the hidden layer has the same or more layers than input layer
// it is assummed a bias will always be included
// the output and weights are provided  for view in separate output files, the function returns a vector
// so it can be used/displayed differently if necessary getWeight(), storedWeights, and getsetWeights():
	//weight file has the following info (only data, no strings)
	//arranged in the following order:
	//the savedWeights pointer has the from layer, node at from layer, node at to layer, and weight
	//however, it will be assumed that correct info for number of nodes is given and matches the info
	//in the file, so this simplifies its extraction, however, the whole info should be extracted just to verify
	Notes: cannot create a pointer to derived class here, compiler gives memory
access violation when it tries to run; if a pointer is created in cpp file, and the
pointer is declared as derived class, it won't grab the function from derived class
//the network can extract info froma file that includes four parameters in this order: layer weight is
from (1 = in, 2 = hidden), node the weight is from, node the weight is goiong to, and the weight AND has no other stuff but
the #s in it AND has the name "neuralweigth.txt"
*/

#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <vector>
#include <stdlib.h> //library where rand is located
#include <stdio.h>
#include <time.h>
#include <cstring>
#include "neural.h"

class Network
{
public:
	Network();
	Network(int pairs, int nodes, int innode, int hidnode, int outnode, float natexp, float lrate, int wfile);
	~Network();
	void train();
	void testnetwork();
	void run();
	//void weights();
	//void loadweights();
	float randomWeights();
	void loadInput(int inrow, int incoloumn, float value);
	void loadOutput(int inrow, int incolumn, float value);
	bool setConfig(std::string constname, float value);
	float** getWeights(std::ifstream& wFile, std::string weightData);
	void displayVariables();
	//void displayInput();
	//bool setInArrayNumbers(int inrow, int incolumn);
	void setInputRow(int num);
	int getInputRow();
	void setInputColumn(int num);
	void loadLayers();
	Network* net;


protected:
	//void feedForward();
	//void backPropagate();
	int iopairs;
	int row = iopairs / 2;
	int column;
	int inNodes;
	int hidNodes;
	int outNodes;
	int maxEpoch;
	int weightfile;
	float on;
	float off;
	float offSoft;
	float onSoft;
	float lr;
	float ee;
	float netsqError;
	float** inputData;
	float** outputData;
	void writeWeight(std::vector<float*> neuralWeights);
	void writeOutput(float** neuralOutput);
	const int OUTPUTFILE = -1111111;
	const int FILENOTOPEN = -2222222;
	const int EMPTYFILE = -3333333;
	float** storedWeights;
	const int WPARAMETER = 4;

};

#endif  //NETWORK_H
