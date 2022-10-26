
#include <stdlib.h>
#include "include/parser.h"

#define FUNC_PTR(name)			AstNode*(name)(Parser*)
#define TRUE					1
#define FALSE					0

static AstNode* ParseExpr(Parser* parser);

/*
	Advance to the next token in the token list
*/

static inline void Advance(Parser* parser) {
	if (parser->Tokens->Length > ++parser->Index) {
		parser->Tkn = &parser->Tokens->Buffer[parser->Index];
	}
}

/*
	Check if a token's type is in an array of token types
*/

static inline int TokenIsType(Token* token, TokenType* ops, uint32 opslen) {
	for (uint32 i = 0; i < opslen; i++) {
		if (token->Type == ops[i]) {
			return TRUE;
		}
	}

	return FALSE;
}

/*
	Identify a factor
	e.g. Numbers, Signs (+/-), Opening to parenthesis
*/

static AstNode* ParseFactor(Parser* parser) {
	Token* token = parser->Tkn;

	if (token->Type == TOKEN_TYPE_INT) {
		Advance(parser);
		return AstNodeNumberInit(token->Value, NUMBER_TYPE_INT, UNARY_TYPE_POSITIVE);
	}
	else if (token->Type == TOKEN_TYPE_FLOAT) {
		Advance(parser);
		return AstNodeNumberInit(token->Value, NUMBER_TYPE_FLOAT, UNARY_TYPE_POSITIVE);
	}
	else if (token->Type == TOKEN_TYPE_PLUS) {
		Advance(parser);
		return ParseFactor(parser);
	}
	else if (token->Type == TOKEN_TYPE_MINUS) {
		Advance(parser);
		AstNode* node = ParseFactor(parser);
		
		switch (node->Type) {
			case AST_NODE_TYPE_NUMBER:
				NumberNodeSwitchUnary(node->Option.Number);
				break;
			case AST_NODE_TYPE_BINOP:
				BinOpNodeSwitchUnary(node->Option.BinOp);
				break;
		}

		return node;
	}
	else if (token->Type == TOKEN_TYPE_LPAREN) {
		Advance(parser);
		AstNode* node = ParseExpr(parser);
		Advance(parser); // Advance past TOKEN_TYPE_RPAREN, will fail if parenthesis are not closed
		
		return node;
	}
	
	// Syntax Error
}

/*
	Identify a binary operation
	e.g. 10 + 10, 5 + 5 * 30
*/

static AstNode* ParseBinOp(Parser* parser, FUNC_PTR(func), TokenType* ops, uint32 opslen) {
	AstNode* left = func(parser);

	while (TokenIsType(parser->Tkn, ops, opslen)) {
		Token* _operator = parser->Tkn;
		Advance(parser);
		AstNode* right = func(parser);

		left = AstNodeBinOpInit(left, right, _operator->Type, UNARY_TYPE_POSITIVE);
	}

	return left;
}

/*
	Identify a term
	Seperated from ParseExpr, as (* and /) takes priority of (+ and -)
	e.g. 10 * 10
*/

static AstNode* ParseTerm(Parser* parser) {
	const TokenType ops[2] = {
		TOKEN_TYPE_MULTIPLY,
		TOKEN_TYPE_DIVIDE
	};
	const uint32 opslen = 2;

	return ParseBinOp(parser, ParseFactor, ops, opslen);
}

/*
	Identify an expression
	e.g. 10 + 10
*/

static AstNode* ParseExpr(Parser* parser) {
	const TokenType ops[2] = {
		TOKEN_TYPE_PLUS,
		TOKEN_TYPE_MINUS
	};
	const uint32 opslen = 2;

	return ParseBinOp(parser, ParseTerm, ops, opslen);
}

/*
	Create a parser struct
*/

Parser* ParserInit(TokenArray* tokens) {
	Parser* parser = calloc(1, sizeof(Parser));
	parser->Tokens = tokens;
	parser->Tkn = &tokens->Buffer[0];
	parser->Index = 0;

	return parser;
}

/*
	Build an abstract syntax tree from a Parser's token list
*/

AstNode* ParserGetResult(Parser* parser) {
	return ParseExpr(parser);
}

/*
	Delete a Parser struct
*/

inline void ParserDelete(Parser* parser) {
	free(parser);
}
