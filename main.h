#ifndef MAIN_H
#define MAIN_H


#include "network.h"

void readConfigFile(std::ifstream &file, std::string configfile);
bool getData(std::string extract, Network &extractinfo);

#endif  //MAIN_H
