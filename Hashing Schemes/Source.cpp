#include <iostream>
#include <string>
#include <iomanip>
#include "Chaining.h"
#include "LinearProbing.h"
#include "DoubleHashing.h"

int hashScheme();
int menu();
bool isPrime(int capacity);
void checkLoadFactor(Chaining<int, countyData>, float loadTime, float loadFactor);
void checkLoadFactor(LinearProbing<int, countyData> map, float loadTime, float loadFactor);
void checkLoadFactor(DoubleHashing<int, countyData> map, float loadTime, float loadFactor);

int main()
{
	int choice = 0, hashChoice = 0;

	do {
		hashChoice = hashScheme();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		switch (hashChoice)
		{
		case 1:
		{
			std::cout << "Using Chain Hashing...\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			std::cout << "\nPlease enter input data file: ";
			std::string inputDataFile;
			std::cin >> inputDataFile;
			inputDataFile = "C:\\Users\\jorge\\Desktop\\" + inputDataFile;
			std::ifstream entryFile;
			entryFile.open(inputDataFile);
			if (entryFile.fail())
			{
				std::cout << "Error: File not found\n";
				exit(1);
			}
			std::string line;
			std::stringstream ss(line);
			std::getline(entryFile, line);
			int capacity = std::stoi(line);
			std::cout << "Please enter desired load factor: ";
			float loadFactor;
			std::cin >> loadFactor;
			int tableSize = (float)capacity / loadFactor;
			while (isPrime(tableSize) != true)
				tableSize++;
			Chaining<int, countyData> chainHash(tableSize);
			Chaining<int, countyData>::Iterator chainHashIt = chainHash.begin();
			std::vector<int> currentCodes;

			std::string  countyCodeS, countyPopulationS, countyName;
			while (std::getline(entryFile, line))
			{
				std::stringstream ss(line);
				std::getline(ss, countyCodeS, ',');
				std::getline(ss, countyPopulationS, ',');
				std::getline(ss, countyName, '\t');
				int countyCode = std::stoi(countyCodeS);
				int countyPopulation = std::stoi(countyPopulationS);
				chainHash.put(countyCode, countyData(countyPopulation, countyName));
				currentCodes.push_back(countyCode);
			}
			std::cout << "Table size: " << chainHash.getTableSize() << "\n";
			std::cout << "Total probes: " << chainHash.getTotalProbes() << "\n";
			std::cout << "Average number of probes: " << chainHash.getTotalProbes() / chainHash.size() << "\n";
			std::cout << "Max number of probes for worst case: " << chainHash.getWorstProbe() << "\n";
			entryFile.close();
			do {
				choice = menu();
				switch (choice)
				{
				case 1:
				{
					std::cin.ignore();
					int code;
					std::cout << "Enter the county's code: ";
					std::cin >> code;
					bool isCode = false;
					for (int i = 0; i < currentCodes.size(); i++)
						if (currentCodes[i] == code)
							isCode = true;
					if (isCode == false)					
						std::cout << "Error: Code not found\n";
					else {
						chainHashIt = chainHash.find(code);
						std::cout << "Total Probes: " << chainHash.getCurrentProbe() << "\n";
						std::cout << "Code\tName\t\t\t Population\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
						std::cout << std::setw(8) << std::left << (*chainHashIt).key() << std::setw(25) << std::left << (*chainHashIt).value().getCountyName() << (*chainHashIt).value().getCountyPopulation() << "\n";
					}
					break;
				}
				case 2:
				{
					std::cin.ignore();
					std::string countyName;
					int countyCode, countyPopulation;
					std::cout << "Please enter a code for the county: ";
					std::cin >> countyCode;
					std::cout << "Please enter the population for the county: ";
					std::cin >> countyPopulation;
					std::cout << "Please enter a name for the county: ";
					std::cin.ignore();
					std::getline(std::cin, countyName);
					chainHash.put(countyCode, countyData(countyPopulation, countyName));
					checkLoadFactor(chainHash, (float)chainHash.size(), loadFactor);
					currentCodes.push_back(countyCode);
					std::cout << "Total Probes: " << chainHash.getCurrentProbe() << "\n";
					break;
				}
				case 3:
				{
					std::cin.ignore();
					int code;
					std::cout << "Enter the county's code: ";
					std::cin >> code;
					Chaining<int, countyData>::Iterator deleteRecord = chainHash.find(code);
					bool isCode = false;
					for (int i = 0; i < currentCodes.size(); i++)
						if (currentCodes[i] == code)
						{
							currentCodes.erase(currentCodes.begin() + i);
							chainHash.erase(deleteRecord);
							isCode = true;
						}
					if (isCode == false)
					{
						std::cout << "Error: Code not found\n";
					}
					else
					{
						std::cout << "Total Probes: " << chainHash.getCurrentProbe() << "\n";
						std::cout << "The county's data has been deleted!\n";
					}
					break;
				}
				case 4:
				{
					chainHashIt = chainHash.begin();
					std::cout << "Code\tName\t\t\t Population\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
					for (int i = 0; i < chainHash.size(); i++)
					{
						std::cout << std::setw(8) << std::left << (*chainHashIt).key() << std::setw(25) << std::left << (*chainHashIt).value().getCountyName() << (*chainHashIt).value().getCountyPopulation() << "\n";
						++chainHashIt;
					}
					break;
				}
				case 5:
				{
					std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nReturning to Hash Menu..."; break;
				}
				default: std::cout << "Please enter a valid option\n"; break;
				}
				std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			} while (choice != 5);
			break;
		}
		case 2: 
		{
			std::cout << "Using Linear Probe Hashing...\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			std::cout << "\nPlease enter input data file: ";
			std::string inputDataFile;
			std::cin >> inputDataFile;
			inputDataFile = "C:\\Users\\jorge\\Desktop\\" + inputDataFile;
			std::ifstream entryFile;
			entryFile.open(inputDataFile);
			if (entryFile.fail())
			{
				std::cout << "Error: File not found\nApplication closing...\n";
				system("pause");
				exit(1);
			}
			std::string line;
			std::stringstream ss(line);
			std::getline(entryFile, line);
			int capacity = std::stoi(line);
			std::cout << "Please enter desired load factor: ";
			float loadFactor;
			std::cin >> loadFactor;
			int tableSize = (float)capacity / loadFactor;
			while (isPrime(tableSize) != true)
				tableSize++;
			LinearProbing<int, countyData> linearHash(tableSize);
			LinearProbing<int, countyData>::Iterator linearHashIt = linearHash.begin();
			std::vector<int> currentCodes;

			std::string  countyCodeS, countyPopulationS, countyName;
			while (std::getline(entryFile, line))
			{
				std::stringstream ss(line);
				std::getline(ss, countyCodeS, ',');
				std::getline(ss, countyPopulationS, ',');
				std::getline(ss, countyName, '\t');
				int countyCode = std::stoi(countyCodeS);
				int countyPopulation = std::stoi(countyPopulationS);
				linearHash.put(countyCode, countyData(countyPopulation, countyName));
				currentCodes.push_back(countyCode);
			}
			std::cout << "Table size: " << linearHash.getTableSize() << "\n";
			std::cout << "Total probes: " << linearHash.getTotalProbes() << "\n";
			std::cout << "Average number of probes: " << linearHash.getTotalProbes() / linearHash.size() << "\n";
			std::cout << "Max number of probes for worst case: " << linearHash.getWorstProbe() << "\n";
			entryFile.close();
			do {
				choice = menu();
				switch (choice)
				{
				case 1:
				{
					std::cin.ignore();
					int code;
					std::cout << "Enter the county's code: ";
					std::cin >> code;
					bool isCode = false;
					for (int i = 0; i < currentCodes.size(); i++)
						if (currentCodes[i] == code)
							isCode = true;
					if (isCode == false)
						std::cout << "Error: Code not found\n";
					else {
						linearHashIt = linearHash.find(code);
						std::cout << "Total Probes: " << linearHash.getCurrentProbe() << "\n";
						std::cout << "Code\tName\t\t\t Population\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
						std::cout << std::setw(8) << std::left << (*linearHashIt).key() << std::setw(25) << std::left << (*linearHashIt).value().getCountyName() << (*linearHashIt).value().getCountyPopulation() << "\n";
					}
					break;
				}
				case 2:
				{
					std::cin.ignore();
					std::string countyName;
					int countyCode, countyPopulation;
					std::cout << "Please enter a code for the county: ";
					std::cin >> countyCode;
					std::cout << "Please enter the population for the county: ";
					std::cin >> countyPopulation;
					std::cout << "Please enter a name for the county: ";
					std::cin.ignore();
					std::getline(std::cin, countyName);
					linearHash.put(countyCode, countyData(countyPopulation, countyName));
					checkLoadFactor(linearHash, (float)linearHash.size(), loadFactor);
					currentCodes.push_back(countyCode);
					std::cout << "Total Probes: " << linearHash.getCurrentProbe() << "\n";
					break;
				}
				case 3:
				{
					std::cin.ignore();
					int code;
					std::cout << "Enter the county's code: ";
					std::cin >> code;
					bool isCode = false;
					for (int i = 0; i < currentCodes.size(); i++)
						if (currentCodes[i] == code)
						{
							currentCodes.erase(currentCodes.begin() + i);
							linearHash.erase(code);
							isCode = true;
						}
					if (isCode == false)
					{
						std::cout << "Error: Code not found\n";
					}
					else
					{
						std::cout << "Total Probes: " << linearHash.getCurrentProbe() << "\n";
						std::cout << "The county's data has been deleted!\n";
					}
					break;
				}
				case 4:
				{
					linearHashIt = linearHash.begin();
					std::cout << "Code\tName\t\t\t Population\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
					for (int i = 0; i < linearHash.size(); i++)
					{
						std::cout << std::setw(8) << std::left << (*linearHashIt).key() << std::setw(25) << std::left << (*linearHashIt).value().getCountyName() << (*linearHashIt).value().getCountyPopulation() << "\n";
						++linearHashIt;
					}
					break;
				}
				case 5:
				{
					std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nReturning to Hash Menu..."; break;
				}
				default: std::cout << "Please enter a valid option\n"; break;
				}
				std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			} while (choice != 5);
			break;
		}
		case 3:
		{
			std::cout << "Using Double Hashing...\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			std::cout << "\nPlease enter input data file: ";
			std::string inputDataFile;
			std::cin >> inputDataFile;
			inputDataFile = "C:\\Users\\jorge\\Desktop\\" + inputDataFile;
			std::ifstream entryFile;
			entryFile.open(inputDataFile);
			if (entryFile.fail())
			{
				std::cout << "Error: File not found\nApplication closing...\n";
				system("pause");
				exit(1);
			}
			std::string line;
			std::stringstream ss(line);
			std::getline(entryFile, line);
			int capacity = std::stoi(line);
			std::cout << "Please enter desired load factor: ";
			float loadFactor;
			std::cin >> loadFactor;
			int tableSize = (float)capacity / loadFactor;
			while (isPrime(tableSize) != true)
				tableSize++;
			DoubleHashing<int, countyData> doubleHash(tableSize);
			DoubleHashing<int, countyData>::Iterator doubleHashIt = doubleHash.begin();
			std::vector<int> currentCodes;

			std::string  countyCodeS, countyPopulationS, countyName;
			while (std::getline(entryFile, line))
			{
				std::stringstream ss(line);
				std::getline(ss, countyCodeS, ',');
				std::getline(ss, countyPopulationS, ',');
				std::getline(ss, countyName, '\t');
				int countyCode = std::stoi(countyCodeS);
				int countyPopulation = std::stoi(countyPopulationS);
				doubleHash.put(countyCode, countyData(countyPopulation, countyName));
				currentCodes.push_back(countyCode);
			}
			std::cout << "Table size: " << doubleHash.getTableSize() << "\n";
			std::cout << "Total probes: " << doubleHash.getTotalProbes() << "\n";
			std::cout << "Average number of probes: " << doubleHash.getTotalProbes() / doubleHash.size() << "\n";
			std::cout << "Max number of probes for worst case: " << doubleHash.getWorstProbe() << "\n";
			entryFile.close();
			do {
				choice = menu();
				switch (choice)
				{
				case 1:
				{
					std::cin.ignore();
					int code;
					std::cout << "Enter the county's code: ";
					std::cin >> code;
					bool isCode = false;
					for (int i = 0; i < currentCodes.size(); i++)
						if (currentCodes[i] == code)
							isCode = true;
					if (isCode == false)
						std::cout << "Error: Code not found\n";
					else {
						doubleHashIt = doubleHash.find(code);
						std::cout << "Total Probes: " << doubleHash.getCurrentProbe() << "\n";
						std::cout << "Code\tName\t\t\t Population\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
						std::cout << std::setw(8) << std::left << (*doubleHashIt).key() << std::setw(25) << std::left << (*doubleHashIt).value().getCountyName() << (*doubleHashIt).value().getCountyPopulation() << "\n";
					}
					break;
				}
				case 2:
				{
					std::cin.ignore();
					std::string countyName;
					int countyCode, countyPopulation;
					std::cout << "Please enter a code for the county: ";
					std::cin >> countyCode;
					std::cout << "Please enter the population for the county: ";
					std::cin >> countyPopulation;
					std::cout << "Please enter a name for the county: ";
					std::cin.ignore();
					std::getline(std::cin, countyName);
					doubleHash.put(countyCode, countyData(countyPopulation, countyName));
					checkLoadFactor(doubleHash, (float)doubleHash.size(), loadFactor);
					currentCodes.push_back(countyCode);
					std::cout << "Total Probes: " << doubleHash.getCurrentProbe() << "\n";
					break;
				}
				case 3:
				{
					std::cin.ignore();
					int code;
					std::cout << "Enter the county's code: ";
					std::cin >> code;
					bool isCode = false;
					for (int i = 0; i < currentCodes.size(); i++)
						if (currentCodes[i] == code)
						{
							currentCodes.erase(currentCodes.begin() + i);
							doubleHash.erase(code);
							isCode = true;
						}
					if (isCode == false)
					{
						std::cout << "Error: Code not found\n";
					}
					else
					{
						std::cout << "Total Probes: " << doubleHash.getCurrentProbe() << "\n";
						std::cout << "The county's data has been deleted!\n";
					}
					break;
				}
				case 4:
				{
					doubleHashIt = doubleHash.begin();
					std::cout << "Code\tName\t\t\t Population\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
					for (int i = 0; i < doubleHash.size(); i++)
					{
						std::cout << std::setw(8) << std::left << (*doubleHashIt).key() << std::setw(25) << std::left << (*doubleHashIt).value().getCountyName() << (*doubleHashIt).value().getCountyPopulation() << "\n";
						++doubleHashIt;
					}
					break;
				}
				case 5:
				{
					std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nReturning to Hash Menu..."; break;
				}
				default: std::cout << "Please enter a valid option\n"; break;
				}
				std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			} while (choice != 5);
			break;
		}
		case 4: break;
		default: std::cout << "Please enter a valid option\n"; break;
		}
	} while (hashChoice != 4);

	system("pause");
	return 0;
}

int hashScheme()
{
	int choice;
	std::cout << "          Hash Menu\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "1) Chain Hashing\n";
	std::cout << "2) Linear Probe Hashing\n";
	std::cout << "3) Double Hashing\n";
	std::cout << "4) Exit Program\n";
	std::cout << "Enter hashing scheme to use: ";
	std::cin >> choice;
	return choice;
}

int menu()
{
	int choice;
	std::cout << "\n         Main Menu\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "1) Search for a record\n";
	std::cout << "2) Insert a record\n";
	std::cout << "3) Delete a record\n";
	std::cout << "4) List all records\n";
	std::cout << "5) Exit to Hash Menu\n";
	std::cout << "Please enter any choice: ";
	std::cin >> choice;
	return choice;
}

bool isPrime(int capacity)
{
	int flag = 1;
	for (int i = 2; i <= sqrt(capacity); i++) {
		if (capacity % i == 0) {
			flag = 0;
			break;
		}
	}

	if (flag == 1) {
		return true;
	}
	else {
		return false;
	}
}

void checkLoadFactor(Chaining<int, countyData> map, float loadTime, float loadFactor)
{
	int tableSize = map.size() / loadFactor;
	bool isSameTableSize = false;
	while (isPrime(tableSize) != true)
		tableSize++;
	if (tableSize == map.getTableSize())
		isSameTableSize = true;
	if (loadTime > loadFactor && isSameTableSize == false) {
		Chaining<int, countyData> tempMap(map.size() / loadFactor);
		Chaining<int, countyData>::Iterator p = map.begin();
		for (int i = 0; i < map.getTableSize(); i++)
		{
			int countyCode = (*p).key();
			int countyPopulation = (*p).value().getCountyPopulation();
			std::string countyName = (*p).value().getCountyName();
			tempMap.put(countyCode, countyData(countyPopulation, countyName));
			++p;
		}
		map = tempMap;
	}
}

void checkLoadFactor(LinearProbing<int, countyData> map, float loadTime, float loadFactor)
{
	int tableSize = map.size() / loadFactor;
	bool isSameTableSize = false;
	while (isPrime(tableSize) != true)
		tableSize++;
	if (tableSize == map.getTableSize())
		isSameTableSize = true;
	if (loadTime > loadFactor && isSameTableSize == false) {
		LinearProbing<int, countyData> tempMap(map.size() / loadFactor);
		LinearProbing<int, countyData>::Iterator p = map.begin();
		for (int i = 0; i < map.getTableSize(); i++)
		{
			int countyCode = (*p).key();
			int countyPopulation = (*p).value().getCountyPopulation();
			std::string countyName = (*p).value().getCountyName();
			tempMap.put(countyCode, countyData(countyPopulation, countyName));
			++p;
		}
		map = tempMap;
	}
}

void checkLoadFactor(DoubleHashing<int, countyData> map, float loadTime, float loadFactor)
{
	int tableSize = map.size() / loadFactor;
	bool isSameTableSize = false;
	while (isPrime(tableSize) != true)
		tableSize++;
	if (tableSize == map.getTableSize())
		isSameTableSize = true;
	if (loadTime > loadFactor && isSameTableSize == false) {
		DoubleHashing<int, countyData> tempMap(map.size() / loadFactor);
		DoubleHashing<int, countyData>::Iterator p = map.begin();
		for (int i = 0; i < map.getTableSize(); i++)
		{
			int countyCode = (*p).key();
			int countyPopulation = (*p).value().getCountyPopulation();
			std::string countyName = (*p).value().getCountyName();
			tempMap.put(countyCode, countyData(countyPopulation, countyName));
			++p;
		}
		map = tempMap;
	}
}