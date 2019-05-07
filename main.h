#ifndef MAIN_H
#define MAIN_H


#include "network.h"


void readConfigFile(std::ifstream &cfile, std::string configfile, Network * neta);
void readDataFile(std::ifstream &dfile, std::string datafile, Network * neta);
bool getData(std::string extract, int row, Network * neta);
bool extraccion(int index, int row, int col, std::string extracto, Network * neta);
bool getConfig(std::string extract, Network *neta);
const int NOTANUMBER = -999999;
bool assignConstant(std::string constname, float constvalue, Network * neta);
void assingData(int row, int col, float value, Network * neta);
const int UNEVENPAIRSNUM = -888888;
//Network * neta; 


#endif  //MAIN_H

