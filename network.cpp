#include "network.h"

Network::Network()
{
	//on = setConfig(value);
	//neuronptr = new Neural*[3];
}

Network::~Network()
{
	std::cout << "you are out of network\n";
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
	bool returnvalue = true;

	if (constname == "ON")
		on = value;
	else if (constname == "OFF")
		off = value;
	else if (constname == "OFFSOFT")
		offSoft = value;
	else if (constname == "ONSOFT")
		onSoft = value;
	else if (constname == "I_UNITS")
		inNodes = value;
	else if (constname == "H_UNITS")
		midNodes = value;
	else if (constname == "O_UNITS")
		outNodes = value;
	else if (constname == "MAX_EPOCH")
		maxEpoch = value;
	else if (constname == "LR")
		lr = value;
	else if (constname == "EE")
		ee = value;
	else
		return false;

	return returnvalue; //maybe just return true here instead of using variable
}

void Network::displayVariables()
{
	std::cout << "on " << on << std::endl;
	std::cout << "off " << off << std::endl;
	std::cout << "offsoft " << offSoft << std::endl;
	std::cout << "onsoft " << onSoft << std::endl;
	std::cout << "i units " << inNodes << std::endl;
	std::cout << "h units " << midNodes << std::endl;
	std::cout << "o units " << outNodes << std::endl;
	std::cout << "max epoch " << maxEpoch << std::endl;
	std::cout << "lr " << lr << std::endl;
	std::cout << "ee " << ee << std::endl;
	
}

void Network::inputLayer()
{
	//nptr = new inNeuron[inNodes];
	//inNeuron(inNodes);
	std::cout << "inNOdes " << inNodes << std::endl;

}
