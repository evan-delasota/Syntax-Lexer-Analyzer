#include <iostream>
#include <string>

#include "Parser.h"
#include "Lexer.h"

int main() {
	Parser parser;
	std::string output = "";

	std::cout << "Syntax Analyzer (Type exit or quit to stop the program)\n";
	std::cout << "Please enter an expression to be parsed: ";

	while (std::cin) {
		std::string string;
		std::getline(std::cin, string);
		if (!std::cin || string == "exit" || string == "quit") break;
		
		output = (!isnan(parser(string))) ? "Valid\n" : "Invalid\n";
		std::cout << output;

	}

	return 0;

}