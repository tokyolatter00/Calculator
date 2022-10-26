
# Calculator

## About
This is a parser written in C for parsing mathematical expressions. It does not include error handling and error checking, and is not fit to be used in production. This is mostly a side project for fun so I could learn more about how these parsers work.

```c
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
```
