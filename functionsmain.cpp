/*
Name: Astrid Lozano
Assignment: fINAL project

NOTES:
//reading any file assumes the format is the same for all incoming files (including variable names)
//for some reason there is one more space in the file that this code cannot deal with
*/
#include "main.h"


void readConfigFile(std::ifstream &cfile, std::string configfile, Network * neta)
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
			std::cout << "line " << textline << std::endl;

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

bool getData(std::string extract, int row, Network *  neta)
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

		if (isdigit(extracto[i]) && ((i + 1) < LINESIZE))
		{
			inputdata += extracto[i];
			i++;
		}
		else if ((i + 1) == LINESIZE)
		{

			inputdata += extracto[i];

			std::string dummystring = " 2.5";
			std::string trickextract = inputdata + dummystring;
			std::string::size_type sz;     // alias of size_t

			float firstinput = std::stof(trickextract, &sz);
			float dummyfloat = std::stof(trickextract.substr(sz));
			i++;
			assingData(row, col, firstinput, neta);
			col++;

		}
		else
		{
			i++;

			std::string dummystring = " 2.5";
			std::string trickextract = inputdata + dummystring;
			std::string::size_type sz;     // alias of size_t


			float firstinput = std::stof(trickextract, &sz);
			float dummyfloat = std::stof(trickextract.substr(sz));

			inputdata = "";
			assingData(row, col, firstinput, neta);
			col++;
		}
	}

	return returnvalue;
}


bool getConfig(std::string extract, Network * neta)
{
	//int alphacheck; //used to check for alphabet characther and to convert string to int;
	bool returnvalue = false;
	const int LINESIZE = extract.size();
	//float configdata;

	std::string inputconstant = "";
	std::string cfgdata = "";

	//Network getconfig;
	std::cout << "extract string " << extract << std::endl;
	for (int i = 0; i < LINESIZE; i++)
	{
		//takes care of constant name
		if (extract[i] != ' ') //maybe add != '\n'
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
			//if ((extract[i] >= -1) && (extract[i] <= 255))
			//{
			//	alphacheck = extract[i];
			//	if (!isalpha(alphacheck))
			//		cfgdata += extract[i];
			//	else
			//		throw NOTANUMBER;
		//	}
			//else
			//{
				cfgdata += extract[j];

			}

		}
	}

	std::string dummystring = " 2.5";
	std::string trickextract = cfgdata + dummystring;
	std::string::size_type sz;     // alias of size_t

	//VALUE OF EE IS GETTING TRUNCATED (AT LEAST ON DISPLAY), FIX THIS LATER
	float actualdata = std::stof(trickextract, &sz);
	float dummyfloat = std::stof(trickextract.substr(sz));

	if (assignConstant(inputconstant, actualdata, neta))
	{
		neta->displayVariables();
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