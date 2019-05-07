#include "network.h"

Network::Network()
{
	nnptr = new Neural;
	//on = setConfig(value);
	//neuronptr = new Neural*[3];
}

Network::~Network()
{
	std::cout << "you are out of network\n";
	//delete[] nnptr;
	//nnptr = nullptr;
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

void Network::loadInput(int inrow, int incolumn, float value)
{
	if ((inrow == 0) && (incolumn == 0))
	{
		inputData = new float*[(row / 2)];
		inputData[inrow] = new float[2];//make this dynamic next
		std::cout << "row 1 " << inrow << std::endl;
		std::cout << "col " << incolumn << std::endl;
		std::cout << "value " << value << std::endl;
	}
	else if ((inrow != 0) && (incolumn == 0))
	{
		std::cout << "you are else if assing\n";
		inputData[inrow] = new float[2];
	}

	//std::cout << "row 1 " << inrow << std::endl;
	//std::cout << "col " << incolumn << std::endl;
	//std::cout << "pointer value " << *((inputData + inrow) + incolumn) << std::endl;
	*(*(inputData + inrow) + incolumn) = value;
	//std::cout << "value " << value << *(*(inputData + inrow) + incolumn) << std::endl;

}

void Network::loadOutput(int inrow, int incolumn, float value)
{
	std::cout << "you are in load output\n";
	//std::cout << "row 1 " << inrow << std::endl;
	//std::cout << "col " << incolumn << std::endl;
	//std::cout << "value " << value << std::endl;
	if ((inrow == 0) && (incolumn == 0))
	{
		//std::cout << "you are in if loadoutput\n";
		outputData = new float*[(row / 2)];
		outputData[inrow] = new float[1]; //make this dynamic next, size of array is determined here, must be set at very beginning, no update
		//std::cout << "row 1 " << inrow << std::endl;
		//std::cout << "col " << incolumn << std::endl;
		//std::cout << "value " << value << std::endl;
	}
	else if ((inrow != 0) && (incolumn == 0))
	{
		//std::cout << "you are else if assing\n";
		outputData[inrow] = new float[1]; //make this dynamic next,
		//inputData[inrow] = new float[incolumn];
	}

	*(*(outputData + inrow) + incolumn) = value;

}


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

void Network::displayInput()
{
	float value;
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 2; k++)
		{
			//value = *(*(inputData + j) + k);
			std::cout << "input " << *(*(inputData + j) + k) << std::endl;// *((inputData + j) + k); //if this won't work, try *inputData[][]
		}

	}

	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 2; k++)
		{
			std::cout << "output " << *(*(outputData + j) + k) << std::endl;// *((inputData + j) + k); //if this won't work, try *inputData[][]
		}

	}
}

/*
bool Network::setInArrayNumbers(int inrow, int incolumn)
{
	row = inrow;
	column = incolumn;
	return false;
}
*/
void Network::setInputColumn(int num)
{
	column = num;
}

void Network::setInputRow(int num)
{
	row = num;
}

int Network::getInputRow()
{
	return row;
}


void Network::inputLayer()
{
	nnptr = new Neural[inNodes];

	//nnptr->inNeuron.x;
	/*
	for (int j = 0; j < inNodes; j++)
	{
		for (int k = 0; k < 2; k++)//make dynamic
		{
			*(nnptr + j)-> // *((inputData + j) + k); //if this won't work, try *inputData[][]
		}

	}
	*/
}
