#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <time.h>
#include <chrono> 
#include <algorithm>
#include "Entry.h"

template <typename K, typename V>
class Sorting {
public:
	typedef Entry<K, V> E;
	typedef std::vector<E> Vect;
	typedef typename Vect::iterator vIt;
	Vect vList;
public:
	Sorting(std::string file) : keyCompares(0), dataMoves(0)
	{
		std::ifstream entryFile;
		entryFile.open(file);
		if (entryFile.fail())
		{
			std::cout << "Error: File not found\n";
			std::cout << "Press enter key to exit...\n";
			std::getchar();
			exit(1);
		}
		K kValue;
		V vValue;
		std::vector<K> kValues;
		std::vector<V> vValues;
		while (entryFile >> kValue)
			kValues.push_back(kValue);
		entryFile.close();
		entryFile.open(file);
		while (entryFile >> vValue)
			vValues.push_back(vValue);
		for (int i = 0; i < kValues.size(); i++)
			vList.push_back(E((kValues[i]), vValues[i]));
		vListBackUp = vList;
		entryFile.close();
	}

	bool keyComparator(K a, K b) { keyCompares++; return a > b; }
	
	void insertionSort(Vect& v)
	{
		int prevValue;
		K key;
		for (int i = 1; i < v.size(); i++)
		{
			key = v[i].key();
			prevValue = i - 1;
			while (prevValue >= 0 && keyComparator(v[prevValue].key(), key))
			{
				v[prevValue + 1].setKey(v[prevValue].key());
				dataMoves++;
				prevValue = prevValue - 1;
			}
			v[prevValue + 1].setKey(key);
			dataMoves++;
		}
	}
	
	void mergeSort(Vect& S) 
	{
		int n = S.size();
		Vect v1(S); Vect* in = &v1; // initial input vector
		Vect v2(n); Vect* out = &v2; // initial output vector
		for (int m = 1; m < n; m *= 2) 
		{ // list sizes doubling
			for (int b = 0; b < n; b += 2 * m) 
			{ // beginning of list
				merge(*in, *out, b, m); // merge sublists
				dataMoves++;
			}
			std::swap(in, out); // swap input with output
			dataMoves = dataMoves + 3;
		}
		S = *in; // copy sorted array to S
	}
	
	void merge(Vect& in, Vect& out, int b, int m) 
	{
		int i = b; // index into run #1
		int j = b + m; // index into run #2
		int n = in.size();
		int e1 = std::min(b + m, n); // end of run #1
		int e2 = std::min(b + 2 * m, n); // end of run #2
		int k = b;
		while ((i < e1) && (j < e2)) {
			if (!(keyComparator(in[i].key(), in[j].key()))) // append smaller to S
				out[k++] = in[i++];
			else
				out[k++] = in[j++];
		}
		while (i < e1) // copy rest of run 1 to S
			out[k++] = in[i++];
		while (j < e2) // copy rest of run 2 to S
			out[k++] = in[j++];
	}

	void swapKeys(Vect& vect, int i, int j) {
		K temp = vect[i].key();
		vect[i].setKey(vect[j].key());
		vect[j].setKey(temp);
		dataMoves = dataMoves + 3;
	}

	int partition(Vect& vect, int left, int right) {
		K pivot = vect[right].key();
		int i = (left - 1);

		for (int j = left; j < right; j++) {
			if (vect[j].key() <= pivot) {
				i++;
				swapKeys(vect, i, j);
				keyCompares++;
			}
		}
		swapKeys(vect, i + 1, right);
		return (i + 1);
	}

	void quickSort(Vect& vect, int left, int right) {
		if (left < right) {
			int pivot = partition(vect, left, right);			
			quickSort(vect, left, pivot - 1);
			quickSort(vect, pivot + 1, right);
		}
	}

	int partition3(Vect& vect, int left, int right) {
		int midIndex = left + (right - left) / 2;
		K leftK = vect[left].key(), rightK = vect[right].key(), midK = vect[midIndex].key();
		int pivotIndex;

		if (keyComparator(leftK, rightK) && !keyComparator(leftK, midK) || !keyComparator(leftK, rightK) && keyComparator(leftK, midK))
			pivotIndex = left;
		else if (keyComparator(rightK, leftK) && !keyComparator(rightK, midK) || !keyComparator(rightK, leftK) && keyComparator(rightK, midK))
			pivotIndex = right;
		else
			pivotIndex = midIndex;

		K pivot = vect[pivotIndex].key();
		int i = (left - 1);

		for (int j = left; j < right; j++) {
			if (vect[j].key() <= pivot) {
				i++;
				swapKeys(vect, i, j);
				keyCompares++;
			}
		}
		swapKeys(vect, i + 1, right);
		return (i + 1);
	}

	void quickSort3(Vect& vect, int left, int right) {
		if (left < right) {
			int pivot = partition3(vect, left, right);
			quickSort(vect, left, pivot - 1);
			quickSort(vect, pivot + 1, right);
		}
	}

	void reset() { keyCompares = 0; dataMoves = 0; vList = vListBackUp; }

	int getKeyCompares() { return keyCompares; }
	int getDataMoves() { return dataMoves; }

	void printFL5(Vect v) {
		std::cout << "First 5 Values: ";
		for (int i = 0; i < 5; i++) {
			std::cout << (v[i]).key() << " ";
		}
		std::cout << "\nLast 5 Values: ";
		for (int i = v.size() - 5; i < v.size(); i++) {
			std::cout << (v[i]).key() << " ";
		}
		std::cout << "\n";
	}

private:
	int keyCompares, dataMoves;
	Vect vListBackUp;
};