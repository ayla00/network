#include "neural.h"

Neural::Neural(int nodes)
{
	innodes = nodes;
	//Neural nnet;
	//Network();
	//netptr = new Network;
	std::cout << "innodes " << innodes << std::endl;
	//in.x = new float[inNodes];
	//nptr = new Neural;
}

Neural::~Neural()
{
	//delete netptr;
	//netptr = nullptr;

	//delete nptr;
	//nptr = nullptr;
}

void Neural::getInput()
{
	std::cout << "in Nodes " << inNodes << std::endl;
	std::cout << "you are in getInput\n";
	in.x = new float[inNodes];
	for (int k = 0; k < 4; k++)
	{
		for (int j = 0; j < inNodes; j++) //make this dynamic
		{
			*(in.x + k) = *(*(inputData + k) + j);
			std::cout << *(in.x + k) << std::endl;
		}


	}

	display(in.x); //erase this 
}

void Neural::display(float * values)
{
	for (int j = 0; j < inNodes; j++)
	{
		for (int k = 0; k < 4; k++) //make this dynamic
			std::cout << "input " << *(in.x + k) << std::endl;
	}
}
/*
void Neural::setx(Neural *setptr)
{
	setptr->x;
}

/*
float Neural::Normalize(float *x)
{
	return ((*x - findMin()) / (findMax() - findMin()));
}

float Neural::findMin()
{
	float min = x[0];

	for (int j = 1; j < x.size; j++)
	{
		if (min < x[j])
			min = min;
		else
			min = x[j];
	}

	return min;
}

float Neural::findMax()
{
	float max = x[0];

	for (int j = 1; j < x.size; j++)
	{
		if (max > x[j])
			max = max;
		else
			max = x[j];
	}

	return max;
}
*/