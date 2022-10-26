
#include <stdlib.h>
#include "src/include/lexer.h"
#include "src/include/parser.h"
#include "src/include/interpreter.h"

Number* CalculateString(const char* source) {
	// Lexer

	Lexer* lexer = LexerInit(source);
	TokenArray* arr = LexerGetResult(lexer);
	LexerDelete(lexer);

	// Parser

	Parser* parser = ParserInit(arr);
	AstNode* node = ParserGetResult(parser);
	ParserDelete(parser);

	// Interpreter

	Interpreter* interpreter = InterpreterInit(node);
	Number* number = InterpreterGetResult(interpreter);
	InterpreterDelete(interpreter);

	// Memory Cleanup

	TokenArrayDelete(arr);
	AstNodeDelete(node);

	return number;
}
