#include "neural.h"

Neural::Neural(int pairs, int nodes, int innode, int hidnode, int outnode, float natexp, float lrate)
{
	//innodes = nodes;
	//Neural nnet;
	std::cout << "derived constructor \n";
	displayVariables();
	Network(pairs, nodes, innode, hidnode, outnode, natexp, lrate);

	iopairs = pairs;
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

	//in = new inNeuron[INCOLUMNS]; //make this dynamic
	//hid = new hidNeuron[HIDCOLUMNS];
	//out = new outNeuron[OUTCOLUMNS];

	in = new Neuron[INCOLUMNS]; //make this dynamic
	hid = new Neuron[HIDCOLUMNS];
	out = new Neuron[OUTCOLUMNS];
	//in->weight = nullptr;
	//in->x = new float[4];//used to be in setInput, if uncomment code still runs ok, i think
	//in[2].x = new float[4];
	//nptr = new Neural;
}

Neural::~Neural()
{
	/*for (int i = 0; i < 2; ++i)
	{
		delete[] in[i];
	}
	delete[] in;*/
	/*
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
	netptr = nullptr;*/
}

void Neural::inputLayer(float** inputData, float** outputData)
{
	std::cout << "you are in input layers " << std::endl;
	std::cout << "in Nodes " << inNodes << std::endl;
	//setInput used to have inNodes as parameter in case you want to change it from place
	//(back to network), it also used to have outputData
	allocatePointers();
	setInput(inputData);
	//setInWeights();
	std::cout << "before \n";
	//sumInInputs();//sumInputs(in->x, in->weight);
	//activation(in->x, in->weight);

	std::cout << "after \n";
	//neural.setWeights(randomWeights());
}

void Neural::hiddenLayer()
{
	std::cout << "you are in hidden layers " << std::endl;
	std::cout << "in Nodes " << inNodes << std::endl;
	//Neural neural(inNodes, (iopairs / 2), ee);
	//std::cout << "in Nodes " << neural.inNodes << std::endl;
	//setInput used to have inNodes as parameter in case you want to change it from place
	//(back to network), it also used to have outputData
	std::cout << "values before activation \n";

	//hiddenActivation();
	//setHidInput();
	//setHidWeights();
	std::cout << "before \n";
	//sumInputs(*hid);
	//activation();

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
	//in = new inNeuron[2];
	//inNeuron inn[2];
	std::cout << "you are in setInput\n";


	for (int k = 0; k < inNodes; k++) //make this dynamic
	{
		//this place is the only one that will let this definition work
		//(nodeLayer + k)->x = new float[4];
		//(in + k)->x = new float[4];
		//in->weight = new float[4];

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


	//float *value;
	//struct * stpr;
	//value = (in + k)->x;

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


void Neural::setInWeights()
{

	for (int k = 0; k < 2; k++) //make this dynamic
	{
		//(in + k)->weight = new float[4];

		for (int j = 0; j < 4; j++)
		{
			std::cout << "k " << k << "\tj " << j << std::endl;
			//std::cout << "pointer " << (nodeLayer + k) << std::endl;
			(in + k)->weight[j] = randomWeights();
			std::cout << "weights " << (in + k)->weight[j] << std::endl;
		}

	}



	for (int k = 0; k < 2; k++) //make this dynamic
	{
		for (int j = 0; j < 4; j++)
			std::cout << "weights " << (in + k)->weight[j] << std::endl;
	}

	std::cout << "about to get out of weights \n" << std::endl;
	//display(in->weight); //erase this 
	/*
	std::cout << "in Nodes " << inNodes << std::endl;
	std::cout << "you are in getWeights\n";

		for (int k = 0; k < 2; k++) //make this dynamic
		{
			(in + k)->weight = new float[4];
			for (int j = 0; j < 4; j++)
			{
				(in + k)->weight[j] = randomWeights();
				std::cout << "weights " << (in + k)->weight[j] << std::endl;
			}

		}*/

}

void Neural::setHidInput()
{
	std::cout << "you are in setHidInput\n";

	for (int k = 0; k < 2; k++) //make this dynamic
	{
		//this place is the only one that will let this definition work

		for (int j = 0; j < 4; j++)
		{
			(hid + k)->x[j] = sigmoid[j][k];

			std::cout << "values " << (in + k)->x[j] << std::endl;
		}
	}

}

void Neural::setHidWeights()
{
	for (int k = 0; k < 2; k++) //make this dynamic
	{

		for (int j = 0; j < 4; j++)
		{
			std::cout << "k " << k << "\tj " << j << std::endl;
			//std::cout << "pointer " << (nodeLayer + k) << std::endl;
			(hid + k)->weight[j] = randomWeights();
			//layer[j] = randomWeights();
			//layer[k]weight[j] = 2.5;
			std::cout << "weights " << (hid + k)->weight[j] << std::endl;
		}

	}


	for (int k = 0; k < 2; k++) //make this dynamic
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << "weight assing function\n";
			std::cout << "weights " << (hid + k)->weight[j] << std::endl;
		}

	}

	std::cout << "about to get out of weights \n" << std::endl;
}




void Neural::sumInInputs()
{
	std::cout << "you are in sumINputs\n";

	for (int s = 0; s < 2; s++)
	{
		for (int w = 0; w < 4; w++)
		{
			sumtotal[w][s] += 0;
		}
	}

	for (int w = 0; w < 4; w++)
	{
		for (int s = 0; s < 2; w++)
		{
			sumtotal[w][s] += (in + s)->x[w];
			std::cout << "total " << sumtotal[w][s] << std::endl;
		}
	}

	//std::cout << "total " << total << std::endl;
	//return total;
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

void Neural::hiddenActivation()
{
	std::cout << "you are in activation\n";
	for (int s = 0; s < 2; s++)
	{
		for (int w = 0; w < 4; w++)
		{
			sigmoid[w][s] += 0;
		}
	}

	for (int s = 0; s < 2; s++)
	{
		for (int w = 0; w < 4; w++)
		{
			std::cout << "sumtotal " << sumtotal[w][s] << std::endl;
			sigmoid[w][s] += (1.0 / (1.0 + pow(ee, -sumtotal[w][s])));
			std::cout << "sigmoid " << sigmoid[w][s] << std::endl;
		}
	}
	//if(activfunction == 1 )  //MAYBE WORK ON THIS ON THE END TO HAVE A RANGE OF FUNCTIONS TO CHOOSE FROM
	std::cout << "EE " << ee << std::endl;
	//sigmoid = (1.0 / (1.0 + pow(ee, -sumInputs(actnodeLayer, weightnodeLayer))));
	//std::cout << "sigmoid " << sigmoid << std::endl;
	//return sigmoid;
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

void Neural::setWeights(float weights)
{
	std::cout << "in Nodes " << inNodes << std::endl;
	std::cout << "you are in getWeights\n";

		for (int k = 0; k < 2; k++) //make this dynamic
		{
			(in + k)->weight = new float[4];
			for (int j = 0; j < 4; j++)
			{
				(in + k)->weight[j] = randomWeights();//weights.at(j);
				std::cout << "weights " << (in + k)->weight[j] << std::endl;
			}

		}

		for (int k = 0; k < inNodes; k++) //make this dynamic
		{
			//(in + k)->weight = new float[inNodes];
			for (int j = 0; j < 4; j++)
				std::cout << "weights " << (in + k)->weight[j] << std::endl;
		}
	//display(in->weight); //erase this
}


*/

