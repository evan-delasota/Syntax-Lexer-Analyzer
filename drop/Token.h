#pragma once

enum class Token {
	Id,
	Num,
	Assign = '=',
	Plus = '+',
	Minus = '-',
	Mul = '*',
	Div = '/',
	Mod = '%',
	Pow = '^',
	Lparen = '(',
	Rparen = ')',
	Semicolon = ';',
	$ = -1		//EOF
};