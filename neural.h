#ifndef NEURAL_H
#define NEURAL_H

#include <iostream>
#include <string>
#include "network.h"

struct inNeuron
{
	float *x;
	float *error;
	float *weight;
	Neural * nptr;
};

struct midNeuron
{
	float *x;
	float *error;
	float *weight;
	Neural * nptr;

};

struct outNeuron
{
	float *x;
	float *error;
	float *weight;
	Neural * nptr;

};

class Neural : public Network
{
public:
	Neural();
	~Neural();
	float loadInput();
	////float geterror();
	//float getweights();
	//void setx();

	int y;
protected:
	//float *x;
	//float *error;
	//float *weights;
	//Neural * nptr;
	Network * netptr;
	//float Normalize(float *x); // or Neural *neuronptr?
	//float findMin();
	//float findMax();
	inNeuron * inptr;
	midNeuron * midptr;
	outNeuron * outptr;

};

#endif  //NEURAL_H
