/*

NOTES:
//reading any file assumes the format is the same for all incoming files (including variable names)
*/


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
	//storedWeights = new float*[;

}

Network::~Network()
{
	//std::cout << "you are out of network\n";
	//delete neuronptr;
	//neuronptr = nullptr;
}

void Network::train()
{
	//load input
	Neural neural(iopairs, column, inNodes, hidNodes, outNodes, ee, lr);

	//sends input
	neural.inputLayer(inputData, outputData);
	std::cout << "before setting weights\n";
	neural.setWeights();
	std::cout << "after setting weights\n";

	for (int epoch = 0; epoch < 10; epoch++)
	{
		std::cout << "inside training loop\n";
		//feed forward
		neural.hiddenLayer();
		neural.outputLayer();

		//calculate errors
		neural.calculateError(outputData);

		//backpropagate
		neural.adjustWeights();
	}

	writeWeight(neural.saveWeights());
	writeOutput(neural.saveOuput());

}


float Network::randomWeights()
{
	std::cout << "iopairs " << iopairs << std::endl;
	float randomnum;

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

	//return randomweights;
}

void Network::loadInput(int inrow, int incolumn, float value)
{
	std::cout << "you are in loadINput\n";
	std::cout << "column " << column << std::endl;
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
	std::cout << "row 1 " << inrow << std::endl;
	std::cout << "col " << incolumn << std::endl;
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
	std::cout << "value " << value << std::endl;
	std::cout << "value data " << *(*(outputData + inrow) + incolumn) << std::endl;





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

bool Network::getWeights(std::ifstream &wFile, std::string weightData)
{
	//readConfigFile(std::ifstream &cfile, std::string configfile, Network * neta)
	//int linenumber;
	std::string inputdata = "";
	std::string datachunk = "";
	int columncount = 0;
	int rowcount = 0;
	int row = 0;
	int column;

	wFile.open(weightData);

	if ((wFile.is_open()))
	{
		//linenumber = countLines(inputfile);
		//puts file at the beginning again so it can be re-read
		//inputfile.clear();
		while (getline(wFile, inputdata) && !wFile.eof())
		{
			if (!inputdata.empty())
				rowcount = rowcount + 1; //so it counts before next function is called
			else
				rowcount = rowcount;
		}
		wFile.clear(); //needed so file can be read again
		wFile.seekg(0); //returns file position to 0 to be read again
		inputdata = "";
		const int PARAMETERS = 4;//the # of parameters in input file is set
		storedWeights = new float*[rowcount];


		for (int p = 0; p < rowcount; p++)
		{
			storedWeights[rowcount] = new float[PARAMETERS];
		}


		while (getline(wFile, inputdata) && !wFile.eof())
		{
			std::cout << "line " << inputdata << std::endl;
			int i = 0;
			const int LINESIZE = inputdata.size();
			//reads number of lines & takes care of emtpy lines as well, except eof
			if (!weightData.empty())
			{
				while (i < LINESIZE)
				{
					if ((inputdata[i] != ' ') && ((i + 1) < LINESIZE))
					{
						datachunk += inputdata[i];
						i++;
					}
					else if ((i + 1) == LINESIZE)
					{
						//std::cout << extracto[i] << std::endl;
						datachunk += inputdata[i];
						//std::cout << " input " << inputdata << std::endl;
						std::string dummystring = " 2.5";
						std::string trickextract = inputdata + dummystring;
						std::string::size_type sz;     // alias of size_t
						//std::cout << "inputdata " << inputdata << std::endl;

						float firstinput = std::stof(trickextract, &sz);
						float dummyfloat = std::stof(trickextract.substr(sz));

						(*(*(storedWeights + row) + column)) = firstinput;
						row++;
						column = 0;
						i++;
					}
					else
					{

						i++; //moves past one white space
						//something to make sure there is no more white space should go here, but
						//is ommitted for now
						columncount++;
						if (columncount > 0) //first column names parameter type, not needed
						{
							std::string dummystring = " 2.5";
							std::string trickextract = datachunk + dummystring;
							std::string::size_type sz;     // alias of size_t
							std::cout << "inputdata " << datachunk << std::endl;

							float firstinput = std::stof(trickextract, &sz);
							float dummyfloat = std::stof(trickextract.substr(sz));

							datachunk = "";
							(*(*(storedWeights + row) + column)) = firstinput;
							column++;
							//i = LINESIZE;
							//extraccion(i, row, col, extracto, extractdata);
						}
						else
							datachunk = "";
					}
				}

			}
			else
				row = row;
		}


		if (rowcount == 0)
		{
			throw EMPTYFILE;
		}

	}
	else
	{
		throw FILENOTOPEN;
	}

	wFile.close();
	return false;
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
	neural.outputLayer();
}

void Network::writeWeight(std::vector<float*> neuralWeights)
{
	const int ROWS = row;
	std::string character = "";

	float * value = new float[ROWS];
	int count = 0; //this will tell the row number
	std::ofstream outputFile("neuralweight.txt");
	std::cout << "innodes " << inNodes << std::endl;
	std::cout << "hidnodes " << hidNodes << std::endl;
	std::cout << "outnodes " << outNodes << std::endl;

	int vectSize = neuralWeights.size();
	if (outputFile.is_open())
	{
		for (int index = 0; index < vectSize; index++)
		{
			value = neuralWeights.at(index);
			std::cout << "v0 " << std::to_string(value[0]) << std::endl;
			std::cout << "next node " << std::to_string(value[1]) << std::endl;
			std::cout << "next node " << *(value + 2) << std::endl;
			std::cout << "next node " << value[3] << std::endl;
			std::cout << "WEIGHT" << ' ' << value[0] << ' ' << value[1] << ' ' << value[2] << ' ' << value[3] << std::endl;
			outputFile << "WEIGHT" << ' ' << value[0] << ' ' << value[1] << ' ' << value[2] << ' ' << value[3] << std::endl;


		}
	}
	else
		throw OUTPUTFILE;

	outputFile.close();
}

void Network::writeOutput(float ** neuralOutput)
{
	std::string character = "";
	float value;
	std::ofstream outputFile("neuraloutput.txt");

	//might need to pass parameters for row and column limits
	//improve this output
	if (outputFile.is_open())
	{
		for (int row = 0; row < (iopairs / 2); row++)
		{
			for (int column = 0; column < outNodes; column++)
			{

				value = (*(*(neuralOutput + row) + column));
				std::cout << "vallue " << value << std::endl;
				if (column != outNodes - 1)
					character += std::to_string(value) + ' ';
				else
					character += std::to_string(value);
			}


			//improve this output
			outputFile << character << std::endl;
			character = "";
		}
	}
	else
		throw OUTPUTFILE;

	outputFile.close();
}



/*
void Network::feedForward()
{
	errors();
	std::cout << "you are in feedForward()\n";
}

void Network::backPropagate()
{
	std::cout << "you are in backPropagate()\n";
}
*/
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