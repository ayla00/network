#include "main.h"


void readConfigFile(std::ifstream &cfile, std::string configfile)
{
	int linenumber;
	std::string textline;
	int count = 0;
	cfile.open(configfile);

	if ((cfile.is_open()))
	{
		//linenumber = countLines(inputfile);
		//puts file at the beginning again so it can be re-read
		//inputfile.clear();

		Network info;

		while (getline(cfile, textline))
		{
			std::cout << "line " << textline << std::endl;
			//reads number of lines
			//if (!textline.empty())
			//{
				if (getConfig(textline, info) == true)
					count += 1;
				else
					count = count;
			//}
			//else
			//	count = count;
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

/*
void readDataFile(std::ifstream & dfile, std::string datafile)
{
	int linenumber;
	std::string textline;
	int count = 0;
	inputfile.open(datafile);

	if (inputfile.is_open())
	{
		//linenumber = countLines(inputfile);
		//puts file at the beginning again so it can be re-read
		//inputfile.clear();

		Network info;

		while (getline(inputfile, textline))
		{
			//reads number of lines
			if (!textline.empty())
			{
				if (getData(textline, info) == true)
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


		info.printList();
		std::cout << "\n\ntotal entries:\t" << info.CountEntries() << std::endl;

	}
	else
	{
		std::cout << "the file you entered cannot be found or does not exist\n";
		std::cout << "please enter a correct filename\n";
	}

	inputfile.close();
}

bool getData(std::string extract, Network & extractdata)
{
	int alphacheck; //used to check for alphabet characther and to convert string to int;
	bool returnvalue = false;
	const int LINESIZE = extract.size();

	std::string input = "";
	std::string otherdata = "";

	Network getdata;

	//ADD CONDITION HERE TO SPLIT THE PROCESSING IN HALF, AS THE  FIRST HALF OF INPUT FILES CONSISTS
	//OF TWO COLUMNS OF INPUT, AND THE LAST HALF IS THE OUTPUT, SO IT NEEDS TO BE SPLITTED

	for (int i = 0; i < LINESIZE; i++)
	{
		if (extract[i] != ' ')  //maybe add != '\n'
		{
			//checks for alphabet characters in number input
			if ((extract[i] >= -1) && (extract[i] <= 255))
			{
				alphacheck = extract[i];
				if (!isalpha(alphacheck))
					input += extract[i];
				else
					throw NOTINTEGER;
			}
			else
				input += extract[i];
		}
		else
		{
			alphacheck = stoi(input); //check this variables too

			//getinfo.id = alphacheck; CHANGE THIS TO NAME OF INPUT FOR NETWORK


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
		}
	}

}
*/

bool getConfig(std::string extract, Network & extractconfig)
{
	int alphacheck; //used to check for alphabet characther and to convert string to int;
	bool returnvalue = false;
	const int LINESIZE = extract.size();
	float configdata;

	std::string inputconstant = "";
	std::string cfgdata = "";

	//Network getconfig;
	std::cout << "extract string " << extract << std::endl;
	for (int i = 0; i < LINESIZE; i++)
	{
		//takes care of constant name
		if (extract[i] != ' ')  //maybe add != '\n'
		{
			inputconstant += extract[i];
		}
		else
		{
			for (int j = i + 1; j < LINESIZE; j++ )
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
				cfgdata += extract[i];
				std::cout << "extract " << cfgdata << std::endl;
			}

		}
	}

		std::cout << "inputconstant " << inputconstant << std::endl;
		std::cout << "you are in getConfig\n";
		//configdata = stof(cfgdata); //check this variables too
		//configdata = cfgdata;

		if (assignConstant(inputconstant, 1.5, extractconfig))
			return true;
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

bool assignConstant(std::string constname, float constvalue, Network &extractconfig)
{
	//Network netconst;
	std::cout << "constname " << constname << "\t constvalue " << constvalue << std::endl;

	if (extractconfig.setConfig(constname, constvalue))
		return true;
	else
		return false;

}
