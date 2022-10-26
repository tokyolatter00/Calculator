
#include <stdlib.h>
#include "include/token.h"

/*
	Create a Token struct, with a type and value
*/

Token* TokenInit(char* value, TokenType type) {
	Token* token = calloc(1, sizeof(Token));
	token->Type = type;
	token->Value = value;

	return token;
}
