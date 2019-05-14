
/*
Name: Astrid Lozano
Assignment: fINAL project

NOTES:
//reading any file assumes the format is the same for all incoming files (including variable names)
//for some reason there is one more space in the file that this code cannot deal with

Notes: cannot create a pointer to derived class here, compiler gives memory
access violation when it tries to run; if a pointer is created in cpp file, and the
pointer is declared as derived class, it won't grab the function from derived class

*/

#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <stdlib.h> //library where rand is located
#include <stdio.h>
#include <time.h>


class Network
{
public:
	Network();
	Network(int pairs, int nodes, int innode, int hidnode, int outnode, float natexp, float lrate, int wfile);
	~Network();
	void train();
	void testnetwork();
	void run();
	//void weights();
	//void loadweights();
	float randomWeights();
	void loadInput(int inrow, int incoloumn, float value);
	void loadOutput(int inrow, int incolumn, float value);
	bool setConfig(std::string constname, float value);
	float** getWeights(std::ifstream &wFile, std::string weightData);
	void displayVariables();
	//void displayInput();
	//bool setInArrayNumbers(int inrow, int incolumn);
	void setInputRow(int num);
	int getInputRow();
	void setInputColumn(int num);
	void loadLayers();


protected:
	//void feedForward();
	//void backPropagate();
	int iopairs;
	int row = iopairs / 2;
	int column;
	int inNodes;
	int hidNodes;
	int outNodes;
	int maxEpoch;
	int weightfile;
	float on;
	float off;
	float offSoft;
	float onSoft;
	float lr;
	float ee;
	float** inputData;
	float** outputData;
	void writeWeight(std::vector<float*> neuralWeights);
	void writeOutput(float ** neuralOutput);
	const int OUTPUTFILE = -1111111;
	const int FILENOTOPEN = -2222222;
	const int EMPTYFILE = -3333333;
	float **storedWeights;

};

#endif  //NETWORK_H