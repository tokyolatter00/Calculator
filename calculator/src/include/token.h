
#pragma once

#define CHAR_PLUS				'+'
#define CHAR_MINUS				'-'
#define CHAR_MULTIPLY			'*'
#define CHAR_DIVIDE				'/'
#define CHAR_LPAREN				'('
#define CHAR_RPAREN				')'
#define CHAR_NULL				'\0'

/*

	Token Type

	- Represents the type of a token

*/

typedef enum _TokenType {
	TOKEN_TYPE_PLUS,
	TOKEN_TYPE_MINUS,
	TOKEN_TYPE_MULTIPLY,
	TOKEN_TYPE_DIVIDE,
	TOKEN_TYPE_LPAREN,
	TOKEN_TYPE_RPAREN,
	TOKEN_TYPE_INT,
	TOKEN_TYPE_FLOAT,
	TOKEN_TYPE_EOF
} TokenType;

/*

	Token

	- Represents a token in a source string

*/

typedef struct _Token {
	TokenType Type;
	char* Value;
} Token;

Token* TokenInit(char* value, TokenType type);
