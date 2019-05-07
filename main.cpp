#include "main.h"
#include "neural.h"


int main()
{
	Network * neta = new Network;
	//Neural * n = new Neural(2);
	std::string file = "configuration.txt";
	std::ifstream cfgfile;
	readConfigFile(cfgfile, file, neta);

	std::string datafile = "datatest2.txt";
	std::ifstream dfile;

	//you can create class after you got i/o pairs
	readDataFile(dfile, datafile, neta);

	neta->displayVariables();
	neta->displayInput();
	std::cout << "you are out of displayInput\n";
	neta->loadLayers();
	//n->display();
	//n->getInput();

	delete neta;
	neta = nullptr;
	//delete n;
	//n = nullptr;

	return 0;
}