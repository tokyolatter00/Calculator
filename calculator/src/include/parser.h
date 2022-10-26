
#pragma once

#include "containers.h"
#include "ast.h"

/*

	Parser

	- Parses through a list of tokens
	- Generates an abstract syntax tree

*/

typedef struct _Parser {
	TokenArray* Tokens;
	Token* Tkn;
	uint64 Index;
} Parser;

Parser* ParserInit(TokenArray* tokens);
AstNode* ParserGetResult(Parser* parser);
extern inline void ParserDelete(Parser* parser);
