#ifndef NEURAL_H
#define NEURAL_H

#include <iostream>
#include <string>
#include "network.h"

class Neural
{
public:
	Neural(float **inputvalues);
	~Neural();
	float getx();
	float geterror();
	float getweights();
	void setx();

	int y;
protected:
	float *x;
	float *error;
	float *weights;
	Neural * nptr;
	Network *netptr;
	//float Normalize(float *x); // or Neural *neuronptr?
	//float findMin();
	//float findMax();

};

#endif  //NEURAL_H
