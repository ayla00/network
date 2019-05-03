#include "network.h"

Network::Network()
{
	neuronptr = new Neural*[3];
}

Network::~Network()
{
	//delete[] neuronptr;
	//neuronptr = nullptr;
}

void Network::middleLayer()
{
	/*
	neuronptr = new inNeuron;

	for (int j = 0; j < 3; j++)
	{
		(neuronptr + j)->y;
		std::cout << "pointer " << (neuronptr + j) << std::endl;
	}
	*/

	/*
	for (int j = 0; j < 3; j++)
	{
		(neuronptr + j)->y;
		std::cout << "pointer " << (neuronptr + j) << std::endl;
	}
	*/

	//neuronptr = new midNeuron*[6];

	for (int j = 0; j < 3; j++)
	{
			std::cout << " * * * * * * * \n";
			//(neuronptr + j)->y;
			//*(neuronptr + j) = new midNeuron[3];
			*(neuronptr + j) = new Neural[j];
			//((neuronptr[) + k)->y = k + j;
			for (int k = 0; k < 3; k++)
			{
				std::cout << "row " << j << "\tcolumn " << k << std::endl;
				std::cout << "pointer " << &neuronptr[j][k] << std::endl;
				std::cout << "pointer " << ((neuronptr + j) + k) << std::endl;
				std::cout << "pointer " << *((neuronptr + j) + k) << std::endl;
			}

	}

	Neural neural;
	midNeuron mid;
	mid.x;
	neural.x;


}

const float Network::getConfig(const float value)
{
	return value;
}
