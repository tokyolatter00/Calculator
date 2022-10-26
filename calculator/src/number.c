
#include <stdlib.h>
#include "include/number.h"

/*
	Create a Number struct wrapped around an integer
*/

Number* NumberIntInit(uint64 integer) {
	Number* number = calloc(1, sizeof(Number));
	number->Option.Int = integer;
	number->Type = NUMBER_TYPE_INT;

	return number;
}

/*
	Create a Number struct wrapped around a float
*/

Number* NumberFloatInit(double flt) {
	Number* number = calloc(1, sizeof(Number));
	number->Option.Float = flt;
	number->Type = NUMBER_TYPE_FLOAT;

	return number;
}

/*
	Create a Number struct, with a number type and sign
	- Converts a string value to a number
	- Assumes inputted string is a valid number, this application does not support error checking
*/

Number* NumberInit(char* value, NumberType type, UnaryType unary) {
	Number* number = NULL;

	switch (type) {
		case NUMBER_TYPE_INT: {
			uint64 integer = strtoll(value, NULL, 10);

			if (unary == UNARY_TYPE_NEGATIVE) {
				integer *= -1;
			}

			number = NumberIntInit(integer, unary);
			break;
		}
		case NUMBER_TYPE_FLOAT: {
			double flt = strtold(value, NULL);

			if (unary == UNARY_TYPE_NEGATIVE) {
				flt *= -1;
			}

			number = NumberFloatInit(flt, unary);
			break;
		}
	}

	return number;
}

/*
	Make the number value of a Number struct negative
	e.g. 10 --> -10, 3.04 --> -3.04
*/

void NumberMakeNegative(Number* number) {
	switch (number->Type) {
		case NUMBER_TYPE_INT:
			number->Option.Int *= -1;
			break;
		case NUMBER_TYPE_FLOAT:
			number->Option.Float *= -1;
			break;
	}
}

/*
	Delete a Number struct
*/

inline void NumberDelete(Number* number) {
	free(number);
}
