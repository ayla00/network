#include "neural.h"

Neural::Neural(int pairs, int nodes, int innode, int hidnode, int outnode, float natexp, float lrate)
{

	std::cout << "derived constructor \n";
	displayVariables();
	Network(pairs, nodes, innode + BIAS, hidnode, outnode, natexp, lrate);


	iopairs = pairs;
	row = iopairs / 2;
	column = nodes;
	std::cout << "nodes " << nodes << std::endl;
	inNodes = innode + BIAS;
	hidNodes = hidnode;
	outNodes = outnode;
	ee = natexp;
	lr = lrate;
	displayVariables();
	const int INCOLUMNS = inNodes;
	const int HIDCOLUMNS = hidNodes;
	const int OUTCOLUMNS = outNodes;
	const int ROWS = row;


	in = new Neuron[INCOLUMNS];
	hid = new Neuron[HIDCOLUMNS];
	out = new Neuron[OUTCOLUMNS];

	//assumes hidden layer HAS the same or more layers than input layer
	//sumtotal = new float*[HIDCOLUMNS];

	//yresult = new Neuron[OUTCOLUMNS]

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

	delete[] out->error;
	out->error = nullptr;
	//DON'T NEED THIS BECAUSE THERE IS NO WEIGHTS FROM OUTPUT LAYER TO OUTPUT
	//delete[] out->weight;
	//out->weight = nullptr;
	delete[] out->x;
	out->x = nullptr;
	delete[] out;
	out = nullptr;

	delete[] hid->error;
	hid->error = nullptr;
	delete[] hid->weight;
	hid->weight = nullptr;
	delete[] hid->x;
	hid->x = nullptr;
	delete[] hid;
	hid = nullptr;

	delete[] in->error;
	in->error = nullptr;
	delete[] in->weight;
	in->weight = nullptr;
	delete[] in->x;
	in->x = nullptr;
	delete[] in;
	in = nullptr;

	delete netptr;
	netptr = nullptr;
}

void Neural::setWeights()
{
	setWeights(inNodes, hidNodes, in);
	setWeights(hidNodes, outNodes, hid);
}

void Neural::inputLayer(float** inputData, float** outputData)
{
	std::cout << "you are in input layers " << std::endl;
	std::cout << "in Nodes " << inNodes << std::endl;
	//setInput used to have inNodes as parameter in case you want to change it from place
	//(back to network), it also used to have outputData
	setInput(inputData);

	//the weights are from current layer to next layer
	//so the number of nodes for weigth array must correspond to the ones for next layer
	//setWeights(inNodes, hidNodes, in); sent it to hidden layer so i can set up loop at network
	std::cout << "before \n";
	//sumInputs(inNodes, hidNodes, in);

	std::cout << "after \n";
}

void Neural::hiddenLayer()
{

	std::cout << "you are in hidden layers " << std::endl;
	std::cout << "in Nodes " << inNodes << std::endl;

	//setInput used to have inNodes as parameter in case you want to change it from place
	//(back to network), it also used to have outputData
	std::cout << "values before activation \n";
	sumInputs(hidNodes, inNodes, in);
	activation(hidNodes, in);
	//hiddenActivation();
	setotherInput(hidNodes, hid);
	//setWeights(hidNodes, outNodes, hid); rearranged to set up loop
	std::cout << "before \n";
	//sums inputs with correct number of nodes for next layer
	//sumInputs(hidNodes, outNodes, hid);
	std::cout << "after \n";
}

void Neural::outputLayer()
{

	std::cout << "you are in output layers " << std::endl;
	std::cout << "in Nodes " << inNodes << std::endl;

	//setInput used to have inNodes as parameter in case you want to change it from place
	//(back to network), it also used to have outputData
	std::cout << "values before activation \n";
	sumInputs(outNodes, hidNodes, hid);
	activation(outNodes, hid);
	setotherInput(outNodes, out);


	//no weights from output layer to output, wait to confirm
	//the next two functions should not be needed
	//setWeights(outNodes, outNodes, out);
	//sumInputs(outNodes, outNodes, out);

	std::cout << "after \n";
}

void Neural::saveWeights()
{
	std::cout << "you are in saveWeights()\n";
}

void Neural::allocatePointers()
{
	//function allocates arrays for use in network
	const int ROWS = iopairs / 2;
	const int HIDRS = hidNodes;
	const int OUTRS = outNodes;

	std::cout << "pairs " << ROWS << std::endl;
	std::cout << "allocate " << std::endl;
	displayVariables();
	for (int nodes = 0; nodes < inNodes; nodes++)
	{
		(in + nodes)->x = new float[ROWS];
		(in + nodes)->weight = new float[HIDRS];
		(in + nodes)->error = new float[ROWS];
	}

	for (int nodes = 0; nodes < hidNodes; nodes++)
	{
		(hid + nodes)->x = new float[ROWS];
		(hid + nodes)->weight = new float[OUTRS];
		(hid + nodes)->error = new float[ROWS];
		//*(sumtotal + nodes) = new float[ROWS];
	}

	for (int nodes = 0; nodes < outNodes; nodes++)
	{
		(out + nodes)->x = new float[ROWS];
		//not needed, do I have to allocate memory anyway?
		//(out + nodes)->weight = new float[ROWS];
		(out + nodes)->error = new float[ROWS];
	}

}

void Neural::setInput(float** inputData)
{
	std::cout << "you are in setInput\n";
	for (int k = 0; k < inNodes; k++)
	{
		if (k != (inNodes - BIAS))
		{
			for (int j = 0; j < 4; j++)
			{
				(in + k)->x[j] = *(*(inputData + j) + k);

			}
		}
		else
		{
			for (int j = 0; j < 4; j++)
			{
				(in + k)->x[j] = BIASVALUE;
			}
		}

	}

	/*for (int k = 0; k < inNodes; k++)
	{

			for (int j = 0; j < 4; j++)
			{
				(in + k)->x[j] = *(*(inputData + j) + k);

			}


	}

	for (int k = 0; k < inNodes; k++) //DELETE, JUST DEMO PURPOSES
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << "values " << (in + k)->x[j] << std::endl;
		}
	}*/


	display(inNodes, in); //erase this 
}

void Neural::display(int nodes, Neuron * nptr)
{
	std::cout << "you are in display\n";
	std::cout << "in Nodes " << inNodes << std::endl;
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < nodes; k++) //make this dynamic
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
			(layer + n)->error[r] = sigmoid[r][n] * (1.0 - (sigmoid[r][n])) * ((*(*(outputData + r) + n)) - (sigmoid[r][n]));
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
	//is the weight calculated for each entry or is the same for all entries w/in same node???
	float sum = 0;
	for (int n = 0; n < back; n++)
	{

		for (int r = 0; r < 4; r++)
		{
			//nodes of previous layer
			//will this work if nodes is zero?, will it ever be zero
			for (int layerindex = 0; layerindex < next; layerindex++)
			{
				//check if i need to do this PER row (r) or is just all  cummulative
				sum += ((nextlayer + layerindex)->error[r]) * ((backlayer + n)->weight[layerindex]);
			}

			(backlayer + n)->error[r] = (((backlayer + n)->x[r]) * (1.0 - (((backlayer + n)->x[r]) * sum)));

		}


	}

	for (int n = 0; n < back; n++)
	{
		for (int r = 0; r < 4; r++) //make this dynamic
			std::cout << "errors " << (backlayer + n)->error[r] << std::endl;
	}
}

void Neural::adjustWeights()
{
	backWeights(hidNodes, outNodes, hid, out);
	backWeights(inNodes, hidNodes, in, hid);
}


void Neural::backWeights(int back, int next, Neuron * backlayer, Neuron * nextlayer)
{
	//is the weight calculated for each entry or is the same for all entries w/in same node???
	for (int n = 0; n < back; n++)
	{

		for (int r = 0; r < 4; r++)
		{
			//nodes of previous layer
			//will this work if nodes is zero?, will it ever be zero
			//CHECK THIS AGAIN
			for (int layerindex = 0; layerindex < next; layerindex++)
			{
				(backlayer + n)->weight[layerindex] = (((backlayer + n)->weight[layerindex]) + (lr * ((nextlayer + layerindex)->error[r]) * (backlayer + n)->x[r]));
			}
		}
	}

	for (int n = 0; n < back; n++)
	{
		for (int r = 0; r < 4; r++) //make this dynamic
			std::cout << "weights " << (backlayer + n)->weight[r] << std::endl;
	}
}



void Neural::setWeights(int current, int next, Neuron * layer)
{
	//this array needs a different set-up thant the input array(x[])
	//it is assumed that there is only one weight value from one neuron to the next for all input entries
	//(as opposed to a different weight for each entry, for example it's the same wegith w[j]=a for all j,
	//instead of each j having a different one w[0]=d, w[1]=e, etc;
	//here, the n is the #of nodes in current layer and r is not the entries as in input, but the number
	//of nodes in next layer
	for (int n = 0; n < current; n++) //make this dynamic
	{
		for (int r = 0; r < next; r++)
		{
			std::cout << "n " << n << "\tr " << r << std::endl;
			(layer + n)->weight[r] = randomWeights();
			std::cout << "weights " << (layer + n)->weight[r] << std::endl;
		}
	}


	for (int n = 0; n < current; n++) //make this dynamic
	{
		for (int r = 0; r < next; r++)
		{
			std::cout << "n " << n << "\tr " << r << std::endl;
			std::cout << "weights " << (layer + n)->weight[r] << std::endl;
		}
	}

	std::cout << "about to get out of weights \n" << std::endl;
	//display(in->weight); //erase this 


}

void Neural::setotherInput(int current, Neuron * layer)
{
	std::cout << "you are in setHidInput\n";
	/*if (layer == hid)
	{
		for (int k = 0; k < current; k++)
		{
			if (k != (current - BIAS))
			{
				for (int j = 0; j < 4; j++)
				{
					(layer + k)->x[j] = sigmoid[j][k];
				}
			}
			else
			{
				for (int j = 0; j < 4; j++)
				{
					(layer + k)->x[j] = BIASVALUE;
				}
			}

		}
	}
	else
	{*/
	for (int k = 0; k < current; k++)
	{
		for (int j = 0; j < 4; j++)
		{
			(layer + k)->x[j] = sigmoid[j][k];
		}
	}
	//}

	for (int k = 0; k < current; k++)
	{

		for (int j = 0; j < 4; j++)
		{

			(layer + k)->x[j] = sigmoid[j][k];

			std::cout << "sigmoid " << sigmoid[j][k] << std::endl;

		}
	}

}



void Neural::sumInputs(int current, int previous, Neuron * backlayer)
{
	std::cout << "you are in sumINputs\n";

	for (int s = 0; s < current; s++)
	{
		for (int w = 0; w < 4; w++)
		{
			//std::cout << "sigmoid array " << sigmoid[j][k] << std::endl;
			//std::cout << "sigmoid pointer " << (*(*(sumtotal + j) + k)) << std::endl;
			sumtotal[w][s] = 0;

		}
	}

	//nodes of current layer

	//was checking for correctness, it looks ok, just changed index names
	for (int n = 0; n < current; n++)
	{
		for (int r = 0; r < 4; r++)
		{
			//nodes of previous layer
			//will this work if nodes is zero?, will it ever be zero
			for (int backindex = 0; backindex < previous; backindex++)
			{
				sumtotal[r][n] += ((backlayer + backindex)->x[r]) * ((backlayer + backindex)->weight[n]);
				//(*(*(sumtotal + r) + n)) = ((backlayer + backindex)->x[r]) * ((backlayer + backindex)->weight[n]);
				std::cout << "total " << sumtotal[r][n] << std::endl;
			}

		}

	}

	//OLD LOOP
	/*for (int s = 0; s < current; s++)
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


	}*/

	//std::cout << "total " << total << std::endl;
	//return total;
}


//don't really need neuron * layer parameter now, might redefine sumtotal[][] so wait till then to erase
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




/*
oid Neural::setotherInput(int current, Neuron * layer)
{
	std::cout << "you are in setHidInput\n";
	if (layer == hid)
	{
		for (int k = 0; k < current; k++)
		{
			if (k != (current - BIAS))
			{
				for (int j = 0; j < 4; j++)
				{
					(layer + k)->x[j] = sigmoid[j][k];
				}
			}
			else
			{
				for (int j = 0; j < 4; j++)
				{
					(layer + k)->x[j] = BIASVALUE;
				}
			}

		}
	}
	else
	{
		for (int k = 0; k < current; k++)
		{
			for (int j = 0; j < 4; j++)
			{
				(layer + k)->x[j] = sigmoid[j][k];
			}
		}
	}

	for (int k = 0; k < current; k++)
	{

		for (int j = 0; j < 4; j++)
		{

			(layer + k)->x[j] = sigmoid[j][k];

			std::cout << "sigmoid " << sigmoid[j][k] << std::endl;

		}
	}

}



void Neural::setInput(float** inputData)
{
	std::cout << "you are in setInput\n";


	for (int k = 0; k < inNodes; k++)
	{
		if (k != (inNodes - BIAS))
		{
			for (int j = 0; j < 4; j++)
			{
				(in + k)->x[j] = *(*(inputData + j) + k);

			}
		}
		else
		{
			for (int j = 0; j < 4; j++)
			{
				(in + k)->x[j] = BIASVALUE;
			}
		}

	}

	for (int k = 0; k < inNodes; k++) //DELETE, JUST DEMO PURPOSES
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << "values " << (in + k)->x[j] << std::endl;
		}
	}


	display(inNodes, in); //erase this
}


float Neural::Normalize(float *value)
{
	return ((*value - findMin()) / (findMax() - findMin()));
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

