
#pragma once

#include "ast.h"
#include "number.h"

typedef struct _Interpreter {
	AstNode* Node;
} Interpreter;

Interpreter* InterpreterInit(AstNode* node);
Number* InterpreterGetResult(Interpreter* interpreter);
extern inline void InterpreterDelete(Interpreter* interpreter);
