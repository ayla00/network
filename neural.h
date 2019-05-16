/*
Name: Astrid Lozano
Assignment: fINAL pROJECT

NOTES:
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
*/


#ifndef NEURAL_H
#define NEURAL_H

#include "network.h"


struct Neuron
{
	float* x;
	float* error;
	float* weight;
	//Neural * nptr;
};


class Neural : public Network
{
public:
	Neural(int pairs, int nodes, int innode, int hidnode, int outnode, float natexp, float lrate, int wfile);
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

protected:
	void allocatePointers();
	void setInput(float** inputData);
	void rWeights(int current, int next, Neuron* layer);
	void setotherInput(int nodes, Neuron* layer);
	void sumInputs(int current, int next, Neuron* layer);
	void activation(int nodes, Neuron* layer);
	void error(int nodes, Neuron* layer, float** outputData);
	void backErrors(int back, int next, Neuron* backlayer, Neuron* nextlayer);
	void backWeights(int back, int next, Neuron* backlayer, Neuron* nextlayer);
	void pushWeights(Neuron* from, Neuron* to);
	Network* netptr;
	float** y;
	std::vector<float*> runweights;
	const int BIAS = 1;
	const float BIASVALUE = 1.0;
	//float Normalize(float *x); // or Neural *neuronptr?
	//float findMin();
	//float findMax();
	const int ROW = row;
	Neuron* in;
	Neuron* hid;
	Neuron* out;
	int innodes;
	//these will have to be adapted for different input
	//float sumtotal[4][3];
	float ** sumtotal;
	//float sigmoid[4][3];
	float ** sigmoid;
	float* value;//array to put saved weights w/ layer and node info
	const int WPARAMETER = 4;
	//different purpose than sumtotal, so want to keep them separate
	float **sum;


};



#endif  //NEURAL_H


