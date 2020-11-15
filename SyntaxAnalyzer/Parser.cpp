#include "Parser.h"

std::map<std::string, double> symbol_table;

// Overloading the () operator
double Parser::operator()(const std::string& string)
{
	std::istringstream iss(string);
	lexer = new Lexer(iss);
	double output = assignExpression();
	delete lexer;
	return output;

}

// Converts string to double
double Parser::toNum(const std::string& string) {
	std::istringstream iss(string);
	double d;

	iss >> d;
	return d;

}

// Checks for constants after the assignment operator
double Parser::assignExpression()
{
	Token token = lexer->getCurrToken();
	std::string tokenText = lexer->getTokenText();
	double output = addOrSubExpression();

	if (lexer->getCurrToken() == Token::Assign) {
		lexer->readNext();
		return symbol_table[tokenText] = addOrSubExpression();

	}
	return output;

}

// Checks for +, - tokens & performs calculation if necessary
double Parser::addOrSubExpression()
{
	double output = mulOrDivExpression();

	for (;;) {
		switch (lexer->getCurrToken()) {
		case Token::Plus:
			lexer->readNext();
			output += mulOrDivExpression();
			break;

		case Token::Minus:
			lexer->readNext();
			output -= mulOrDivExpression();

		default:
			return output;

		}
	}

}

// Checks for *, /, or % tokens & performs calculation if necessary
double Parser::mulOrDivExpression()
{
	double output = powerExpression();
	double d;

	for (;;) {
		switch (lexer->getCurrToken()) {
		case Token::Mul:
			lexer->readNext();
			output *= powerExpression();
			break;

		case Token::Div:
			lexer->readNext();
			d = powerExpression();
			output /= d;
			break;

		case Token::Mod:
			lexer->readNext();
			d = powerExpression();
			output = fmod(output, d);
			break;

		default:
			return output;

		}
	}

}

// Checks for power token & performs calculation if necessary
double Parser::powerExpression()
{
	double output = unaryExpression();
	
	if (lexer->getCurrToken() == Token::Pow) {
		lexer->readNext();
		double d = unaryExpression();
		return pow(output, d);

	}
	return output;

}

// Adds a sign if necessary
double Parser::unaryExpression()
{
	switch (lexer->getCurrToken()) {
	case Token::Plus:
		lexer->readNext();
		return +analyze();

	case Token::Minus:
		lexer->readNext();
		return -analyze();

	default: 
		return analyze();

	}
}

// Returns value of argument, checks for open parenthesis 
double Parser::getArg() {
	double d = 0;

	lexer->readNext();
	if (lexer->getCurrToken() != Token::Lparen) {
		std::cout << "Missing a '(' before function name.\n";
		return d;
	}

	lexer->readNext();
	d = addOrSubExpression();

	if (lexer->getCurrToken() != Token::Rparen) {
		std::cout << "Missing closing ')'\n";
		return d;
	}

	lexer->readNext();
	return d;

}

// Matches any valid operator, then recursively calls helper functions if necessary
double Parser::analyze()
{
	std::string tokenText = lexer->getTokenText();
	double d = 0;

	switch (lexer->getCurrToken()) {
	// Identifiers
	case Token::Id:
		lexer->readNext();
		return symbol_table[tokenText];
	// Numerical values	
	case Token::Num:
		lexer->readNext();
		return toNum(tokenText);
	// Subexpressions
	case Token::Lparen:
		lexer->readNext();
		d = addOrSubExpression();
		if (lexer->getCurrToken() != Token::Rparen) {
			std::cout << "Missing closing ')' in expression\n";
			break;
		}
		lexer->readNext();
		return d;

	case Token::Int:
		d = getArg();
		if (d < 0)		 return ceil(d);
		else			 return floor(d);
	default:
		return d;

	}

}
