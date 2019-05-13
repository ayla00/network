#include "main.h"
#include "neural.h"


int main()
{
	srand(time(NULL));
	std::cout << "main before pointer\n";
	Network* neta = new Network;
	std::cout << "main after pointer\n";
	//Neural * neural = new Neural;
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
	//Neural n;
	//std::cout << "test " << n.test << std::endl;

	neta->train();

	//neta->loadLayers();
	//n->display();
	//n->getInput();

	delete neta;
	neta = nullptr;
	//delete neural;
	//neural = nullptr;

	return 0;
}