
#pragma once

#include "containers.h"

/*

	Lexer

	- Performs lexical analysis on a source string
	- Generate a list of tokens

*/

typedef struct _Lexer {
	char* Source;
	char Char;
	uint64 Length;
	uint64 Index;
} Lexer;

Lexer* LexerInit(char* source);
TokenArray* LexerGetResult(Lexer* lexer);
extern inline void LexerDelete(Lexer* lexer);
