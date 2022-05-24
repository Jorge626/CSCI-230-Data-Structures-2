/* Program: Sorting Applications
Author: Jorge Aranda
Class: CSCI 230
Date: 4/20/20
Description: Implements quick sort with the last element and the median of three
as a pivot, as well as merge sort and insertion sort. Everything is implemented in a class
that takes an Entry key and value pair.
I certify that the code below is my own work.
Exception(s): Code Fragments
	auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
*/

#include "Sorting.h"

void writeDataToFile(std::ofstream& file, std::string algorithm, std::string fileName, Sorting<int, std::string> list, double runtime);
void writeDataToFile(std::ofstream& file, std::string algorithm, std::string fileName, Sorting<std::string, int> list, double runtime);

int main()
{
	std::cout << "Input File: small1k.txt\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	Sorting<int, std::string> smallIS("C:\\Users\\jorge\\Desktop\\small1k.txt");
	Sorting<std::string, int> smallSI("C:\\Users\\jorge\\Desktop\\small1k.txt");

	auto start = std::chrono::steady_clock::now();
	smallIS.insertionSort(smallIS.vList);
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;

	std::ofstream file;
	file.open("small1kOutput.txt");
	std::cout << "Writing to small1kOutput.txt...\n";

	std::string iS = "Insertion-Sort";
	std::string fNS = "small1k.txt";
	double runtime = std::chrono::duration <double, std::milli>(diff).count();

	writeDataToFile(file, iS, fNS, smallIS, runtime);
	smallIS.reset();

	start = std::chrono::steady_clock::now();
	smallIS.mergeSort(smallIS.vList);
	end = std::chrono::steady_clock::now();
	diff = end - start;

	std::string mS = "Merge-Sort";
	runtime = std::chrono::duration <double, std::milli>(diff).count();
	writeDataToFile(file, mS, fNS, smallIS, runtime);
	smallIS.reset();

	start = std::chrono::steady_clock::now();
	smallIS.quickSort(smallIS.vList, 0, smallIS.vList.size() - 1);
	end = std::chrono::steady_clock::now();
	diff = end - start;

	std::string qS = "Quick-Sort";
	runtime = std::chrono::duration <double, std::milli>(diff).count();
	writeDataToFile(file, qS, fNS, smallIS, runtime);
	smallIS.reset();


	start = std::chrono::steady_clock::now();
	smallIS.quickSort3(smallIS.vList, 0, smallIS.vList.size() - 1);
	end = std::chrono::steady_clock::now();
	diff = end - start;

	std::string qS3 = "Quick-Sort 3";
	runtime = std::chrono::duration <double, std::milli>(diff).count();
	writeDataToFile(file, qS3, fNS, smallIS, runtime);
	smallIS.reset();

	start = std::chrono::steady_clock::now();
	smallSI.insertionSort(smallSI.vList);
	end = std::chrono::steady_clock::now();
	diff = end - start;

	runtime = std::chrono::duration <double, std::milli>(diff).count();
	writeDataToFile(file, iS, fNS, smallSI, runtime);
	smallSI.reset();

	start = std::chrono::steady_clock::now();
	smallSI.mergeSort(smallSI.vList);
	end = std::chrono::steady_clock::now();
	diff = end - start;

	runtime = std::chrono::duration <double, std::milli>(diff).count();
	writeDataToFile(file, mS, fNS, smallSI, runtime);
	smallSI.reset();

	start = std::chrono::steady_clock::now();
	smallSI.quickSort(smallSI.vList, 0, smallSI.vList.size() - 1);
	end = std::chrono::steady_clock::now();
	diff = end - start;

	runtime = std::chrono::duration <double, std::milli>(diff).count();
	writeDataToFile(file, qS, fNS, smallSI, runtime);
	smallSI.reset();

	start = std::chrono::steady_clock::now();
	smallSI.quickSort3(smallSI.vList, 0, smallSI.vList.size() - 1);
	end = std::chrono::steady_clock::now();
	diff = end - start;

	runtime = std::chrono::duration <double, std::milli>(diff).count();
	writeDataToFile(file, qS3, fNS, smallSI, runtime);
	smallSI.reset();

	std::cout << "Closing small1kOutput.txt...\n";
	file.close();

	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nInput File: large100k.txt\n";
	Sorting<int, std::string> largeIS("C:\\Users\\jorge\\Desktop\\large100k.txt");
	Sorting<std::string, int> largeSI("C:\\Users\\jorge\\Desktop\\large100k.txt");

	file.open("large100kOutput.txt");
	std::cout << "Writing to large100kOutput.txt...\n";

	start = std::chrono::steady_clock::now();
	largeIS.mergeSort(largeIS.vList);
	end = std::chrono::steady_clock::now();
	diff = end - start;

	std::string fNL = "large100k.txt";
	runtime = std::chrono::duration <double, std::milli>(diff).count();
	writeDataToFile(file, mS, fNL, largeIS, runtime);
	largeIS.reset();

	start = std::chrono::steady_clock::now();
	largeIS.quickSort(largeIS.vList, 0, largeIS.vList.size() - 1);
	end = std::chrono::steady_clock::now();
	diff = end - start;

	runtime = std::chrono::duration <double, std::milli>(diff).count();
	writeDataToFile(file, qS, fNL, largeIS, runtime);
	largeIS.reset();

	start = std::chrono::steady_clock::now();
	largeIS.quickSort3(largeIS.vList, 0, largeIS.vList.size() - 1);
	end = std::chrono::steady_clock::now();
	diff = end - start;

	runtime = std::chrono::duration <double, std::milli>(diff).count();
	writeDataToFile(file, qS3, fNL, largeIS, runtime);
	largeIS.reset();

	start = std::chrono::steady_clock::now();
	largeSI.mergeSort(largeSI.vList);
	end = std::chrono::steady_clock::now();
	diff = end - start;
	largeSI.reset();

	runtime = std::chrono::duration <double, std::milli>(diff).count();
	writeDataToFile(file, mS, fNL, largeSI, runtime);
	largeSI.reset();

	start = std::chrono::steady_clock::now();
	largeSI.quickSort(largeSI.vList, 0, largeSI.vList.size() - 1);
	end = std::chrono::steady_clock::now();
	diff = end - start;

	runtime = std::chrono::duration <double, std::milli>(diff).count();
	writeDataToFile(file, qS, fNL, largeSI, runtime);
	largeSI.reset();

	start = std::chrono::steady_clock::now();
	largeSI.quickSort3(largeSI.vList, 0, largeSI.vList.size() - 1);
	end = std::chrono::steady_clock::now();
	diff = end - start;

	runtime = std::chrono::duration <double, std::milli>(diff).count();
	writeDataToFile(file, qS3, fNL, largeSI, runtime);
	largeSI.reset();

	std::cout << "Closing large100kOutput.txt...\n";
	file.close();

	std::cout << "\nPress the enter key to exit...\n";
	std::getchar();
	return 0;
}



void writeDataToFile(std::ofstream& file, std::string algorithm, std::string fileName, Sorting<int, std::string> list, double runtime)
{
	file << algorithm << "\n";
	file << "--------------\n";
	file << "Input file name: " << fileName;
	file << "\nNumber of values sorted: " << list.vList.size();
	file << "\nKey Data Type: int";
	file << "\nNumber of Key Compares: " << list.getKeyCompares();
	file << "\nRuntime: " << runtime << " ms";
	file << "\nFirst 5 Values: ";
	for (int i = 0; i < 5; i++) {
		file << (list.vList[i]).key() << " ";
	}
	file << "\nLast 5 Values: ";
	for (int i = list.vList.size() - 5; i < list.vList.size(); i++) {
		file << (list.vList[i]).key() << " ";
	}
	file << "\n\n";
}

void writeDataToFile(std::ofstream& file, std::string algorithm, std::string fileName, Sorting<std::string, int> list, double runtime)
{
	file << algorithm << "\n";
	file << "--------------\n";
	file << "Input file name: " << fileName;
	file << "\nNumber of values sorted: " << list.vList.size();
	file << "\nKey Data Type: std::string";
	file << "\nNumber of Key Compares: " << list.getKeyCompares();
	file << "\nRuntime: " << runtime << " ms";
	file << "\nFirst 5 Values: ";
	for (int i = 0; i < 5; i++) {
		file << (list.vList[i]).key() << " ";
	}
	file << "\nLast 5 Values: ";
	for (int i = list.vList.size() - 5; i < list.vList.size(); i++) {
		file << (list.vList[i]).key() << " ";
	}
	file << "\n\n";
}