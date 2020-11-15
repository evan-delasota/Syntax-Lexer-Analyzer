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

	if (tokenBuffer == "Int") return Token::Int;

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
			return Token(character);
	}

	std::cout << "Not a valid input\n";
	return Token::$;

}
