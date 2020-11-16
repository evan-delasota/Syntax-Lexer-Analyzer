#pragma once

#include "Lexer.h"

class Parser
{
public:
	Parser() {};

	double operator() (const std::string&);
	double toNum(const std::string&);

private:
	Lexer* lexer;

	double assignExpression();
	double addOrSubExpression();
	double mulOrDivExpression();
	double powerExpression();
	double unaryExpression();
	double analyze();

};
