#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <string>
#include <map>

class StandardTrie {
public:

	StandardTrie(std::string fileName) : _root(getNode()), wordsInTree(0)
	{ 
		std::ifstream USDec;
		std::string word;
		USDec.open("C:\\Users\\jorge\\Desktop\\" + fileName);
		if (USDec.fail())
		{
			std::cin.ignore();
			std::cout << "Error: File not found!\nPress enter key to exit...\n";
			std::getchar();
			exit(1);
		}
		else
		{
			std::cout << "Reading file and inserting words into trie...\n";
			while (USDec >> word)
			{
				word.erase(std::remove(word.begin(), word.end(), '.'), word.end());
				word.erase(std::remove(word.begin(), word.end(), ','), word.end());
				word.erase(std::remove(word.begin(), word.end(), ':'), word.end());
				word.erase(std::remove(word.begin(), word.end(), ';'), word.end());
				word.erase(std::remove(word.begin(), word.end(), '['), word.end());
				word.erase(std::remove(word.begin(), word.end(), ']'), word.end());
				word.erase(std::remove(word.begin(), word.end(), '('), word.end());
				word.erase(std::remove(word.begin(), word.end(), ')'), word.end());
				word.erase(std::remove(word.begin(), word.end(), '0'), word.end());
				word.erase(std::remove(word.begin(), word.end(), '1'), word.end());
				word.erase(std::remove(word.begin(), word.end(), '2'), word.end());
				word.erase(std::remove(word.begin(), word.end(), '3'), word.end());
				word.erase(std::remove(word.begin(), word.end(), '4'), word.end());
				word.erase(std::remove(word.begin(), word.end(), '5'), word.end());
				word.erase(std::remove(word.begin(), word.end(), '6'), word.end());
				word.erase(std::remove(word.begin(), word.end(), '7'), word.end());
				word.erase(std::remove(word.begin(), word.end(), '8'), word.end());
				word.erase(std::remove(word.begin(), word.end(), '9'), word.end());
				std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return std::tolower(c); });
				insert(word);
			}	
			USDec.close();
		}
	}

	StandardTrie() : _root(getNode()), wordsInTree(0) { }

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

	bool search(std::string word)
	{
		struct TrieNode *node = _root;
		for (int i = 0; i < word.length(); i++)
		{
			int index = word[i] - 'a';
			if (!node->children[index])
				return false;
			node = node->children[index];
		}
		return (node != NULL && node->isWord);
	}

	void isInTree(std::string word) {
		bool isAWord = search(word);
		if (isAWord)
		{
			std::cout << "Yes\n";
			std::cout << "Found " << word << " " << wordCount[word] << " times.\n";
		}
		else
			std::cout << "No\n";
	}

	void insert(std::string word)
	{
		if (!search(word)) {
			struct TrieNode *node = _root;
			for (int i = 0; i < word.length(); i++)
			{
				int index = word[i] - 'a';
				if (!node->children[index])
					node->children[index] = getNode();
				node = node->children[index];
			}
			node->isWord = true;
			wordCount[word] = 1;
			wordsInTree++;
		}
		else
		{
			int i = wordCount.at(word);
			i++;
			wordCount[word] = i;
		}
	}

	bool isEmpty()
	{
		for (int i = 0; i < 26; i++)
			if (_root->children[i])
				return false;
		return true;
	}

	TrieNode* erase(TrieNode* root, std::string word, int depth = 0)
	{
		if (!root)
			return NULL;

		if (depth == word.size()) {

			if (root->isWord)
				root->isWord = false;

			if (isEmpty()) {
				delete (root);
				root = NULL;
			}
			wordsInTree--;
			return root;
		}

		int index = word[depth] - 'a';
		root->children[index] =
			erase(root->children[index], word, ++depth);

		if (isEmpty() && root->isWord == false) {
			delete (root);
			root = NULL;
		}
		return root;
	}

	TrieNode* getRoot() { return _root; }

	int getTotalWords() { return wordsInTree; }

private: 
	TrieNode *_root;
	int wordsInTree;
	std::map<std::string, int> wordCount;
};