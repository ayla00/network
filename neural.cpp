
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

	const int INCOLUMNS = inNodes;
	const int HIDCOLUMNS = hidNodes;
	const int OUTCOLUMNS = outNodes;
	const int ROWS = row;


	in = new Neuron[INCOLUMNS];
	hid = new Neuron[HIDCOLUMNS];
	out = new Neuron[OUTCOLUMNS];

	y = new float* [ROWS];
	sumtotal = new float* [ROWS];
	sigmoid = new float* [ROWS];
	sum = new float[ROWS];

	// this will build empty network
	allocatePointers();

}

Neural::~Neural()
{

	delete[] sum;
	sum = nullptr;

	delete[] sigmoid;
	sigmoid = nullptr;

	delete[] sumtotal;
	sumtotal = nullptr;

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
		//pointers/arrays have dif structure than above containers
		//y should have same structure as outputData
		//for other ones the # of nodes for hiddenLayer was chosen (assumes it's greater than or equal to inputLayer)
		y[nodes] = new float[OUTRS];
		sumtotal[nodes] = new float[HIDRS];
		sigmoid[nodes] = new float[HIDRS];
	}


}


void Neural::setWeights()
{
	rWeights(inNodes, hidNodes, in);
	rWeights(hidNodes, outNodes, hid);
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
			//when this function is called, it means a weights file has been opened in Network and storedWeights is already full
			//does it get the values automatically or have to send them through parameter? check this
			(layer + n)->weight[r] = (*(*(storedWeights + r) + (WPARAMETER - 1)));//this gives column were weight is located
		}

	}
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
	//sums inputs with correct number of nodes for next layer
	sumInputs(outNodes, hidNodes, hid);
	activation(outNodes, out);
	setotherInput(outNodes, out);
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


void Neural::sumInputs(int current, int previous, Neuron * backlayer)
{


	for (int n = 0; n < current; n++)
	{
		for (int r = 0; r < row; r++)
		{
			*(*(sumtotal + r) + n) = 0;
		}
	}

	//nodes of current layer

	//delivers appropriate index limit to each layer (accounts for bias node)
	//for sumInputs, the sum will be used in next layer, so for to include correct # of nodes for next layer
	//this condition is the appropriate one
	if (backlayer != hid)
	{
		//std::cout << "you are in adjust index limit to BIas\n";
		current = current - BIAS;
	}
	else
		current = current;

	//was checking for correctness, it looks ok, just changed index names
	for (int n = 0; n < current; n++)
	{
		for (int r = 0; r < row; r++)
		{
			//nodes of previous layer
			for (int backindex = 0; backindex < previous; backindex++)
			{
				(*(*(sumtotal + r) + n)) += ((backlayer + backindex)->x[r]) * ((backlayer + backindex)->weight[n]);
			}
		}

	}


}


void Neural::activation(int nodes, Neuron * layer)
{

	for (int s = 0; s < nodes; s++)
	{
		for (int w = 0; w < row; w++)
		{
			*(*(sigmoid + w) + s) = 0;
		}
	}

	if (layer != out)
		nodes = nodes - BIAS;
	else
		nodes = nodes;

	for (int n = 0; n < nodes; n++)
	{
		for (int r = 0; r < row; r++)
		{
			*(*(sigmoid + r) + n) = (1.0 / (1.0 + pow(ee, -(*(*(sumtotal + r) + n)))));
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
					(layer + k)->x[j] = (*(*(sigmoid + j) + k));
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
				(layer + k)->x[j] = (*(*(sigmoid + j) + k));
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

	for (int n = 0; n < nodes; n++)
	{
		for (int r = 0; r < 4; r++)
		{
			(layer + n)->error[r] = 0;
		}

	}

	for (int n = 0; n < nodes; n++)
	{
		for (int r = 0; r < row; r++)
		{
			(layer + n)->error[r] = ((layer + n)->x[r]) * (1.0 - ((layer + n)->x[r])) * (((*(*(outputData + r) + n))) - ((layer + n)->x[r]));
		}

	}


}

void Neural::backErrors(int back, int next, Neuron * backlayer, Neuron * nextlayer)
{


	for (int s = 0; s < back; s++)
	{
		for (int w = 0; w < row; w++)
		{
			*(sum + w) = 0;
		}
	}

	for (int n = 0; n < back; n++)
	{
		int layerindex;//necessary as index is used out of for loop
		for (int r = 0; r < row; r++)
		{
			//nodes of previous layer
			for (layerindex = 0; layerindex < next; layerindex++)
			{
				sum[r] += ((nextlayer + layerindex)->error[r]) * ((backlayer + n)->weight[layerindex]);

			}

			(backlayer + n)->error[r] = (((backlayer + n)->x[r]) * (1.0 - ((backlayer + n)->x[r])) * sum[r]);

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

	for (int n = 0; n < back; n++)
	{

		for (int r = 0; r < row; r++)
		{
			//nodes of previous layer
			for (int layerindex = 0; layerindex < next; layerindex++)
			{
				//error from previous layer is used
				(backlayer + n)->weight[layerindex] = (((backlayer + n)->weight[layerindex]) + (lr * ((nextlayer + layerindex)->error[r]) * ((backlayer + n)->x[r])));
				//adjweightStack.push_back((backlayer + n)->weight[layerindex]);
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

void Neural::displayVector()
{
	float* estrato = new float;
	int index = 0;
	//int indice = 0;
	int sizeadjw = adjweightStack.size();

	for (int n = 0; n < inNodes; n++)
	{
		for (int r = 0; r < row; r++)
		{
			//std::cout << " input i" << " weight ih " << " sumtotal h " << " sig h " << " weight h " << " sumtotal o " << " sigmoid o " << " error " << std::endl;

			for (int indice = 0; indice < outNodes; indice++)
			{
				std::cout << " error o/a " << " sigmoid o " << " error h/o " << " weight h/o " << " act h " << " adj w h/o " << std::endl;
				std::cout << (out + indice)->error[r] << '\t' << (out + indice)->x[r] << '\t' << (hid + n)->error[r] << '\t' << (hid + n)->weight[r];
				std::cout << '\t' << (hid + n)->x[r] << '\t' << adjweightStack.at(index) << std::endl;
				index++;

				std::cout << " error h/o " << " act h " << " weigth h/o" << " error h/o " << "weight i/h " << " adj w i/h " << std::endl;
				std::cout << (out + indice)->error[r] << '\t' << (hid + n)->x[r] << '\t' << (hid + n)->weight[r] << '\t' << (hid + n)->error[r];
				std::cout << '\t' << (in + n)->weight[r] << '\t' << adjweightStack.at(index) << std::endl;
				index += 1;
			}

		}


	}
	//delete estrato;
	//estrato = nullptr;
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