#pragma once

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <math.h>
#include <cctype>

#include "Token.h"

class Lexer {
public:
	inline Lexer(std::istream& istream) : sourceInput{ &istream }, okToDelete{ false } { init(); }
	inline Lexer(std::istream* streamPointer) : sourceInput{ streamPointer }, okToDelete{ true } { init(); }
	inline ~Lexer() { if (okToDelete) delete sourceInput; }
	
	inline Token getCurrToken() const { return currToken; }
	inline std::string getTokenText() const { return TokenText; }
	inline int getSymbolCount() const { return count; }
	
	void readNext();
	void printSymbolTable();
private:
	std::istream* sourceInput;
	bool okToDelete;
	Token currToken;
	std::string TokenText;
	
	inline void init() { currToken = getToken(); TokenText = getTokenText(); }

	Token getToken();
	std::string tokenBuffer;

	int memLocation = 5000;
	int count = 0;
	std::map<std::string, int> symbolMap;
	std::string symbolType[1000];
};


