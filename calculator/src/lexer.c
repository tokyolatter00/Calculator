
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/lexer.h"
#include "include/token.h"

#define IS_DIGIT(chr)			(isdigit(chr) || chr == '.')

/*
	Advance to the next character in the source string
*/

static inline void Advance(Lexer* lexer) {
	lexer->Char = lexer->Length > ++lexer->Index
		? lexer->Source[lexer->Index]
		: NULL;
}

/*
	Peeks ahead of the current character in the source string by an offset
*/

static inline char PeekNext(Lexer* lexer, uint64 offset) {
	return lexer->Length > lexer->Index + offset
		? lexer->Source[lexer->Index + offset]
		: NULL;
}

/*
	Advance then build a token
*/

static inline Token* AdvanceWith(Lexer* lexer, TokenType type) {
	Advance(lexer);
	return TokenInit(NULL, type);
}

/*
	Skips any whitespace characters
*/

static inline void SkipWhitespace(Lexer* lexer) {
	while (isspace(lexer->Char)) {
		Advance(lexer);
	}
}

/*
	Scans the length of a number before it is built
*/

static uint64 ScanNumberLength(Lexer* lexer, uint32* decimals) {
	uint64 length = 0;
	uint64 offset = 0;
	uint32 _decimals = 0;
	char chr = lexer->Char;

	while (IS_DIGIT(chr)) {
		if (chr == '.') {
			_decimals++;

			if (_decimals > 1) {
				// Error, number cannot have more than 1 decimal point
				break;
			}
		}

		length++;
		offset++;
		chr = PeekNext(lexer, offset);
	}

	*decimals = _decimals;
	return length;
}

/*
	Build a number based token
*/

static Token* BuildNumber(Lexer* lexer) {
	uint32 decimals;
	uint64 length = ScanNumberLength(lexer, &decimals);
	uint64 index = 0;
	char* buffer = malloc(length + 1);

	while (IS_DIGIT(lexer->Char)) {
		buffer[index++] = lexer->Char;
		Advance(lexer);
	}
	
	buffer[index] = '\0';

	// If decimals is greater than 0 then it is a floating point number

	if (decimals == 0) {
		return TokenInit(buffer, TOKEN_TYPE_INT);
	}
	else {
		return TokenInit(buffer, TOKEN_TYPE_FLOAT);
	}
}

/*
	Build the next token
*/

static Token* GetNextToken(Lexer* lexer) {
	SkipWhitespace(lexer);

	switch (lexer->Char) {
		case CHAR_PLUS:
			return AdvanceWith(lexer, TOKEN_TYPE_PLUS);
		case CHAR_MINUS:
			return AdvanceWith(lexer, TOKEN_TYPE_MINUS);
		case CHAR_MULTIPLY:
			return AdvanceWith(lexer, TOKEN_TYPE_MULTIPLY);
		case CHAR_DIVIDE:
			return AdvanceWith(lexer, TOKEN_TYPE_DIVIDE);
		case CHAR_LPAREN:
			return AdvanceWith(lexer, TOKEN_TYPE_LPAREN);
		case CHAR_RPAREN:
			return AdvanceWith(lexer, TOKEN_TYPE_RPAREN);
		case CHAR_NULL:
			return AdvanceWith(lexer, TOKEN_TYPE_EOF);
	}

	if (IS_DIGIT(lexer->Char)) {
		return BuildNumber(lexer);
	}

	// Syntax Error
}

/*
	Create a Lexer struct
*/

Lexer* LexerInit(char* source) {
	Lexer* lexer = calloc(1, sizeof(Lexer));
	lexer->Source = source;
	lexer->Char = source[0];
	lexer->Length = strlen(source);
	lexer->Index = 0;

	return lexer;
}

/*
	Build a token array from a Lexer's source string
*/

TokenArray* LexerGetResult(Lexer* lexer) {
	TokenArray* arr = TokenArrayInit();
	TokenType token_type;
	
	do {
		Token* token = GetNextToken(lexer);
		token_type = token->Type;

		TokenArrayAppend(arr, *token);
		free(token); // Token has been loaded to the token array so it is OK to delete
	} while (token_type != TOKEN_TYPE_EOF);

	return arr;
}

/*
	Delete a Lexer struct
*/

inline void LexerDelete(Lexer* lexer) {
	free(lexer);
}
