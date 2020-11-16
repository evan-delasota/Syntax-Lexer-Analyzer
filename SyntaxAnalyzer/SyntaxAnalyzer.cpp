#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Parser.h"
//#include "Lexer.h"

int main() {
	Parser parser;
	std::string output = "";
	std::ifstream fileInput;
	fileInput.open("test.txt");

	std::stringstream ss;
	ss << fileInput.rdbuf();
	fileInput.close();
	try {
		output = (!isnan(parser(ss.str()))) ? "Valid\n" : "Invalid\n";
		std::cout << output;

	}
	catch (const char* error) {
		std::cout << error;
	}

	std::ofstream fileOutput("output.txt");
	fileOutput << output;
	return 0;

	// Uncomment for user input in CLI
	/*
	std::cout << "Syntax Analyzer (Type exit or quit to stop the program)\n";
	std::cout << "Please enter an expression to be parsed: ";

	while (std::cin) {
		std::string string;
		std::getline(std::cin, string);
		if (!std::cin || string == "exit" || string == "quit") break;
		
		output = (!isnan(parser(string))) ? "Valid\n" : "Invalid\n";
		std::cout << output;

	}
	*/
	return 0;

}