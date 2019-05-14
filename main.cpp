/*
Name: Astrid Lozano
Assignment: fINAL project

NOTES:
//reading any file assumes the format is the same for all incoming files (including variable names)
//for some reason there is one more space in the file that this code cannot deal with
*/


#include "main.h"
#include "neural.h"


int main()
{
	//try
	//{
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
	//}
	//catch (...)
	//{
		//std::cout << "an error has occurred\n";
	//}



	return 0;
}