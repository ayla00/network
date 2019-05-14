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
#include "main.h"
#include "neural.h"


int main()
{
	try
	{
		srand(time(NULL));

		Network* neta = new Network;

		std::string file = "configuration.txt";
		std::ifstream cfgfile;
		readConfigFile(cfgfile, file, neta);

		std::string datafile = "and.dat";
		std::ifstream dfile;

		//you can create class after you got i/o pairs
		readDataFile(dfile, datafile, neta);


		neta->train();
		//neta->testnetwork();
		//neta->run();
		std::string weightfile = "neuralweight.txt";


		delete neta;
		neta = nullptr;
	}
	catch (...)
	{
		std::cout << "an error has occurred\n";
	}



	return 0;
}