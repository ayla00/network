#include "main.h"


void readConfigFile(std::ifstream &cfile, std::string configfile, Network * neta)
{
	//int linenumber;
	std::string textline;
	int count = 0;
	cfile.open(configfile);

	if ((cfile.is_open()))
	{
		//linenumber = countLines(inputfile);
		//puts file at the beginning again so it can be re-read
		//inputfile.clear();


		while (getline(cfile, textline) && !cfile.eof())
		{
			std::cout << "line " << textline << std::endl;

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
			std::cout << "the file is empty\n\n";
		}


		//info.printList();
		//std::cout << "\n\ntotal entries:\t" << info.CountEntries() << std::endl;

	}
	else
	{
		std::cout << "the file you entered cannot be found or does not exist\n";
		std::cout << "please enter a correct filename\n";
	}

	cfile.close();
}


void readDataFile(std::ifstream & dfile, std::string datafile, Network * neta)
{

	std::string textline;
	int count = 0;
	dfile.open(datafile);
	int newcount = 0;

	std::cout << "YOU ARE IN READDATA\n";
	//first round just counts # of lines to get i/o pairs
	if ((dfile.is_open()))
	{
		std::cout << "YOU ARE FIRST IFF COUNT\n";
		while (getline(dfile, textline) && !dfile.eof())
		{
			if (!textline.empty())
				count += 1;
			else
				count = count;
		}
		neta->setInputRow(count);
		std::cout << "row " << neta->getInputRow() << std::endl;
		dfile.clear(); //needed so file can be read again
	}
	else
	{
		std::cout << "the file you entered cannot be found or does not exist\n";
		std::cout << "please enter a correct filename\n";
	}

	//condition to let user know if issues w # of i/o pairs
	if (count == 0)
	{
		std::cout << "the file is empty\n\n";
	}
	else if (count % 2 != 0)
	{
		std::cout << "uneven i/o pairs\n   fix input file\n";
	}
	else
	{

		dfile.seekg(0); //returns file position to 0 to be read again
		//dfile.clear(); //needed so file can be read again
		
		//this round gets data
		while (getline(dfile, textline) && !dfile.eof())
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

			//extractdata.setInputRow(count);
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

	//std::string inputconstant = "";
	//std::string inputdata = "";
	//std::cout << "rows " << rowcount << std::endl;
	//Network getconfig;
	std::cout << "extract string " << extract << std::endl;
	neta->setInputColumn(COLUMNUM);

	if (extraccion(STARTINDEX, row, COLUMNUM, extract, neta))
	{
		//rownum = rownum + 1;
		return true;
	}
	else
		return false;




}

bool extraccion(int index, int row, int col, std::string extracto, Network * neta)
{
	bool returnvalue = false;
	const int LINESIZE = extracto.size();
	std::cout << "SIZE " << LINESIZE << std::endl;
	std::string inputdata = "";
	int i = index;


	//std::cout << "YOU ARE IN EXTRACCION\n";
	//std::cout << "total rows " << (neta->getInputRow() / 2) << std::endl;
	//std::cout << "rows " << row << std::endl;
	//std::cout << "columns " << col << std::endl;
	//std::cout << "YOU ARE IN if EXTRACCION\n";
	while (i < LINESIZE)
	{
		//std::cout << "YOU ARE IN for EXTRACCION\n";
		//takes care of constant name
		//if (((extracto[i] != ' ') || (extracto[i] != '\t')))// && ((i + 1) < LINESIZE) ) //maybe add != '\n'
		if (isdigit(extracto[i]) && ((i + 1) < LINESIZE))
		{

			//std::cout << "YOU ARE IN for if EXTRACCION\n";
			//std::cout << extracto[i] << std::endl;
			inputdata += extracto[i];
			i++;
			//countrow = 0;
		}
		else if ((i + 1) == LINESIZE)
		{
			//std::cout << extracto[i] << std::endl;
			inputdata += extracto[i];
			//std::cout << " input " << inputdata << std::endl;
			std::string dummystring = " 2.5";
			std::string trickextract = inputdata + dummystring;
			std::string::size_type sz;     // alias of size_t
			//std::cout << "inputdata " << inputdata << std::endl;

			float firstinput = std::stof(trickextract, &sz);
			float dummyfloat = std::stof(trickextract.substr(sz));
			i++;
			assingData(row, col, firstinput, neta);
			col++;

			//i = LINESIZE;
		}
		else
		{
			i++;
			std::cout << " else input " << inputdata << std::endl;
			std::string dummystring = " 2.5";
			std::string trickextract = inputdata + dummystring;
			std::string::size_type sz;     // alias of size_t
			std::cout << "inputdata " << inputdata << std::endl;

			float firstinput = std::stof(trickextract, &sz);
			float dummyfloat = std::stof(trickextract.substr(sz));

			inputdata = "";
			assingData(row, col, firstinput, neta);
			col++;
			//i = LINESIZE;
			//extraccion(i, row, col, extracto, extractdata);
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

				std::cout << "extract " << cfgdata << std::endl;
			}

		}
	}

	std::string dummystring = " 2.5";
	std::string trickextract = cfgdata + dummystring;
	std::string::size_type sz;     // alias of size_t

	//VALUE OF EE IS GETTING TRUNCATED (AT LEAST ON DISPLAY), FIX THIS LATER
	float actualdata = std::stof(trickextract, &sz);
	float dummyfloat = std::stof(trickextract.substr(sz));
	std::cout << "config data " << actualdata << std::endl;
	std::cout << "dummy # " << dummyfloat << std::endl;

	std::cout << "inputconstant " << inputconstant << std::endl;

	if (assignConstant(inputconstant, actualdata, neta))
	{
		neta->displayVariables();
		return true;
	}
	else
		return false;




	//getinfo.id = alphacheck; CHANGE THIS TO NAME OF INPUT FOR NETWORK


	/** SAVE THIS FOR LAST IF YOU HAVE TIME, THIS WILL CHECK FOR COMMA DELIMITED FILES
	for (int j = (i + 1); j < LINESIZE; j++) //starts at next value of i, since i is whitespace
	{
		i = LINESIZE; //to prevent loop from looking into other indexes

		if ((extract[j] != ' ') && ((j + 1) != LINESIZE))
			palabra += extract[j];
		else if ((extract[j] != ' ') && ((j + 1) == LINESIZE))
		{
			palabra += extract[j];
			//getinfo.data = checkCharLimit(palabra);

			if (extractdata.add(getdata.id, getdata.data))
				returnvalue = true;
			else
				returnvalue = false;

			return returnvalue; //code must be here to exit
		}

	}
	*/



}

bool assignConstant(std::string constname, float constvalue, Network * neta)
{
	//Network netconst;
	std::cout << "constname " << constname << "\t constvalue " << constvalue << std::endl;

	if (neta->setConfig(constname, constvalue))
		return true;
	else
		return false;

}

void assingData(int row, int col, float value, Network * neta)
{
	//std::cout << "row " << row << std::endl;
	//std::cout << "col " << col << std::endl;
	//std::cout << "value " << value << std::endl;
	//std::cout << "total row " << (neta->getInputRow() / 2) << std::endl;

	//std::cout << "pointer " << value << std::endl;
	if (row < (neta->getInputRow() / 2))
	{
		//std::cout << "YOU ARE IN ASSINGDATA IF\n";
		neta->loadInput(row, col, value);
	}
	else
	{
		//std::cout << "YOU ARE IN ASSINGDATA else\n";
		//std::cout << "row" << (neta->getInputRow() - row) << std::endl;
		neta->loadOutput((row - (neta->getInputRow() / 2)), col, value);
	}

}
