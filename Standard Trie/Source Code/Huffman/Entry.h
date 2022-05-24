#pragma once

class Entry {
public: 
	Entry(char c, int i) : character(c), count(i) { }
	Entry(char c) : character(c), count(1) { }
	Entry() : character(), count(-1) { }
	char getCharacter() { return character; } 
	int  getCount() { return count; } 
	void setCharacter(char c) { character = c; } 
	void setCount(int i) { count = i; } 
	void addToCount() { count++; }
private: 
	char character; 
	int count; 
};

class CodeEntry {
public:
	CodeEntry(char c, std::string i) : character(c), code(i) { }
	CodeEntry(char c) : character(c), code("1") { }
	CodeEntry() : character(), code("-1") { }
	char getCharacter() { return character; }
	std::string getCount() { return code; }
	void setCharacter(char c) { character = c; }
	void setCount(int i) { code = i; }
private:
	char character;
	std::string code;
};