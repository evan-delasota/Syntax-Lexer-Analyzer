#pragma once

enum class Token {
	Id,
	Num,
	Int,
	Assign = '=',
	Plus = '+',
	Minus = '-',
	Mul = '*',
	Div = '/',
	Mod = '%',
	Pow = '^',
	Lparen = '(',
	Rparen = ')',
	$ = -1		//EOF
};