/*
Name: Astrid Lozano
Assignment: fINAL project

NOTES:
//reading any file assumes the format is the same for all incoming files (including variable names)
//for some reason there is one more space in the file that this code cannot deal with
*/


#include "network.h"
#include "neural.h"

Network::Network()
{
	iopairs = 0;
	displayVariables();
}

Network::Network(int pairs, int nodes, int innode, int hidnode, int outnode, float natexp, float lrate, int wfile)
{
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

void Network::train()
{
	//load input
	Neural neural(iopairs, column, inNodes, hidNodes, outNodes, ee, lr, weightfile);

	//sends input
	neural.inputLayer(inputData, outputData);

	neural.setWeights();


	for (int epoch = 0; epoch < 100; epoch++)
	{

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

void Network::testnetwork()
{
	//load empty network
	Neural neural(iopairs, column, inNodes, hidNodes, outNodes, ee, lr, weightfile);
	std::ifstream wfile;
	std::string file = "neuralweight.txt";

	//gets weight file or sets up random weights
	if (weightfile == 1)
		getWeights(wfile, file);
	else
		neural.setWeights();

	//feed forward
	neural.inputLayer(inputData, outputData);
	neural.hiddenLayer();
	neural.outputLayer();

	//get out put
	neural.calculateError(outputData);
	writeWeight(neural.saveWeights());
	writeOutput(neural.saveOuput());

}

void Network::run()
{
	//load empty network
	Neural neural(iopairs, column, inNodes, hidNodes, outNodes, ee, lr, weightfile);
	std::ifstream wfile;
	std::string file = "neuralweight.txt";

	//gets weight file or sets up random weights
	if (weightfile == 1)
		getWeights(wfile, file);
	else
		neural.setWeights();

	//feed forward
	neural.inputLayer(inputData, outputData);
	neural.hiddenLayer();
	neural.outputLayer();

	//get out put
	writeWeight(neural.saveWeights());
	writeOutput(neural.saveOuput());
}



float Network::randomWeights()
{

	float randomnum;

	do {
		do
		{
			randomnum = (static_cast<float> (-10 + rand() % 30)) / (static_cast<float> (1 + rand() % 15));
		} while (randomnum <= -1.0);
	} while (randomnum >= 1.0);


	return randomnum;
}

void Network::loadInput(int inrow, int incolumn, float value)
{

	if ((inrow == 0) && (incolumn == 0))
	{
		inputData = new float*[(row / 2)];
		inputData[inrow] = new float[2];//make this dynamic next
	}
	else if ((inrow != 0) && (incolumn == 0))
	{
		inputData[inrow] = new float[2];
	}

	iopairs = iopairs + 1;

	*(*(inputData + inrow) + incolumn) = value;


}

void Network::loadOutput(int inrow, int incolumn, float value)
{


	if ((inrow == 0) && (incolumn == 0))
	{
		outputData = new float*[(row / 2)];
		outputData[inrow] = new float[1]; //make this dynamic next, size of array is determined here, must be set at very beginning, no update
	}
	else if ((inrow != 0) && (incolumn == 0))
	{
		outputData[inrow] = new float[1];

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
	else if (constname == "WEIGHTFILE")
		weightfile = value;
	else
		return false;

	return returnvalue; //maybe just return true here instead of using variable
}

float **Network::getWeights(std::ifstream &wFile, std::string weightData)
{

	std::string inputdata = "";
	std::string datachunk = "";
	int columncount = 0;
	int rowcount = 0;
	int row = 0;
	int column;

	wFile.open(weightData);

	if ((wFile.is_open()))
	{

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

							float firstinput = std::stof(trickextract, &sz);
							float dummyfloat = std::stof(trickextract.substr(sz));

							datachunk = "";
							(*(*(storedWeights + row) + column)) = firstinput;
							column++;

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
	return storedWeights;
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

/*void Network::displayInput()
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
}*/


void Network::setInputColumn(int num)
{
	column = num;
}

void Network::loadLayers()
{
	Neural neural(iopairs, column, inNodes, hidNodes, outNodes, ee, lr, weightfile);

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


	int vectSize = neuralWeights.size();
	if (outputFile.is_open())
	{
		for (int index = 0; index < vectSize; index++)
		{

			value = neuralWeights.at(index);
			outputFile << value[0] << ' ' << value[1] << ' ' << value[2] << ' ' << value[3] << std::endl;
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

	if (outputFile.is_open())
	{
		for (int row = 0; row < (iopairs / 2); row++)
		{
			for (int column = 0; column < outNodes; column++)
			{

				value = (*(*(neuralOutput + row) + column));

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




