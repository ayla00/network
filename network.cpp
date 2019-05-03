#include "network.h"

Network::Network()
{
	//on = setConfig(value);
	//neuronptr = new Neural*[3];
}

Network::~Network()
{
	//delete[] neuronptr;
	//neuronptr = nullptr;
}

/*
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
/*
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
*/

bool Network::setConfig(std::string constname, float value)
{
	std::cout << "you are in setCOnfig\n";
	std::cout << "constname" << constname << std::endl;
	if (constname == "ON")
	{
		//THIS IS TEMPORARY WHILE I GET CODE TO CONVERT TO STRING TO FLOAT
		inNodes = 3;
		on = value;
		std::cout << "on " << on << std::endl;
		return true;
	}
	else
		return false;
	//else if (constname == "OFF")
	//	;
//	else if (constname == "OFFSOFT")
	//	setConfig(constvalue);
	//else if (constname == "ONSOFT")
		//setConfig(constvalue);
	//return value;

}

void Network::inputLayer()
{
	//nptr = new inNeuron[inNodes];
	//inNeuron(inNodes);
	std::cout << "inNOdes " << inNodes << std::endl;

}
