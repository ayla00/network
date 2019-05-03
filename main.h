#ifndef MAIN_H
#define MAIN_H


#include "network.h"

void readConfigFile(std::ifstream &cfile, std::string configfile);
//void readDataFile(std::ifstream &dfile, std::string datafile);
//bool getData(std::string extract, Network &extractdata);
bool getConfig(std::string extract, Network &extractconfig);
const int NOTANUMBER = -999999;
bool assignConstant(std::string constname, float constvalue, Network &extractconfig);

#endif  //MAIN_H
