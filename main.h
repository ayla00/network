/*
Name: Astrid Lozano
Assignment: fINAL pROJECT

NOTES:
//reading any file assumes the format is the same for all incoming files (including variable names)
//for some reason there is one more space in the file that this code cannot deal with
//the weights are from current layer to next layer
// it is assumed that the hidden layer has the same or more layers than input layer
// it is assummed a bias will always be included
// the output is provided  for view in output file, the function returns a vector so it can be used/displayed differently if necessary
getWeight(), storedWeights, and getsetWeights():
	//weight file has the following info (only data, no strings)
	//arranged in the following order:
	//the savedWeights pointer has the from layer, node at from layer, node at to layer, and weight
	//however, it will be assumed that correct info for number of nodes is given and matches the info
	//in the file, so this simplifies its extraction, however, the whole info should be extracted just to verify
*/

#ifndef MAIN_H
#define MAIN_H


#include "network.h"



void readConfigFile(std::ifstream& cfile, std::string configfile, Network* neta);
void readDataFile(std::ifstream& dfile, std::string datafile, Network* neta);
bool getData(std::string extract, int row, Network* neta);
bool extraccion(int index, int row, int col, std::string extracto, Network* neta);
bool getConfig(std::string extract, Network* neta);
const int NOTANUMBER = -999999;
bool assignConstant(std::string constname, float constvalue, Network* neta);
void assingData(int row, int col, float value, Network* neta);
const int UNEVENPAIRSNUM = -888888;
const int EMPTYFILE = -3333333;
const int NOFILE = -4444444;
const int OUTPUTFILE = -1111111;
const int FILENOTOPEN = -2222222;




#endif  //MAIN_H
