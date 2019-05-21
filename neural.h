/*
Name: Astrid Lozano
Assignment: fINAL pROJECT

NOTES:
* the sample output and weights are produced by running the test() function and will be found in the same file where code
is stored
//reading any file assumes the format is the same for all incoming files (including variable names)
//for some reason there is one more space in the file that this code cannot deal with
//the weights are from current layer to next layer
// it is assumed that the hidden layer has the same or more layers than input layer
// it is assummed a bias will always be included
// the output is provided  for view in output file, the function returns a vector so it can be used/displayed differently if necessary
getWeight(), storedWeights, and getsetWeights():
	//weight file has the following info (only data, no strings)
	//arranged in the following order:
	//the savedWeights pointer has the from layer, node at from layer, node at to layer, and weight
	//however, it will be assumed that correct info for number of nodes is given and matches the info
	//in the file, so this simplifies its extraction, however, the whole info should be extracted just to verify
//the network can extract info froma file that includes four parameters in this order: layer weight is
from (1 = in, 2 = hidden), node the weight is from, node the weight is goiong to, and the weight AND has no other stuff but
the #s in it AND has the name "neuralweigth.txt"
*/


#ifndef NEURAL_H
#define NEURAL_H

//#include "network.h"
#include <math.h>
#include <vector>
#include <stdlib.h> //library where rand is located
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>


struct Neuron
{
	float* x;
	float* error;
	float* weight;
};


class Neural
{
public:
	Neural(int pairs, int nodes, int innode, int hidnode, int outnode, float natexp, float lrate, int mepoch, float onvar, float offvar);
	~Neural();


	void setWeights();
	void inputLayer(float** inputData, float** outputData);
	void hiddenLayer();
	void outputLayer();
	void display(int nodes, Neuron* nptr);
	void calculateError(float** outputData);
	void adjustWeights();
	std::vector<float*> saveWeights();
	float** saveOuput();
	void getsetWeights(float** weights);
	void displayVector();
	float getMSError();

protected:
	void allocatePointers();
	void setInput(float** inputData);
	float randomWeights();
	void rWeights(int current, int next, Neuron* layer);
	void setotherInput(int nodes, Neuron* layer);
	void sumInputs(int current, int next, Neuron* layer);
	void activation(int nodes, Neuron* layer);
	void error(int nodes, Neuron* layer, float** outputData);
	void backErrors(int back, int next, Neuron* backlayer, Neuron* nextlayer);
	void backWeights(int back, int next, Neuron* backlayer, Neuron* nextlayer);
	void pushWeights(Neuron* from, Neuron* to);
	//add a functionto empty these vectors before start of next train epoch
	std::vector<float> adjweightStack;
	//to be used in getsetWeights
	const int INLAYER = 1;
	const int HIDLAYER = 2;
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
	float** y;
	int* hiddenArray;
	std::vector<float*> runweights;
	const int BIAS = 1;
	const float BIASVALUE = 1.0;
	//std::vector<float> finalWeights;
	//float Normalize(float *x); // or Neural *neuronptr?
	//float findMin();
	//float findMax();
	const int ROW = row;
	Neuron* in;
	Neuron* hid;
	Neuron* out;
	int innodes;
	float** sumtotal;
	float** sigmoid;
	float* value;//array to put saved weights w/ layer and node info
	const int WPARAMETER = 4;
	//different purpose than sumtotal, so want to keep them separate
	float* sum;
	float meansqError;


};

#endif  //NEURAL_H


