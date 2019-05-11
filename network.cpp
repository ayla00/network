#include "network.h"
#include "neural.h"

Network::Network()
{
	iopairs = 0;
	//on = setConfig(value);
	std::cout << "DEFAULT CONSTRUCTOR \n";
	displayVariables();
}

Network::Network(int pairs, int nodes, int innode, int hidnode, int outnode, float natexp, float lrate)
{
	std::cout << "parametrized CONSTRUCTOR \n";
	iopairs = pairs;
	column = nodes;
	inNodes = innode;
	hidNodes = hidnode;
	outNodes = outnode;
	ee = natexp;
	lr = lrate;
	displayVariables();
}

Network::~Network()
{
	//std::cout << "you are out of network\n";
	//delete neuronptr;
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

float Network::randomWeights()
{
	std::cout << "iopairs " << iopairs << std::endl;
	float randomnum;
	//std::vector<float> randomweights;
	//for (int i = 0; i < (iopairs / 2); i++)
	//{
		
		do {
			do
			{
				randomnum = (static_cast<float> (-10 + rand() % 30)) / (static_cast<float> (1 + rand() % 15));
			} while (randomnum <= -1.0); //((randomnum < -1.0) || (randomnum > 1.0))
		} while (randomnum >= 1.0);

		//this may give more variety of numbers
		//may be obsolete, test how values come out using old and new definitions of function
		if ((randomnum <= 1.0) && (randomnum >= -1.0))
			return randomnum;
		else
		{
			//this makes sure every weight gets an assingment if something filtered through other loop,
			//also makes sure it's a weight less than 1
			randomnum = (static_cast<float> (-1 + rand() % 3)) / (static_cast<float> (1 + rand() % 5));
			return randomnum;
		}

	//}
	//return randomweights;
}

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

	iopairs = iopairs + 1;
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
		hidNodes = value;
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
	std::cout << "h units " << hidNodes << std::endl;
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
			std::cout << "input " << *(*(inputData + j) + k) << std::endl;
		}

	}

	for (int j = 0; j < 4; j++)
	{
		if (outNodes > 1)
		{
			for (int k = 0; k < 2; k++)
			{
			std::cout << "output " << *(*(outputData + j) + k) << std::endl;
			}
		}
		else
			std::cout << "output " << *(*(outputData + j)) << std::endl;

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

void Network::loadLayers()
{
	std::cout << "you are in loadLayers\n";
	std::cout << "in Nodes " << inNodes << std::endl;
	displayVariables();
	std::cout << "before derived\n";
	Neural neural(iopairs, column, inNodes, hidNodes, outNodes, ee, lr);
	std::cout << "after derived\n";
	//Network &node = neural;
	//maybe delete the inNodes parameter form inputLayer as it is being sent in the constructor
	neural.inputLayer(inputData, outputData);
	neural.hiddenLayer();
}

void Network::setInputRow(int num)
{
	row = num;
}

int Network::getInputRow()
{
	return row;
}






/*
std::vector<float> Network::randomWeights()
{
	std::cout << "iopairs " << iopairs << std::endl;

	float randomnum;
	std::vector<float> randomweights;
	for (int i = 0; i < (iopairs / 2); i++)
	{
		//this gives more variety of numbers
		do
		{
			randomnum = (static_cast<float> (-10 + rand() % 30)) / (static_cast<float> (1 + rand() % 15));
		} while ((randomnum < -1.0) || (randomnum > 1.0));

		if ((randomnum <= 1.0) && (randomnum >= -1.0))
		{
			randomweights.push_back(randomnum);
			std::cout << randomweights.at(i) << std::endl;
		}
		else
		{
			//this makes sure every weight gets an assingment if something filtered through other loop,
			//also makes sure it's a weight less than 1
			randomnum = (static_cast<float> (-1 + rand() % 3)) / (static_cast<float> (1 + rand() % 5));
			randomweights.push_back(randomnum);
			std::cout << randomweights.at(i) << std::endl;
		}

	}
	return randomweights;
}
*/