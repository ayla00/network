#ifndef NEURAL_H
#define NEURAL_H

#include "network.h"
/*
struct inNeuron
{
	//std::vector<float*> x;
	float* x;
	float* error;
	float* weight;
	//Neural * nptr;
};

struct hidNeuron
{
	float* x;
	float* error;
	float* weight;
	//Neural * nptr;

};

struct outNeuron
{
	float* x;
	float* error;
	float* weight;
	//Neural * nptr;
};*/

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
	Neural(int pairs, int nodes, int innode, int hidnode, int outnode, float natexp, float lrate);// : Network() {};
	~Neural();

	void display(Neuron* nptr);
	////float geterror();
	//void setWeights(std::vector<float> weights);
	//float randomWeights();
	//void setWeights();
	void inputLayer(float** inputData, float** outputData);
	void hiddenLayer();
	//void activation();
	void hiddenActivation();
	int y;
protected:
	//void setInput(float **inputData, float **outputData);
	//*nodeLayer will be in->x, mid->x, or out->x
	void allocatePointers();
	void setInput(float** inputData);
	void setWeights(Neuron* layer);
	void setotherInput(Neuron* layer);
	void sumInputs(Neuron* layer);
	//void sumInputs(float *actnodeLayer, float * weightnodeLayer);
	//Neural * nptr;
	//float sigmoid;
	Network* netptr;
	//float Normalize(float *x); // or Neural *neuronptr?
	//float findMin();
	//float findMax();
	//inNeuron* in;
	//hidNeuron* hid;
	//outNeuron* out;
	Neuron* in;
	Neuron* hid;
	Neuron* out;
	int innodes;
	//template <struct> T;
	float sumtotal[4][2];
	float sigmoid[4][2];

};






#endif  //NEURAL_H

