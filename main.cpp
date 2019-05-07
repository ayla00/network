#include "network.h"
#include "main.h"

int main()
{
	Network * neta = new Network;
	std::string file = "configuration.txt";
	std::ifstream cfgfile;
	readConfigFile(cfgfile, file, neta);

	//Network n;
	std::string datafile = "datatest2.txt";
	std::ifstream dfile;

	//you can create class after you got io pairs

	readDataFile(dfile, datafile, neta);
	//Network n; //= new Network;
	neta->displayVariables();
	neta->displayInput();
	//delete n;
	//n = nullptr;
	delete neta;
	neta = nullptr;
	return 0;
}