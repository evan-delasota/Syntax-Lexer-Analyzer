#include "Lexer.h"

// Reads incoming stream of tokens
void Lexer::readNext() {
	if (currToken != Token::$) {
		currToken = getToken();
		TokenText = tokenBuffer;
	}
}

// Analyzes and returns token/lexeme pair
Token Lexer::getToken() {
	std::string s;
	std::istream& input = *sourceInput;
	tokenBuffer.clear();
	char character = input.get();

	while (isspace(character)) {
		character = input.get();
	}

	if (!input) {
		return Token::$;
	}

	if (isalpha(character)) {
		tokenBuffer = character;
		character = input.get();

		while (isalnum(character)) {
			tokenBuffer += character;
			character = input.get();
		}
	input.putback(character);

	std::cout << "Token: Identifier		Lexeme: " << tokenBuffer << "\n";
	if (tokenBuffer == ";") return Token::Semicolon;

	return Token::Id;

	}

	//Checking if it's a number
	if (isdigit(character)) {
		tokenBuffer = character;
		character = input.get();

		while (isdigit(character)) {
			tokenBuffer += character;
			character = input.get();
		}

		if (character == '.') {
			tokenBuffer += character;
			character = input.get();

			while (isdigit(character)) {
				tokenBuffer += character;
				character = input.get();
			}
		}

		std::cout << "Token: Number			Lexeme: " << tokenBuffer << "\n";
		input.putback(character);
		return Token::Num;
	}
	// If number starts with decimal
	if (character == '.') {
		tokenBuffer = character;
		character = input.get();

		if (!isdigit(character)) {
			std::cout << "Logical Error\n";
			return Token::$;
		}

		while (isdigit(character)) {
			tokenBuffer += character;
			character = input.get();
		}
		std::cout << "Token: Number			Lexeme: " << tokenBuffer << "\n";


		input.putback(character);
		return Token::Num;
	}

	tokenBuffer = character;
	switch (character) {
		case '=':
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '^':
		case '(':
		case ')':
			std::cout << "Token: Operator			Lexeme: " << tokenBuffer << "\n";
			return Token(character);
	}

	if (character == '$' || character == ';') {
		if (character == ';') {
			std::cout << "Token: Semicolon		Lexeme: " << tokenBuffer << "\n";
		}
		return Token::$;
	}

	throw ("Not a valid input\n");

}
