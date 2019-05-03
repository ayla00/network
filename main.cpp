#include "network.h"
#include "main.h"

int main()
{
	Network n;
	std::string file = "configuration.txt";
	std::ifstream cfgfile;
	readConfigFile(cfgfile, file);

	return 0;
}