/*
Name: Astrid Lozano
Assignment: fINAL project

NOTES:
//reading any file assumes the format is the same for all incoming files (including variable names)
//for some reason there is one more space in the file that this code cannot deal with
*/

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
const int EMPTYFILE = -3333333;
const int NOFILE = -4444444;



#endif  //MAIN_H
