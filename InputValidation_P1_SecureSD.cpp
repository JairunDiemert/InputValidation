#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <functional>
#include <algorithm>
#include <climits>

template <typename T>
bool getInputData(T& data)
{
	if (std::cin.peek() == '\n')
	{
		//Clear stream
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		return true;
	}
	std::cin >> data;

	//Error check
	if(!std::cin.good())
	{
		//Clear stream
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		return false;
	}
	//Clear stream
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	return true;
}
template <typename T>
bool getInputDataID(T& data)
{
	if (std::cin.peek() == '\n')
	{
		//Clear stream
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		return false;
	}
	std::cin >> data;

	//Error check
	if (!std::cin.good())
	{
		//Clear stream
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		return false;
	}
	//Clear stream
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	return true;
}
template <typename T>
bool getInputDataName(T& data)
{
	if (std::cin.peek() == '\n')
	{
		//Clear stream
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout <<"Program Terminated";
		_Exit(13);
	}
	std::cin >> data;

	//Error check
	if (!std::cin.good())
	{
		//Clear stream
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		return false;
	}
	//Clear stream
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	return true;
}

template <typename T>
bool unsignedIntInputValidation(T& data)
{
	long long int signCheck;
	if (!getInputDataID(signCheck)) return false;
		if (signCheck < 0 || signCheck > 65535)
		{
			return false;
		}
	data = signCheck;
	return true;
}
std::string random_string(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

void readFileAndAssignInfoToOutput(std::ifstream& inf, std::ofstream& outf, std::string& names, std::string& uwfIDs, std::string& altIDs)
{
	std::string name;
	std::string voterID;
	unsigned int votingStation;

	if (inf.is_open())
	{
		if (outf.is_open())
		{
			while (!std::getline(inf, name, ' ').eof())
			{
				std::string uwfID;
				std::string alternateID;
				std::getline(inf, uwfID, ' ');
				std::getline(inf, alternateID);
				outf << name << " ";
				outf << uwfID << " ";
				outf << alternateID << " ";
				voterID = random_string(16);
				outf << voterID << " ";
				votingStation = rand() % 9;
				outf << votingStation + 1 << "\n";

				names += name + " ";
				uwfIDs += uwfID + " ";
				altIDs += alternateID + " ";
			}
		}
		else std::cout << "Unable to open in file";
	}
	else std::cout << "Unable to open out file";
}
void addNewPersonToOutFile(std::ofstream& outf, std::string& name, unsigned int& uwfID, std::string& altID, 
						   std::string& voterID, unsigned int& votingStation, std::string& names, std::string& uwfIDs, std::string& altIDs)
{
	outf << name << " ";
	outf << uwfID << " ";
	outf << altID << " ";
	voterID = random_string(16);
	outf << voterID << " ";
	votingStation = rand() % 9;
	outf << votingStation + 1 << "\n";

	names += name + " ";
	uwfIDs += std::to_string(uwfID) + " ";
	altIDs += altID + " ";

	std::cout << name << " is assigned VoterID " << voterID << " at Voting Station " << votingStation + 1 << "\n\n";
}
int main()
{	
	srand((unsigned int)time(NULL));

	bool pass = false;
	char choice;
	std::string name;
	unsigned int uwfID;
	std::string altID;
	std::string voterID;
	unsigned int votingStation;

	std::string names;
	std::string uwfIDs;
	std::string altIDs;

	std::ifstream inf("input.dat");
	std::ofstream outf("output.dat");

	readFileAndAssignInfoToOutput(inf, outf, names, uwfIDs, altIDs);
	std::cout << "Welcome to Voting Registration" << "\n";
	while (!pass)
	{	
		name = "";
		uwfID = 0;
		altID = "";
		pass = true;
		std::cout << "Name> ";
		if ((!getInputDataName(name))) pass = false;
		else if (names.find(name) != std::string::npos) pass = false;
		std::cout << "UWF ID> ";
		if (!unsignedIntInputValidation(uwfID)) pass = false;
		else if (uwfIDs.find(std::to_string(uwfID)) != std::string::npos) pass = false;
		std::cout << "Alternate ID> ";
		if (!getInputData(altID)) pass = false;
		if (!pass) std::cout << "Invalid input" << "\n\n";
		else
		{
			addNewPersonToOutFile(outf, name, uwfID, altID, voterID, votingStation, names, uwfIDs, altIDs);
			std::cout << "(e)xit || (c)ontinue > ";
			std::cin >> choice;
			if (std::cin.good() && ((choice == 'e') || (choice == 'E')))
			{
				//Clear stream
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				pass = true;
			}
			else
			{
				//Clear stream
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				pass = false;
			}
		}
	}
	inf.close();
	outf.close();
}
