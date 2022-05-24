#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "HeapPriorityQueue.h"

class HuffmanCoding {
public:
	HuffmanCoding(std::string file) {
		std::ifstream moneyText;
		char character;
		fileName = "C:\\Users\\jorge\\Desktop\\" + file;
		moneyText.open(fileName);
		if (moneyText.fail())
		{
			std::cin.ignore();
			std::cout << "Error: File not found!\nPress enter key to exit...\n";
			std::getchar();
			exit(1);
		}
		else
		{
			std::cout << "Reading file and creating frequency table...\n";
			while (moneyText.get(character))
			{
				int index = checkChar(character);
				if (index > -1)
					allChar[index].addToCount();
				else
					allChar.push_back(Entry(character));
				totalCharacters++;
			}
			std::cout << "Closing file...\n";
			moneyText.close();
		}
		std::cout << "Compressing text...\n";
		HuffmanCodes(allChar, huffCodes);
	}

	int checkChar(char c) {
		int index = -1;
		for (int i = 0; i < allChar.size(); i++) {
			if (allChar[i].getCharacter() == c)
				index = i;
		}
		return index;
	}

	void printFrequencyTable() {
		for (int i = 0; i < allChar.size(); i++)
			std::cout << allChar[i].getCharacter() << ":" << std::setw(7) << allChar[i].getCount() << "\n";
	}

	void printHuffCodes() {
		for (int i = 0; i < huffCodes.size(); i++)
			std::cout << huffCodes[i].getCharacter() << ":" << std::setw(7)<< huffCodes[i].getCount() << "\n";
	}
	int getTotalBits() {
		int totalBits = 0;
		for (int i = 0; i < allChar.size(); i++)
		{
			for (int j = 0; j < allChar.size(); j++)
			{
				int bits = 0;
				if (allChar[i].getCharacter() == huffCodes[j].getCharacter())
				{
					bits = allChar[i].getCount() * huffCodes[j].getCount().length();
				}
				totalBits = totalBits + bits;
			}
		}
		return totalBits;
	}

	std::string textToCode() {
		std::string text = "";
		char c;
		std::ifstream file;
		file.open(fileName);
		while (file.get(c))
		{
			int i = 0;
			while (c != huffCodes[i].getCharacter())
				i++;
			text = text + huffCodes[i].getCount();
		}
		file.close();
		return text;
	}

	void writeData(std::ofstream& file)
	{
		for (int i = 0; i < huffCodes.size(); i++)
			file << huffCodes[i].getCharacter() << ":" << std::setw(7) << huffCodes[i].getCount() << "\n";
		file << "**********\n";
		file << "Number of Characters: " << totalCharacters;
		file << "\nNumber of bits: " << getTotalBits() << "\n";
		file << textToCode();
	}

private:
	std::vector<Entry> allChar;
	std::vector<CodeEntry> huffCodes;
	std::string fileName;
	int totalCharacters;
};