/* Program: Standard Trie
Author: Jorge Aranda
Class: CSCI 230
Date: 5/3/20
Description: Implements standard trie. Driver takes in a file input from desktop
and then creates a trie with given txt file. Then brings you to a menu where you can
insert, delete, search, and get the total words in the trie.
I certify that the code below is my own work.
Exception(s): 
	word.erase(std::remove(word.begin(), word.end(), '.'), word.end());
	std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return std::tolower(c); });
	struct TrieNode
	{
		struct TrieNode *children[26];
		bool isWord;
		TrieNode() : isWord(false) { }
	};

	struct TrieNode *getNode(void)
	{
		struct TrieNode *node = new TrieNode;

		for (int i = 0; i < 26; i++)
			node->children[i] = NULL;

		return node;
	}
*/


#include "StandardTrie.h"

int menu();

int main() {
	std::string fileName;
	std::cout << "Please enter file name: ";
	std::cin >> fileName;
	StandardTrie trieTest(fileName);
	int choice;
	do {
		choice = menu();
		std::string word;
		switch (choice)
		{
		case 1: 
			std::cin.ignore();
			word;
			std::cout << "Enter a word to insert: ";
			std::cin >> word;
			if (trieTest.search(word))
				std::cout << "Error: Word already in trie\n";
			else {
				trieTest.insert(word);
				std::cout << word << " has been inserted!\n";
			}
			break;
		case 2:
			std::cin.ignore();
			std::cout << "Enter a word to remove: ";
			std::cin >> word;
			trieTest.erase(trieTest.getRoot(), word);
			std::cout << word << " has been removed!\n";
			break;
		case 3:
			std::cin.ignore();
			std::cout << "Enter a word to search: ";
			std::cin >> word;
			trieTest.isInTree(word);
			break;
		case 4:
			std::cout << "Total words in trie: " << trieTest.getTotalWords() << "\n";
			break;
		case 5:
			std::cout << "Thank you for using my program!\n";
			break;
		default:
			std::cout << "Error: Please enter a valid option\n";
			break;
		}

	} while (choice != 5);
	
	std::cin.ignore();
	std::cout << "Press enter key to exit...\n";
	std::getchar();
}

int menu()
{
	int choice = 0;
	std::cout << "\n~~~~~~~~~Menu~~~~~~~~~~~\n";
	std::cout << "1) Insert word\n";
	std::cout << "2) Remove word\n";
	std::cout << "3) Search for word\n";
	std::cout << "4) Total words in tree\n";
	std::cout << "5) Exit Program\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "Please enter any choice: ";
	std::cin >> choice;
	return choice;
}