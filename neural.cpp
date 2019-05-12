#include "neural.h"

Neural::Neural(int pairs, int nodes, int innode, int hidnode, int outnode, float natexp, float lrate)
{

	std::cout << "derived constructor \n";
	displayVariables();
	Network(pairs, nodes, innode, hidnode, outnode, natexp, lrate);

	iopairs = pairs;
	row = iopairs / 2;
	column = nodes;
	std::cout << "nodes " << nodes << std::endl;
	inNodes = innode;
	hidNodes = hidnode;
	outNodes = outnode;
	ee = natexp;
	lr = lrate;
	displayVariables();
	const int INCOLUMNS = inNodes;
	const int HIDCOLUMNS = hidNodes;
	const int OUTCOLUMNS = outNodes;


	in = new Neuron[INCOLUMNS];
	hid = new Neuron[HIDCOLUMNS];
	out = new Neuron[OUTCOLUMNS];

	// this will build empty network
	allocatePointers();
	//nptr = new Neural;
}

Neural::~Neural()
{
	/*for (int i = 0; i < 2; ++i)
	{
		delete[] in[i];
	}
	delete[] in;*/

	delete[] in->x;
	in->x = nullptr;
	delete[] in->weight;
	in->weight = nullptr;
	delete[] in->error;
	in->error = nullptr;
	delete[] in;
	in = nullptr;
	delete[] hid->x;
	hid->x = nullptr;
	delete[] hid->weight;
	hid->weight = nullptr;
	delete[] hid->error;
	hid->error = nullptr;
	delete[] hid;
	hid = nullptr;
	delete[] out->x;
	out->x = nullptr;
	delete[] out->weight;
	out->weight = nullptr;
	delete[] out->error;
	out->error = nullptr;
	delete[] out;
	out = nullptr;
	delete netptr;
	netptr = nullptr;
}

void Neural::inputLayer(float** inputData, float** outputData)
{
	std::cout << "you are in input layers " << std::endl;
	std::cout << "in Nodes " << inNodes << std::endl;
	//setInput used to have inNodes as parameter in case you want to change it from place
	//(back to network), it also used to have outputData
	setInput(inputData);
	setWeights(inNodes, in);
	std::cout << "before \n";
	sumInputs(inNodes, hidNodes, in);

	std::cout << "after \n";
}

void Neural::hiddenLayer()
{
	std::cout << "you are in hidden layers " << std::endl;
	std::cout << "in Nodes " << inNodes << std::endl;

	//setInput used to have inNodes as parameter in case you want to change it from place
	//(back to network), it also used to have outputData
	std::cout << "values before activation \n";
	activation(hidNodes, in);
	//hiddenActivation();
	setotherInput(hidNodes, hid);
	setWeights(hidNodes, hid);
	std::cout << "before \n";
	sumInputs(hidNodes, outNodes, hid);
	std::cout << "after \n";
}

void Neural::outputLayer()
{
	std::cout << "you are in output layers " << std::endl;
	std::cout << "in Nodes " << inNodes << std::endl;

	//setInput used to have inNodes as parameter in case you want to change it from place
	//(back to network), it also used to have outputData
	std::cout << "values before activation \n";
	activation(outNodes, hid);
	setotherInput(outNodes, out);
	setWeights(outNodes, out);
	std::cout << "before \n";
	sumInputs(outNodes, outNodes, out);

	std::cout << "after \n";
}

void Neural::allocatePointers()
{
	//function allocates arrays for use in network
	const int ROWS = iopairs / 2;
	std::cout << "pairs " << ROWS << std::endl;
	std::cout << "allocate " << std::endl;
	displayVariables();
	for (int nodes = 0; nodes < inNodes; nodes++)
	{
		(in + nodes)->x = new float[ROWS];
		(in + nodes)->weight = new float[ROWS];
		(in + nodes)->error = new float[ROWS];
	}

	for (int nodes = 0; nodes < hidNodes; nodes++)
	{
		(hid + nodes)->x = new float[ROWS];
		(hid + nodes)->weight = new float[ROWS];
		(hid + nodes)->error = new float[ROWS];
	}

	for (int nodes = 0; nodes < outNodes; nodes++)
	{
		(out + nodes)->x = new float[ROWS];
		(out + nodes)->weight = new float[ROWS];
		(out + nodes)->error = new float[ROWS];
	}

}

void Neural::setInput(float** inputData)
{
	std::cout << "you are in setInput\n";


	for (int k = 0; k < inNodes; k++)
	{

		for (int j = 0; j < 4; j++)
		{
			(in + k)->x[j] = *(*(inputData + j) + k);

			std::cout << "values " << (in + k)->x[j] << std::endl;
		}
	}

	for (int k = 0; k < 2; k++) //DELETE, JUST DEMO PURPOSES
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << "values " << (in + k)->x[j] << std::endl;
		}
	}


	display(in); //erase this 
}

void Neural::display(Neuron * nptr)
{
	std::cout << "you are in display\n";
	std::cout << "in Nodes " << inNodes << std::endl;
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 2; k++) //make this dynamic
			std::cout << "input " << (nptr + k)->x[j] << std::endl;
	}
}

void Neural::calculateError(float** outputData)
{
	error(outNodes, out, outputData); //errors at ouput layer
	backErrors(hidNodes, outNodes, hid, out); //errors at hidden layer
	backErrors(inNodes, hidNodes, in, hid); //errors at input layer
}

void Neural::error(int nodes, Neuron * layer, float** outputData)
{
	for (int n = 0; n < nodes; n++)
	{
		for (int r = 0; r < 4; r++) //make this dynamic
		{
			(layer + n)->error[r] = sigmoid[r][n] * (1.0 - (sigmoid[r][n])) * ((*(*(outputData + r) + n)));
		}


	}

	for (int n = 0; n < nodes; n++)
	{
		for (int r = 0; r < 4; r++) //make this dynamic
			std::cout << "input " << (layer + n)->error[r] << std::endl;
	}
	//return 0.0f;
}

void Neural::backErrors(int back, int next, Neuron * backlayer, Neuron * nextlayer)
{

	for (int n = 0; n < back; n++)
	{

		for (int r = 0; r < 4; r++)
		{
			//nodes of previous layer
			//will this work if nodes is zero?, will it ever be zero
			for (int layerindex = 0; layerindex < next; layerindex++)
			{
				(backlayer + n)->error[r] += ((nextlayer + layerindex)->error[r]) * ((backlayer + layerindex)->weight[r]);
				std::cout << "total " << sumtotal[r][n] << std::endl;
			}

		}


	}

	for (int n = 0; n < back; n++)
	{
		for (int r = 0; r < 4; r++) //make this dynamic
			std::cout << "errors " << (backlayer + n)->error[r] << std::endl;
	}
}


/*
float Neural::randomWeights()
{
	//netptr->iopairs;
	std::cout << "iopairs " << iopairs << std::endl;//netptr->iopairs << std::endl;
	std::cout << "innodes " << innodes << std::endl;
	float randomnum;
	//std::vector<float> randomweights;
	//for (int i = 0; i < iopairs; i++)
	//{
		//this gives more variety of numbers
		do
		{
			randomnum = (static_cast<float> (-10 + rand() % 30)) / (static_cast<float> (1 + rand() % 15));
		} while ((randomnum < -1.0) || (randomnum > 1.0));

		if ((randomnum <= 1.0) && (randomnum >= -1.0))
		{
			//randomweights.push_back(randomnum);
			//std::cout << randomweights.at(i) << std::endl;
			return randomnum;
		}
		else
		{
			//this makes sure every weight gets an assingment if something filtered through other loop,
			//also makes sure it's a weight less than 1
			randomnum = (static_cast<float> (-1 + rand() % 3)) / (static_cast<float> (1 + rand() % 5));
			return randomnum;
			//randomweights.push_back(randomnum);
			//std::cout << randomweights.at(i) << std::endl;
		}

	//}
	//return randomweights;
}*/


void Neural::setWeights(int current, Neuron * layer)
{

	for (int k = 0; k < current; k++) //make this dynamic
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << "k " << k << "\tj " << j << std::endl;
			(layer + k)->weight[j] = randomWeights();
			std::cout << "weights " << (layer + k)->weight[j] << std::endl;
		}
	}



	for (int k = 0; k < current; k++) //make this dynamic
	{
		for (int j = 0; j < 4; j++)
			std::cout << "weights " << (layer + k)->weight[j] << std::endl;
	}

	std::cout << "about to get out of weights \n" << std::endl;
	//display(in->weight); //erase this 


}

void Neural::setotherInput(int current, Neuron * layer)
{
	std::cout << "you are in setHidInput\n";

	for (int k = 0; k < current; k++) //make this dynamic
	{

		for (int j = 0; j < 4; j++)
		{

			(layer + k)->x[j] = sigmoid[j][k];

			std::cout << "values " << (layer + k)->x[j] << std::endl;

		}
	}

}



void Neural::sumInputs(int current, int previous, Neuron * layer)
{
	std::cout << "you are in sumINputs\n";

	for (int s = 0; s < current; s++)
	{
		for (int w = 0; w < 4; w++)
		{
			sumtotal[w][s] += 0;
		}
	}

	//nodes of current layer
	for (int s = 0; s < current; s++)
	{

		for (int w = 0; w < 4; w++)
		{
			//nodes of previous layer
			//will this work if nodes is zero?, will it ever be zero
			for (int layerindex = 0; layerindex < previous; layerindex++)
			{
				sumtotal[w][s] += ((layer + layerindex)->x[w]) * ((layer + layerindex)->weight[w]);
				std::cout << "total " << sumtotal[w][s] << std::endl;
			}

		}


	}

	//std::cout << "total " << total << std::endl;
	//return total;
}

void Neural::activation(int nodes, Neuron * layer)
{
	std::cout << "you are in act2ivation\n";
	for (int s = 0; s < nodes; s++)
	{
		for (int w = 0; w < 4; w++)
		{
			sigmoid[w][s] = 0;
		}
	}

	for (int s = 0; s < nodes; s++)
	{
		for (int w = 0; w < 4; w++)
		{
			sigmoid[w][s] = (1.0 / (1.0 + pow(ee, -sumtotal[w][s])));
		}
	}
}

/*void Neural::sumInputs(float *actnodeLayer, float * weightnodeLayer)
{
	std::cout << "you are in sumINputs\n";
	//float sumtotal[4][2];
	for (int s = 0; s < 2; s++)
	{
		for (int w = 0; w < 4; w++)
		{
			sumtotal[w][s] += 0;
		}
	}

	for (int s = 0; s < 2; s++)
	{
		for (int w = 0; w < 4; w++)
		{
			sumtotal[w][s] += ((actnodeLayer + s)[w])*((weightnodeLayer + s)[w]);
			std::cout << "sumtotal " << ((actnodeLayer + s)[w])*((weightnodeLayer + s)[w]) << std::endl;
			std::cout << "sumtotal " << sumtotal[w][s] << std::endl;
		}
	}

	//std::cout << "total " << total << std::endl;
	//return total;
}
*/




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

