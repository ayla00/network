/*
Name: Astrid Lozano
Assignment: fINAL pROJECT

NOTES:
* the sample output and weights are produced by running the test() function and will be found in the same file where code
is stored
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
//the network can extract info froma file that includes four parameters in this order: layer weight is
from (1 = in, 2 = hidden), node the weight is from, node the weight is goiong to, and the weight AND has no other stuff but
the #s in it AND has the name "neuralweigth.txt"
*/
#include "main.h"


void readConfigFile(std::ifstream& cfile, std::string configfile, Network* neta)
{

	std::string textline;
	int count = 0;
	cfile.open(configfile);

	if ((cfile.is_open()))
	{

		while (getline(cfile, textline) && !cfile.eof())
		{
			//reads number of lines & takes care of emtpy lines as well, except eof
			if (!textline.empty())
			{
				if (getConfig(textline, neta) == true)
					count += 1;
				else
					count = count;
			}
			else
				count = count;
		}



		if (count == 0)
		{
			throw EMPTYFILE;
		}

	}
	else
	{
		throw NOFILE;
	}

	cfile.close();
}


void readDataFile(std::ifstream & dfile, std::string datafile, Network * neta)
{

	std::string textline;
	int count = 0;
	dfile.open(datafile);
	int newcount = 0;

	//first round just counts # of lines to get i/o pairs
	if ((dfile.is_open()))
	{
		while (getline(dfile, textline) && !dfile.eof())
		{
			if (!textline.empty())
				count += 1;
			else
				count = count;
		}

		if ((count % 2) != 0)
			neta->setInputRow(count + 1); //really should be iopairs
		else
			neta->setInputRow(count);

		dfile.clear(); //needed so file can be read again
	}
	else
	{
		throw NOFILE;
	}

	//condition to let user know if issues w # of i/o pairs
	if (count == 0)
	{
		throw EMPTYFILE;
	}
	//else if (count % 2 != 0)
	//{
		//std::cout << "uneven i/o pairs\n   fix input file\n"; //FUNCTION NEEDS TO BE PERFECTED FOR THIS TO WORK
	//}
	else
	{

		dfile.seekg(0); //returns file position to 0 to be read again
		//dfile.clear(); //needed so file can be read again

		//this round gets data
		while (getline(dfile, textline))
		{

			//reads number of lines & takes care of emtpy lines as well, except eof
			if (!textline.empty())
			{
				newcount = newcount + 1; //so it counts before next function is called
				getData(textline, newcount - 1, neta);

			}
			else
				newcount = newcount;
		}
	}

	dfile.close();
}

bool getData(std::string extract, int row, Network * neta)
{
	//int alphacheck; //used to check for alphabet character and to convert string to int;
	bool returnvalue = false;
	const int LINESIZE = extract.size();
	const int COLUMNUM = 0;
	const int STARTINDEX = 0;

	neta->setInputColumn(COLUMNUM);

	if (extraccion(STARTINDEX, row, COLUMNUM, extract, neta))
		return true;
	else
		return false;


}

bool extraccion(int index, int row, int col, std::string extracto, Network * neta)
{
	bool returnvalue = false;
	const int LINESIZE = extracto.size();

	std::string inputdata = "";
	int i = index;


	while (i < LINESIZE)
	{
		//is digit takes care of space, comma, dot, and minus, and char
		//condiions to allow for dots and minus signs
		if ((extracto[i] != ',') && isdigit(extracto[i]) && ((i + 1) < LINESIZE)) //(extracto[i] == '.') && (extracto[i] == '-') && 
		{
			inputdata += extracto[i];
			i++;
			returnvalue = false;
		}
		else if ((i + 1) == LINESIZE)
		{

			inputdata += extracto[i];

			float floatinput = atof(inputdata.c_str());

			i++;
			assingData(row, col, floatinput, neta);
			col++;
			returnvalue = true;

		}
		else
		{
			i++;

			float floatinput = atof(inputdata.c_str());


			inputdata = "";
			assingData(row, col, floatinput, neta);
			col++;
			returnvalue = true;
		}
	}

	return returnvalue;
}


bool getConfig(std::string extract, Network * neta)
{
	int alphacheck; //used to check for alphabet characther and to convert string to int;
	bool returnvalue = false;
	const int LINESIZE = extract.size();
	std::string inputconstant = "";
	std::string cfgdata = "";

	for (int i = 0; i < LINESIZE; i++)
	{
		//takes care of constant name
		if ((extract[i] != ' ') && (extract[i] != ',')) //maybe add != '\n'
		{
			inputconstant += extract[i];
		}
		else
		{
			for (int j = i + 1; j < LINESIZE; j++)
			{
				i = LINESIZE; //to prevent code going through loop again
			//checks for alphabet characters in number input
			//assigns number value to constant
				/*if ((extract[i] >= -1) && (extract[i] <= 255) && (extract[i] != '.') && (extract[i] != '-'))
				{
					alphacheck = extract[i];
					if (!isalpha(alphacheck))
						cfgdata += extract[i];
					else
						throw NOTANUMBER;
				}
				else
				{*/

				cfgdata += extract[j];
				//}
			}

		}
	}

	float floatdata = atof(cfgdata.c_str());
	//std::string dummystring = " 2.5";
	//std::string trickextract = cfgdata + dummystring;
	//std::string::size_type sz;     // alias of size_t

	//VALUE OF EE IS GETTING TRUNCATED (AT LEAST ON DISPLAY), FIX THIS LATER
	//float actualdata = std::stof(trickextract, &sz);
	//float dummyfloat = std::stof(trickextract.substr(sz));

	if (assignConstant(inputconstant, floatdata, neta))
	{
		//neta->displayVariables();
		return true;
	}
	else
		return false;


}

bool assignConstant(std::string constname, float constvalue, Network * neta)
{

	if (neta->setConfig(constname, constvalue))
		return true;
	else
		return false;

}

void assingData(int row, int col, float value, Network * neta)
{

	if (row < (neta->getInputRow() / 2))
	{
		neta->loadInput(row, col, value);
	}
	else
	{
		neta->loadOutput((row - (neta->getInputRow() / 2)), col, value);
	}

}