#include "Parser.h"

std::map<std::string, double> symbolTable;

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
		if (token != Token::Id) {
			throw ("Invalid assignment\n");
		}
		std::cout << "<Statement> -> <Compound> | <Assign> \n"
			<< "<Assign> -> <Identifier> = <Expression> \n\n";
		lexer->readNext();
		return symbolTable[tokenText] = addOrSubExpression();

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
			std::cout << "<Empty> -> Epsilon \n"
				<< "<TermPrime> -> * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty> \n"
				<< "<Empty> -> Epsilon \n"
				<< "<ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | <Empty> \n\n";
			lexer->readNext();
			output += mulOrDivExpression();
			break;

		case Token::Minus:
			std::cout << "<Empty> -> Epsilon \n"
				<< "<TermPrime > -> * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty> \n"
				<< "<Empty> -> Epsilon \n"
				<< "<ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | <Empty> \n\n";
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
			std::cout << "<Empty> -> Epsilon \n"
				<< "<ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> \n"
				<< "<ExpressionPrime> -> % <Term> <ExpressionPrime> | <Empty> \n\n";
			lexer->readNext();
			output *= powerExpression();
			break;

		case Token::Div:
			std::cout << "<Empty> -> Epsilon \n"
				<< "<ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> \n"
				<< "<ExpressionPrime> -> % <Term> <ExpressionPrime> | < Empty> \n\n";
			lexer->readNext();
			d = powerExpression();
			break;

		case Token::Mod:
			std::cout << "<Empty> -> Epsilon \n"
				<< "<ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> \n"
				<< "<ExpressionPrime> -> % <Term> <ExpressionPrime> | < Empty> \n\n";
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

// Matches any valid operator, then recursively calls helper functions if necessary
double Parser::analyze()
{
	std::string tokenText = lexer->getTokenText();
	double d = 0;

	switch (lexer->getCurrToken()) {
	// Identifiers
	case Token::Id:
		std::cout << "<Expression> -> <Term> <ExpressionPrime> \n"
			<< "<Term > -> <Factor> <TermPrime> \n"
			<< "<Factor> -> - <Primary> | <Primary> \n"
			<< "<Primary> -> <Identifier> | <Integer> | <Identifier> (<IDs>) | (<Expression>) | <Real> \n\n";
		lexer->readNext();
		return symbolTable[tokenText];
	// Numerical values	
	case Token::Num:
		std::cout << "<Factor> -> - <Primary> | <Primary> \n"
			<< "<Primary> -> <Identifier> | <Integer> \n\n";
		lexer->readNext();
		return toNum(tokenText);
	// Subexpressions
	case Token::Lparen:
		lexer->readNext();
		d = addOrSubExpression();
		if (lexer->getCurrToken() != Token::Rparen) {
			throw ("Missing closing ')' in expression\n");
			break;
		}
		lexer->readNext();
		return d;

	case Token::Semicolon:
		std::cout << "<Empty> -> Epsilon \n"
			<< "<TermPrime> -> * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty>\n"
			<< "<Empty> -> Epsilon \n"
			<< "<ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | <Empty>  \n"
			<< "<Empty> -> Epsilon \n\n";

	default:
		throw ("Invalid expression\n");

	}

}
