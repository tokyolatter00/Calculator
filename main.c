
#include <stdio.h>
#include <crtdbg.h>
#include "calculator/calculator.h"

int main(void) {
	const char* source = "(2) + (17*2-30) * (5)+2 - (8/2)*4";
	// Result of this source is 8

	Number* result = CalculateString(source);

	if (result->Type == NUMBER_TYPE_INT) {
		printf("Result: %d\n", result->Option.Int);
	}
	else if (result->Type == NUMBER_TYPE_FLOAT) {
		printf("Result: %f\n", result->Option.Float);
	}

	NumberDelete(result);
	_CrtDumpMemoryLeaks(); // Currently zero memory leaks detected
}
