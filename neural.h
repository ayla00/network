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
	Neural(int pairs, int nodes, int innode, int hidnode, int outnode, float natexp, float lrate);// : Network() {};
	~Neural();

	void display(Neuron* nptr);
	////float geterror();
	void inputLayer(float** inputData, float** outputData);
	void hiddenLayer();
	void outputLayer();
	int y;
protected:
	//void setInput(float **inputData, float **outputData);
	//*nodeLayer will be in->x, mid->x, or out->x
	void allocatePointers();
	void setInput(float** inputData);
	void setWeights(int nodes, Neuron* layer);
	void setotherInput(int nodes, Neuron* layer);
	void sumInputs(int current, int next, Neuron* layer);
	void activation(int nodes, Neuron* layer);
	//float sigmoid;
	Network* netptr;
	//float Normalize(float *x); // or Neural *neuronptr?
	//float findMin();
	//float findMax();
	Neuron* in;
	Neuron* hid;
	Neuron* out;
	int innodes;
	//these will have to be adapted for different input
	float sumtotal[4][2];
	float sigmoid[4][2];

};



#endif  //NEURAL_H

