/*
Name: Astrid Lozano
Assignment: fINAL pROJECT

NOTES:
//reading any file assumes the format is the same for all incoming files (including variable names)
//for some reason there is one more space in the file that this code cannot deal with
//the weights are from current layer to next layer
// it is assumed that the hidden layer has the same or more layers than input layer
// it is assummed a bias will always be included
// the output is provided  for view in output file, the function returns a vector so it can be used/displayed differently if necessary
getWeight(), storedWeights, and getsetWeights():
	//weight file has the following info (only data, no strings)
	//arranged in the following order:
	//the savedWeights pointer has the from layer, node at from layer, node at to layer, and weight
	//however, it will be assumed that correct info for number of nodes is given and matches the info
	//in the file, so this simplifies its extraction, however, the whole info should be extracted just to verify
*/

#include "network.h"
#include "neural.h"

Network::Network()
{
	iopairs = 0;

}

Network::Network(int pairs, int nodes, int innode, int hidnode, int outnode, float natexp, float lrate, int wfile)
{
	iopairs = pairs;
	row = pairs / 2;
	column = nodes;
	inNodes = innode;
	hidNodes = hidnode;
	outNodes = outnode;
	ee = natexp;
	lr = lrate;

}


Network::~Network()
{
	//std::cout << "you are out of network\n";
}

void Network::train()
{

	//load input
	Neural neural(iopairs, column, inNodes, hidNodes, outNodes, ee, lr, weightfile);

	std::ifstream wfile;
	std::string file = "neuralweight.txt";
	//sends input
	neural.inputLayer(inputData, outputData);


	//gets weight file or sets up random weights
	//getWeights in Network opens a file and puts weights in a vector, which is sent to getsetWeights in Neural to assign them
	if (weightfile == 1)
		neural.getsetWeights(getWeights(wfile, file));
	else
		neural.setWeights();

	for (int epoch = 0; epoch < maxEpoch; epoch++)
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

	//gets weight file 
	//if the network can have different nodes and # of layers, hardcoding them in neural class
	//would not be efficient, so it is assumed that once the neural network is ready, it will
	//always upload weights
	neural.getsetWeights(getWeights(wfile, file));

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
		neural.getWeights(wfile, file);
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
		inputData = new float* [(row / 2)];
		inputData[inrow] = new float[2];
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
		outputData = new float* [(iopairs / 2)];
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

float** Network::getWeights(std::ifstream & wFile, std::string weightData)
{

	std::string inputdata = "";
	std::string datachunk = "";
	int columncount = 0;
	int rowcount = 0;
	int row = 0;
	int column = 0;

	wFile.open(weightData);

	if ((wFile.is_open()))
	{

		while (getline(wFile, inputdata))
		{
			if (!inputdata.empty())
				rowcount = rowcount + 1; //so it counts before next function is called
			else
				rowcount = rowcount;
		}

		wFile.clear(); //needed so file can be read again
		wFile.seekg(0); //returns file position to 0 to be read again
		inputdata = "";
		storedWeights = new float* [rowcount];

		for (int p = 0; p < rowcount; p++)
		{
			*(storedWeights + p) = new float[WPARAMETER];

		}

		while (getline(wFile, inputdata) && !wFile.eof())
		{

			int i = 0;
			const int LINESIZE = inputdata.size();
			//reads number of lines & takes care of emtpy lines as well, except eof
			if (!weightData.empty())
			{
				while (i < LINESIZE)
				{
					std::cout << inputdata << std::endl;
					if ((inputdata[i] != ' ') && ((i + 1) < LINESIZE))
					{

						datachunk += inputdata[i];
						i++;
					}
					else if ((i + 1) == LINESIZE)
					{

						datachunk += inputdata[i];

						std::string dummystring = " 2.5";
						std::string trickextract = inputdata + dummystring;
						std::string::size_type sz;     // alias of size_t

						float firstinput = std::stof(trickextract, &sz);
						float dummyfloat = std::stof(trickextract.substr(sz));
						std::cout << "r " << row << "col " << column << std::endl;
						(*(*(storedWeights + row) + column)) = firstinput;
						std::cout << "weight value " << firstinput << " stored value " << (*(*(storedWeights + row) + column)) << std::endl;
						row++;
						column = 0;
						i++;
					}
					else
					{

						i++; //moves past one white space
						//something to make sure there is no more white space should go here, but
						//is ommitted for now, comma delimited conditions also should go somewhere


						std::string dummystring = " 2.5";
						std::string trickextract = datachunk + dummystring;
						std::string::size_type sz;     // alias of size_t
						std::cout << (storedWeights + rowcount) << std::endl;
						float firstinput = std::stof(trickextract, &sz);
						float dummyfloat = std::stof(trickextract.substr(sz));

						//it arranges the info for one weight in a row (each row is the info for one weight, each colum is a parameter)
						(*(*(storedWeights + row) + column)) = firstinput;
						std::cout << "weight value " << firstinput << " stored value " << (*(*(storedWeights + row) + column)) << std::endl;
						column++;

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

	float* value = new float[ROWS];
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

void Network::writeOutput(float** neuralOutput)
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




