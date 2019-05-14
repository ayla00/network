
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



#include "neural.h"

Neural::Neural(int pairs, int nodes, int innode, int hidnode, int outnode, float natexp, float lrate, int wfile)
{


	Network(pairs, nodes, innode + BIAS, hidnode + BIAS, outnode, natexp, lrate, wfile);


	iopairs = pairs;
	row = iopairs / 2;
	column = nodes;
	inNodes = innode + BIAS;
	hidNodes = hidnode + BIAS;
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

	y = new float* [ROWS];
	//sumtotal = new float*[ROWS];
	//sigmoid = new float*[ROWS];
	//value = new float[4];//constant number of parameters

	// this will build empty network
	allocatePointers();

}

Neural::~Neural()
{

	delete[] y;
	y = nullptr;

	delete[] out->error;
	out->error = nullptr;
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




void Neural::inputLayer(float** inputData, float** outputData)
{

	setInput(inputData);

}

void Neural::hiddenLayer()
{

	//sums inputs with correct number of nodes for next layer
	sumInputs(hidNodes, inNodes, in);
	activation(hidNodes, in);
	setotherInput(hidNodes, hid);

}

void Neural::outputLayer()
{
	sumInputs(outNodes, hidNodes, hid);
	activation(outNodes, hid);
	setotherInput(outNodes, out);
}


void Neural::setWeights()
{
	rWeights(inNodes, hidNodes, in);
	rWeights(hidNodes, outNodes, hid);
}


std::vector<float*> Neural::saveWeights()
{
	//how to make this dynamic?
	pushWeights(in, hid);
	pushWeights(hid, out);
	return runweights;
}


float** Neural::saveOuput()
{

	//if there are more than one outNode would I have to produce just one y or as many as output nodes?
	//in that case the y would be a summation of the columns
	for (int column = 0; column < outNodes; column++)
	{
		for (int r = 0; r < row; r++)
		{

			(*(*(y + r) + column)) = sigmoid[r][column];
		}

	}

	return y;
}

void Neural::getsetWeights(float** weights)
{
	Neuron* layer;
	//the storeddWeights pointer has the from layer, node at from layer, node at to layer, and weight
	//however, it will be assumed that correct info for number of nodes is given and matches the info
	//in the file, so this simplifies its extraction, it was written w/ same loop so order is same
	for (int n = 0; n < (inNodes + hidNodes); n++)
	{
		if (n < inNodes)
			layer = in;
		else
			layer = hid;

		for (int r = 0; r < row; r++)
		{
			(layer + n)->weight[r] = (*(*(storedWeights + r) + (WPARAMETER - 1)));//this gives column were weight is located
		}

	}
}

void Neural::allocatePointers()
{
	//function allocates arrays for use in network
	const int ROWS = iopairs / 2;
	const int HIDRS = hidNodes;
	const int OUTRS = outNodes;
	const int COLUMN = column;

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
	}

	for (int nodes = 0; nodes < outNodes; nodes++)
	{
		(out + nodes)->x = new float[ROWS];
		(out + nodes)->error = new float[ROWS];
		//no memory allocated for weight as not needed
	}
	for (int nodes = 0; nodes < ROWS; nodes++)
	{
		//has a dif structure than above containers
		y[nodes] = new float[COLUMN];
		//sumtotal[nodes] = new float[COLUMN];
		//sigmoid[nodes] = new float[COLUMN];
	}


}

void Neural::setInput(float** inputData)
{

	for (int k = 0; k < inNodes; k++)
	{
		if (k != (inNodes - BIAS))
		{
			for (int j = 0; j < row; j++)
			{
				(in + k)->x[j] = *(*(inputData + j) + k);

			}
		}
		else
		{
			for (int j = 0; j < row; j++)
			{
				(in + k)->x[j] = BIASVALUE;
			}
		}

	}

}



void Neural::display(int nodes, Neuron * nptr)
{

	for (int j = 0; j < row; j++)
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

	/*for (int n = 0; n < nodes; n++)
	{
		for (int r = 0; r < 4; r++)
		{
			(layer + n)->error[r] = 0;
		}

	}*/

	for (int n = 0; n < nodes; n++)
	{
		for (int r = 0; r < row; r++)
		{
			(layer + n)->error[r] = sigmoid[r][n] * (1.0 - (sigmoid[r][n])) * ((*(*(outputData + r) + n)) - (sigmoid[r][n]));
			//(layer + n)->error[r] = (*(*sigmoid + r) + n) * (1.0 - (sigmoi[w][s])) * ((*(*(outputData + r) + n)) - ((*(*sigmoid + r) + n)));
		}

	}


}

void Neural::backErrors(int back, int next, Neuron * backlayer, Neuron * nextlayer)
{

	float sum[4][3];

	for (int s = 0; s < back; s++)
	{
		for (int w = 0; w < row; w++)
		{
			sum[w][s] = 0;
		}
	}

	for (int n = 0; n < back; n++)
	{
		int layerindex;//necessary as index is used out of for loop
		for (int r = 0; r < row; r++)
		{
			//nodes of previous layer
			//will this work if nodes is zero?, will it ever be zero
			for (layerindex = 0; layerindex < next; layerindex++)
			{
				//check if i need to do this PER row (r) or is just all  cummulative
				sum[r][layerindex] += ((nextlayer + layerindex)->error[r]) * ((backlayer + n)->weight[layerindex]);
			}

			(backlayer + n)->error[r] = (((backlayer + n)->x[r]) * (1.0 - ((backlayer + n)->x[r])) * sum[r][layerindex]);


		}


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

		for (int r = 0; r < row; r++)
		{
			//nodes of previous layer
			//will this work if nodes is zero?, will it ever be zero
			//CHECK THIS AGAIN
			for (int layerindex = 0; layerindex < next; layerindex++)
			{
				//here (backlayer + n)->weight[layerindex] = (((backlayer + n)->weight[layerindex]) + (lr * ((nextlayer + layerindex)->error[r]) * (backlayer + n)->x[r]));
				//error from previous layer is used
				(backlayer + n)->weight[layerindex] = (((backlayer + n)->weight[layerindex]) + (lr * ((nextlayer + layerindex)->error[r]) * (backlayer + n)->x[r]));
			}
		}
	}


}

void Neural::pushWeights(Neuron * from, Neuron * to)
{


	const int ROWS = row;

	float fromlayer;
	float fromNode, toNode;

	if (from == in)
	{
		//maybe modify if you make hidden layers dynamic
		fromlayer = 1;
		fromNode = inNodes;
		toNode = hidNodes;
	}
	else
	{
		fromlayer = 2;
		fromNode = hidNodes;
		toNode = outNodes;
	}


	for (int node = 0; node < fromNode; node++)
	{

		for (int nextnode = 0; nextnode < toNode; nextnode++)
		{
			//first is from layer #, present layer node #, then next layer node, then weight
			//do we have to save the weights to the bias?????
			//needs to be a new address each time, other wise it passes only one address to vector
			//and vector only captures one pointer as opposed to all pointers.
			//opposite problem than the usual reassigment
			value = new float[WPARAMETER];//constant number of parameters
			value[0] = fromlayer;
			value[1] = node;
			value[2] = nextnode;
			value[3] = ((from + node)->weight[nextnode]);

			runweights.push_back(value);
		}
	}

}



void Neural::rWeights(int current, int next, Neuron * layer)
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
			(layer + n)->weight[r] = randomWeights();
		}
	}


}

void Neural::setotherInput(int current, Neuron * layer)
{

	if (layer == hid)
	{
		for (int k = 0; k < current; k++)
		{
			if (k != (current - BIAS))
			{
				for (int j = 0; j < row; j++)
				{
					(layer + k)->x[j] = sumtotal[j][k];
				}
			}
			else
			{
				for (int j = 0; j < row; j++)
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
			for (int j = 0; j < row; j++)
			{
				(layer + k)->x[j] = sumtotal[j][k];
			}
		}
	}

	//for (int k = 0; k < current; k++)
	//{

		//for (int j = 0; j < 4; j++)
		//{
			//(layer + k)->x[j] = sigmoid[j][k];

		//}
	//}

}



void Neural::sumInputs(int current, int previous, Neuron * backlayer)
{


	for (int s = 0; s < current; s++)
	{
		for (int w = 0; w < row; w++)
		{
			sumtotal[w][s] = 0;
		}
	}

	//nodes of current layer

	//delivers appropriate index limit to each layer (accounts for bias node)
	if (backlayer != out)
		current = current - BIAS;
	else
		current = current;

	//was checking for correctness, it looks ok, just changed index names
	for (int n = 0; n < current; n++)
	{
		for (int r = 0; r < row; r++)
		{
			//nodes of previous layer
			//will this work if nodes is zero?, will it ever be zero
			for (int backindex = 0; backindex < previous; backindex++)
			{
				sumtotal[r][n] += ((backlayer + backindex)->x[r]) * ((backlayer + backindex)->weight[n]);
				//(*(*(sumtotal + r) + n)) = ((backlayer + backindex)->x[r]) * ((backlayer + backindex)->weight[n]);

			}

		}

	}


}


//don't really need neuron * layer parameter now, might redefine sumtotal[][] so wait till then to erase
void Neural::activation(int nodes, Neuron * layer)
{
	for (int s = 0; s < nodes; s++)
	{
		for (int w = 0; w < row; w++)
		{
			sumtotal[w][s] = 0;
		}
	}

	for (int s = 0; s < nodes; s++)
	{
		for (int w = 0; w < row; w++)
		{
			sigmoid[w][s] = (1.0 / (1.0 + pow(ee, -(sumtotal[w][s]))));
		}
	}
}


/*
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
