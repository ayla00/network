#ifndef NEURAL_H
#define NEURAL_H

#include <iostream>
#include <string>


class Neural
{
public:
	Neural();
	~Neural();
	float getx();
	float geterror();
	float getweights();

	int y;
protected:
	float *x;
	float *error;
	float *weights;
	Neural * nptr;
	//void Normalize(Neural * neuronptr);
	//float findMin();
	//float findMax();

};

#endif  //NEURAL_H
