
#pragma once

#include "token.h"
#include "types.h"

/*

	Token Array

	- Array of tokens which dynamically grows in size

*/

typedef struct _TokenArray {
	Token* Buffer;
	uint64 Length;
	uint64 Capacity;
} TokenArray;

TokenArray* TokenArrayInit();
void TokenArrayAppend(TokenArray* arr, Token token);
extern inline void TokenArrayDelete(TokenArray* arr);
