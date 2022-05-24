/* Program: Huffman Coding
Author: Jorge Aranda
Class: CSCI 230
Date: 5/3/20
Description: Implements huffman coding algorithm. Driver takes in a file input from desktop
and then creates a frequency table and huffman compression file with given txt file.
I certify that the code below is my own work.
Exception(s): Majority of HeapPriorityQueue.h,
Made many modifications to functions in order to work with how I implemented it
*/

#include "HuffmanCoding.h"

int main() {
	std::string fileName;
	std::cout << "Please enter file name: ";
	std::cin >> fileName;
	HuffmanCoding huffExample(fileName);
	std::cout << "\nFrequency Table\n~~~~~~~~~~~~~~~~\n";
	huffExample.printFrequencyTable();
	std::cout << "\nCompressed Code\n~~~~~~~~~~~~~~~~\n";
	huffExample.printHuffCodes();
	std::ofstream file;
	file.open("moneyOut.txt");
	std::cout << "\nWriting to moneyOut.txt...\n";
	huffExample.writeData(file);
	std::cout << "Closing file...\n";
	file.close();
	std::cin.ignore();
	std::cout << "Press the enter key to exit...\n";
	std::getchar();
}