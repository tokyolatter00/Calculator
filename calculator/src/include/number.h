
#pragma once

#include "ast.h"

/*

	Number

	- Represents a number
	- Contains the type and the int/float value of the number

*/

typedef struct _Number {
	NumberType Type;

	union {
		int64 Int;
		double Float;
	} Option;
} Number;

Number* NumberIntInit(uint64 integer);
Number* NumberFloatInit(double flt);
Number* NumberInit(char* value, NumberType type, UnaryType unary);
void NumberMakeNegative(Number* number);
extern inline void NumberDelete(Number* number);
