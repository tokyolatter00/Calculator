
#include <stdio.h>
#include <stdlib.h>
#include "include/ast.h"

// Number Node

/*
	Create a NumberNode struct
*/

NumberNode* NumberNodeInit(char* value, NumberType type, UnaryType unary) {
	NumberNode* node = calloc(1, sizeof(NumberNode));
	node->Value = value;
	node->Type = type;
	node->Unary = unary;

	return node;
}

/*
	Switch the sign of a number
	- Positive -> Negative
	- Negative -> Positive
*/

void NumberNodeSwitchUnary(NumberNode* node) {
	switch (node->Unary) {
		case UNARY_TYPE_POSITIVE:
			node->Unary = UNARY_TYPE_NEGATIVE;
			break;
		case UNARY_TYPE_NEGATIVE:
			node->Unary = UNARY_TYPE_POSITIVE;
			break;
	}
}

/*
	Delete a NumberNode struct
*/

inline void NumberNodeDelete(NumberNode* node) {
	printf("Freeing: [%s]\n", node->Value);
	free(node->Value);
	printf("Freed\n");
	free(node);
}

// Binary Operation Node

/*
	Create a BinOpNode struct
*/

BinOpNode* BinOpNodeInit(struct _AstNode* left, struct _AstNode* right, OperatorType _operator) {
	BinOpNode* node = calloc(1, sizeof(BinOpNode));
	node->Left = left;
	node->Right = right;
	node->Operator = _operator;

	return node;
}

/*
	Switch the sign of a binary operation
	- Positive -> Negative
	- Negative -> Positive
*/

void BinOpNodeSwitchUnary(BinOpNode* binop) {
	switch (binop->Unary) {
		case UNARY_TYPE_POSITIVE:
			binop->Unary = UNARY_TYPE_NEGATIVE;
			break;
		case UNARY_TYPE_NEGATIVE:
			binop->Unary = UNARY_TYPE_POSITIVE;
			break;
	}
}

/*
	Delete a BinOpNode struct
*/

inline void BinOpNodeDelete(BinOpNode* node) {
	AstNodeDelete(node->Left);
	AstNodeDelete(node->Right);
	free(node);
}

// Ast Node

/*
	Create an AstNode struct wrapped around a NumberNode struct
*/

AstNode* AstNodeNumberInit(char* value, NumberType type, UnaryType unary) {
	AstNode* node = calloc(1, sizeof(AstNode));
	node->Option.Number = NumberNodeInit(value, type, unary);
	node->Type = AST_NODE_TYPE_NUMBER;

	return node;
}

/*
	Create an AstNode struct wrapped around a BinOpNode struct
*/

AstNode* AstNodeBinOpInit(struct _AstNode* left, struct _AstNode* right, OperatorType _operator) {
	AstNode* node = calloc(1, sizeof(AstNode));
	node->Option.BinOp = BinOpNodeInit(left, right, _operator);
	node->Type = AST_NODE_TYPE_BINOP;

	return node;
}

/*
	Delete an AstNode struct
*/

inline void AstNodeDelete(AstNode* node) {
	switch (node->Type) {
		case AST_NODE_TYPE_NUMBER:
			NumberNodeDelete(node->Option.Number);
			break;
		case AST_NODE_TYPE_BINOP:
			BinOpNodeDelete(node->Option.BinOp);
			break;
	}

	free(node);
}

// Serialisation

/*
	Serialise an OperatorType
*/

char* OperatorToString(TokenType _operator) {
	switch (_operator) {
		case TOKEN_TYPE_PLUS:
			return "+";
		case TOKEN_TYPE_MINUS:
			return "-";
		case TOKEN_TYPE_MULTIPLY:
			return "*";
		case TOKEN_TYPE_DIVIDE:
			return "/";
	}
}

/*
	Serialise a NumberNode
*/

char* NumberNodeToString(NumberNode* node) {
	return node->Value;
}

/*
	Serialise a BinOpNode
*/

char* BinOpNodeToString(BinOpNode* node) {
	char* leftstr = AstNodeToString(node->Left);
	char* rightstr = AstNodeToString(node->Right);
	char* opstr = OperatorToString(node->Operator);

	static char buffer[1024];
	snprintf(buffer, 1024, "(%s %s %s)", leftstr, opstr, rightstr);

	return buffer;
}

/*
	Serialsie an AstNode
*/

inline char* AstNodeToString(AstNode* node) {
	switch (node->Type) {
		case AST_NODE_TYPE_NUMBER:
			return NumberNodeToString(node->Option.Number);
		case AST_NODE_TYPE_BINOP:
			return BinOpNodeToString(node->Option.BinOp);
	}
}