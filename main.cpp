#include "main.h"
#include "neural.h"


int main()
{
	srand(time(NULL));
	Network * neta = new Network;
	//Neural * n = new Neural;
	std::string file = "configuration.txt";
	std::ifstream cfgfile;
	readConfigFile(cfgfile, file, neta);
	neta->test = 9;
	std::string datafile = "datatest2.txt";
	std::ifstream dfile;

	//you can create class after you got i/o pairs
	readDataFile(dfile, datafile, neta);

	neta->displayVariables();
	neta->displayInput();
	std::cout << "you are out of displayInput\n";
	Neural n;
	std::cout << "test " << n.test << std::endl;
	neta->loadLayers();
	//n->display();
	//n->getInput();

	delete neta;
	neta = nullptr;
	//delete n;
	//n = nullptr;

	return 0;
}