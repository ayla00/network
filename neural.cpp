#include "neural.h"

Neural::Neural()
{
	//innodes = nodes;
	//Neural nnet;
	//Network();
	//netptr = new Network;
	std::cout << "test " << test << std::endl;
	in = new inNeuron[2]; //make this dynamic
	//in[2].x = new float[4];
	//nptr = new Neural;
}

Neural::~Neural()
{
	//delete netptr;
	//netptr = nullptr;

	//delete nptr;
	//nptr = nullptr;
}

void Neural::getInput(int inNodes, float **inputData, float**outputData)
{
	//in = new inNeuron[2];


	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 2; k++) //make this dynamic
		{
			std::cout << "for loop\n";
			(in + k)->x = new float[4];

			(in + k)->x[j] = *(*(inputData + j) + k);
			std::cout << "making sure " << (in + k)->x[j] << std::endl;

		}
	}

	for (int j = 0; j < 4; j++)
	{

		for (int k = 0; k < 2; k++) //make this dynamic
		{
			std::cout << "testin display\n";
			std::cout << (in + k)->x[j] << std::endl;

		}
	}

	display(in->x); //erase this 
}

void Neural::display(float * values)
{
	std::cout << "you are in display\n";
	std::cout << "in Nodes " << inNodes << std::endl;
	for (int j = 0; j < 4; j++)
	{
		//for (int k = 0; k < 2; k++) //make this dynamic
		std::cout << "input " << values[j] << std::endl;
	}
}

void Neural::getWeights(std::vector<float> weights)
{
	std::cout << "in Nodes " << inNodes << std::endl;
	std::cout << "you are in getInput\n";
	in->weight = new float[inNodes];


	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < inNodes; k++) //make this dynamic
		{

			*(in->weight + j) = weights.at(j);
		}


	}

	display(in->weight); //erase this 
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