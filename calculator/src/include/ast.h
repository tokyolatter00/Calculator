
#pragma once

#include "token.h"
#include "types.h"

// Number Node

/*
	
	Number Type

	- Represents the type of a number (integer/floating point)

*/

typedef enum _NumberType {
	NUMBER_TYPE_INT,
	NUMBER_TYPE_FLOAT
} NumberType;

/*
	
	Unary Type

	- Represents the sign of a number (positive/negative)

*/

typedef enum _UnaryType {
	UNARY_TYPE_POSITIVE,
	UNARY_TYPE_NEGATIVE
} UnaryType;


/*

	Number Node

	- Represents a number as a node
	- Contains the type, sign and string value of the number

*/

typedef struct _NumberNode {
	NumberType Type;
	UnaryType Unary;
	char* Value;
} NumberNode;

NumberNode* NumberNodeInit(char* value, NumberType type, UnaryType unary);
void NumberNodeSwitchUnary(NumberNode* node);
void NumberNodeDelete(NumberNode* node);

// Binary Operation Node

/*

	Operator Type

	- Represents the type of a mathematical operation
	- e.g. addition, subtraction, multiplication, division

*/

typedef enum _OperatorType {
	OPERATOR_TYPE_ADDITION = TOKEN_TYPE_PLUS,
	OPERATOR_TYPE_SUBTRACTION = TOKEN_TYPE_MINUS,
	OPERATOR_TYPE_MULTIPLICATION = TOKEN_TYPE_MULTIPLY,
	OPERATOR_TYPE_DIVISION = TOKEN_TYPE_DIVIDE
} OperatorType;


/*
	
	Bin Op Node

	- Represents a binary operation as a node
	- Contains a left node, right node, and the mathematical operation
	- Also contains a sign, example: -(10 + 10) would be a negative number

*/

typedef struct _BinOpNode {
	struct _AstNode* Left;
	struct _AstNode* Right;
	OperatorType Operator;
	UnaryType Unary;
} BinOpNode;

BinOpNode* BinOpNodeInit(struct _AstNode* left, struct _AstNode* right, OperatorType _operator, UnaryType unary);
void BinOpNodeSwitchUnary(BinOpNode* node);
extern inline void BinOpNodeDelete(BinOpNode* node);

// Ast Node

/*

	Ast Node Type

	- Represents the type of an AST node (number, binary operation)

*/

typedef enum _AstNodeType {
	AST_NODE_TYPE_NUMBER,
	AST_NODE_TYPE_BINOP
} AstNodeType;

/*
	
	Ast Node

	- Represents an abstract syntax tree as a node
	- Contains the type of the node as well as the internal node

*/

typedef struct _AstNode {
	AstNodeType Type;

	union {
		NumberNode* Number;
		BinOpNode* BinOp;
	} Option;
} AstNode;

AstNode* AstNodeNumberInit(char* value, NumberType type, UnaryType unary);
AstNode* AstNodeBinOpInit(struct _AstNode* left, struct _AstNode* right, OperatorType _operator, UnaryType unary);
extern inline void AstNodeDelete(AstNode* node);

// Serialisation

/*

	Serialisation Methods

	- Used for debugging to print out an abstract syntax tree

*/

char* OperatorToString(TokenType _operator);
char* NumberNodeToString(NumberNode* node);
char* BinOpNodeToString(BinOpNode* node);
char* AstNodeToString(AstNode* node);
