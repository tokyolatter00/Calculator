
#include <stdio.h>//
#include <stdlib.h>
#include "include/interpreter.h"

Number* VisitAstNode(AstNode* node);

// Mathematics

#define MATH_INT_INT(left, _operator, right)			NumberIntInit(left->Option.Int _operator right->Option.Int)
#define MATH_INT_FLOAT(left, _operator, right)			NumberFloatInit(left->Option.Int _operator right->Option.Float)
#define MATH_FLOAT_INT(left, _operator, right)			NumberFloatInit(left->Option.Float _operator right->Option.Int)
#define MATH_FLOAT_FLOAT(left, _operator, right)		NumberFloatInit(left->Option.Float _operator right->Option.Float)

static Number* PerformAddition(Number* left, Number* right) {
	switch (left->Type) {
		case NUMBER_TYPE_INT:
			switch (right->Type) {
				case NUMBER_TYPE_INT:
					return MATH_INT_INT(left, +, right);
				case NUMBER_TYPE_FLOAT:
					return MATH_INT_FLOAT(left, +, right);
			}
		case NUMBER_TYPE_FLOAT:
			switch (right->Type) {
				case NUMBER_TYPE_INT:
					return MATH_FLOAT_INT(left, +, right);
				case NUMBER_TYPE_FLOAT:
					return MATH_FLOAT_FLOAT(left, +, right);
			}
	}
}

static Number* PerformSubtraction(Number* left, Number* right) {
	switch (left->Type) {
		case NUMBER_TYPE_INT:
			switch (right->Type) {
				case NUMBER_TYPE_INT:
					return MATH_INT_INT(left, -, right);
				case NUMBER_TYPE_FLOAT:
					printf("Subtracting int and float\n");
					MATH_INT_FLOAT(left, -, right);
					printf("Subtracted int and float\n");
					return MATH_INT_FLOAT(left, -, right);
			}
		case NUMBER_TYPE_FLOAT:
			switch (right->Type) {
				case NUMBER_TYPE_INT:
					return MATH_FLOAT_INT(left, -, right);
				case NUMBER_TYPE_FLOAT:
					return MATH_FLOAT_FLOAT(left, -, right);
			}
	}
}

static Number* PerformMultiplication(Number* left, Number* right) {
	switch (left->Type) {
		case NUMBER_TYPE_INT:
			switch (right->Type) {
				case NUMBER_TYPE_INT:
					return MATH_INT_INT(left, *, right);
				case NUMBER_TYPE_FLOAT:
					return MATH_INT_FLOAT(left, *, right);
			}
		case NUMBER_TYPE_FLOAT:
			switch (right->Type) {
				case NUMBER_TYPE_INT:
					return MATH_FLOAT_INT(left, *, right);
				case NUMBER_TYPE_FLOAT:
					return MATH_FLOAT_FLOAT(left, *, right);
			}
	}
}

static Number* PerformDivision(Number* left, Number* right) {
	switch (left->Type) {
		case NUMBER_TYPE_INT:
			switch (right->Type) {
				case NUMBER_TYPE_INT:
					return MATH_INT_INT(left, /, right);
				case NUMBER_TYPE_FLOAT:
					return MATH_INT_FLOAT(left, /, right);
			}
		case NUMBER_TYPE_FLOAT:
			switch (right->Type) {
				case NUMBER_TYPE_INT:
					return MATH_FLOAT_INT(left, /, right);
				case NUMBER_TYPE_FLOAT:
					return MATH_FLOAT_FLOAT(left, /, right);
			}
	}
}

// Visit Node

static Number* VisitNumberNode(NumberNode* node) {
	return NumberInit(node->Value, node->Type, node->Unary);
}

static Number* VisitBinOpNode(BinOpNode* node) {
	Number* left = VisitAstNode(node->Left);
	Number* right = VisitAstNode(node->Right);
	Number* result = NULL;

	switch (node->Operator) {
		case OPERATOR_TYPE_ADDITION:
			result = PerformAddition(left, right);
			break;
		case OPERATOR_TYPE_SUBTRACTION:
			result = PerformSubtraction(left, right);
			break;
		case OPERATOR_TYPE_MULTIPLICATION:
			result = PerformMultiplication(left, right);
			break;
		case OPERATOR_TYPE_DIVISION:
			result = PerformDivision(left, right);
			break;
	}

	NumberDelete(left);
	NumberDelete(right);

	if (node->Unary == UNARY_TYPE_NEGATIVE) {
		NumberMakeNegative(result);
	}

	return result;
}

static Number* VisitAstNode(AstNode* node) {
	switch (node->Type) {
		case AST_NODE_TYPE_NUMBER:
			return VisitNumberNode(node->Option.Number);
		case AST_NODE_TYPE_BINOP:
			return VisitBinOpNode(node->Option.BinOp);
	}
}

// Header Implementation

Interpreter* InterpreterInit(AstNode* node) {
	Interpreter* interpreter = calloc(1, sizeof(Interpreter));
	interpreter->Node = node;

	return interpreter;
}

Number* InterpreterGetResult(Interpreter* interpreter) {
	return VisitAstNode(interpreter->Node);
}

inline void InterpreterDelete(Interpreter* interpreter) {
	free(interpreter);
}
