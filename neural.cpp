#include "neural.h"

Neural::Neural(int nodes, int niopairs, float nee)
{
	//innodes = nodes;
	//Neural nnet;
	Network();
	netptr = new Network;
	std::cout << "test " << test << std::endl;
	in = new inNeuron[2]; //make this dynamic
	innodes = nodes;
	iopairs = niopairs;
	ee = nee;
	std::cout << "test " << innodes << std::endl;
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

	delete[] in->x;
	in->x = nullptr;
	delete[] in;
	in = nullptr;
	delete nptr;
	nptr = nullptr;
}

void Neural::setInput(int inNodes, float **inputData, float**outputData)
{
	//in = new inNeuron[2];
	//inNeuron inn[2];

		for (int k = 0; k < 2; k++) //make this dynamic
		{
			//this place is the only one that will let this definition work
			(in + k)->x = new float[4];

			for (int j = 0; j < 4; j++)
			{
				(in + k)->x[j] = *(*(inputData + j) + k);
				std::cout << "values " << (in + k)->x[j] << std::endl;
			}
		}

	//display(in->x); //erase this 
}
/*
void Neural::display(float * values)
{
	std::cout << "you are in display\n";
	std::cout << "in Nodes " << inNodes << std::endl;
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 2; k++) //make this dynamic
			std::cout << "input " << values[j][k] << std::endl;
	}
}
*/


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
}

void Neural::setWeights()
{
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

	}

	for (int k = 0; k < innodes; k++) //make this dynamic
	{
		//(in + k)->weight = new float[inNodes];
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
				
		}
	
		for (int k = 0; k < innodes; k++) //make this dynamic
		{
			//(in + k)->weight = new float[inNodes];
			for (int j = 0; j < 4; j++)
				std::cout << "weights " << (in + k)->weight[j] << std::endl;
		}

		std::cout << "about to get out of weights \n" <<  std::endl;
	//display(in->weight); //erase this */
}

float Neural::sumInputs()
{
	std::cout << "you are in sumINputs\n";
	float total = 0;
	for (int s = 0; s < 2; s++)
	{
		for (int w = 0; w < 4; w++)
		{
			total += ((in + s)->x[w])*((in + s)->weight[w]);
		}
	}

	std::cout << "total " << total << std::endl;
	return total;
}

float Neural::activation()
{
	//if(activfunction == 1 )  //MAYBE WORK ON THIS ON THE END TO HAVE A RANGE OF FUNCTIONS TO CHOOSE FROM
	std::cout << "EE " << ee << std::endl;
	sigmoid = (1.0 / (1.0 + pow(ee, -sumInputs())));
	std::cout << "sigmoid " << sigmoid << std::endl;
	return sigmoid;
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