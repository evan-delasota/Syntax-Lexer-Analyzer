#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Parser.h"

int main() {
	Parser parser;
	std::string output = "";
	std::ifstream fileInput;
	std::vector<std::string> expressions;
	std::string expressionSegment;
	fileInput.open("test.txt");

	std::stringstream ss;
	ss << fileInput.rdbuf();
	fileInput.close();

	while (std::getline(ss, expressionSegment, '\n')) {
		expressions.push_back(expressionSegment);
	}

	try {
		for (int i = 0; i < expressions.size(); ++i) {
			if (expressions.at(i) == " " || expressions.at(i) == "") {
				continue;

			} else {
				output = (!isnan(parser(expressions.at(i)))) ? "Valid Expression\n" : "Invalid Expression\n";
				std::cout << output;
				
				std::ofstream fileOutput("output.txt");
				fileOutput << output;
			}
		}
	}
	catch (const char* error) {
		std::cout << error;
	}

	
	system("pause");
	// Uncomment for user input in CLI
	/*
	std::cout << "Syntax Analyzer (Type exit or quit to stop the program)\n";
	std::cout << "Please enter an expression to be parsed: ";

	while (std::cin) {
		std::string string;
		std::getline(std::cin, string);
		if (!std::cin || string == "exit" || string == "quit") break;
		
		output = (!isnan(parser(ss.str()))) ? "Valid Expression\n" : "Invalid Expression\n";
		std::cout << output;

	}
	*/
	return 0;

}