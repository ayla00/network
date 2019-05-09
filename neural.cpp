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
	//inNeuron inn[2];
	//in = 
	//(in + 2)->x = new float[4];

		for (int k = 0; k < 2; k++) //make this dynamic
		{

			//this place is the only definition that will let this work
			(in + k)->x = new float[4];

			for (int j = 0; j < 4; j++)
			{

				(in + k)->x[j] = *(*(inputData + j) + k);
				std::cout << "values " << (in + k)->x[j] << std::endl;
			}


		}


	display(in->x); //erase this 
}
/*
void Neural::display(float * values)
{
	std::cout << "you are in display\n";
	std::cout << "in Nodes " << inNodes << std::endl;
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 2; k++) //make this dynamic
			std::cout << "input " << values[j][k] << std::endl;
	}
}
*/


void Neural::getWeights(std::vector<float> weights)
{
	std::cout << "in Nodes " << inNodes << std::endl;
	std::cout << "you are in getInput\n";
	//in->weight = new float[inNodes];


	
		//in->weight = new float[inNodes];
		for (int k = 0; k < inNodes; k++) //make this dynamic
		{
			(in + k)->weight = new float[inNodes];
			for(int j = 0; j < 4; j++)
				(in + k)->weight[j] = weights.at(j);
		}
	
		for (int k = 0; k < inNodes; k++) //make this dynamic
		{
			//(in + k)->weight = new float[inNodes];
			for (int j = 0; j < 4; j++)
				std::cout << "weights " << (in + k)->weight[j];
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