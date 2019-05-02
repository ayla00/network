#ifndef NEURAL_H
#define NEURAL_H

#include <iostream>
#include <string>


class Neural
{
public:
	Neural();
	~Neural();

	int y;
protected:
	float *x;
	float *error;
	//void Normalize(Neural * neuronptr);
	//float findMin();
	//float findMax();

};

#endif  //NEURAL_H
