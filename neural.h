#ifndef NEURAL_H
#define NEURAL_H

#include "network.h"

struct inNeuron
{
	float *x;
	float *error;
	float *weight;
	//Neural * nptr;
};

struct midNeuron
{
	float *x;
	float *error;
	float *weight;
	//Neural * nptr;

};

struct outNeuron
{
	float *x;
	float *error;
	float *weight;
	//Neural * nptr;
};

class Neural : public Network
{
public:
	Neural(int innodes);// : Network() {};
	~Neural();
	void getInput();
	void display(float *values);
	////float geterror();
	//float getweights();
	//void setx();

	int y;
protected:
	//float *x;
	//float *error;
	//float *weights;
	Neural * nptr;
	//Network * netptr;
	//float Normalize(float *x); // or Neural *neuronptr?
	//float findMin();
	//float findMax();
	inNeuron in;
	midNeuron mid;
	outNeuron out;
	int innodes;

};

#endif  //NEURAL_H
