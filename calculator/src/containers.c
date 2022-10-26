
#include <stdlib.h>
#include "include/containers.h"

/*
	Allocate more memory for the token array

	- Create a new buffer double the size
	- Copy existing data into the new buffer
	- Doubles each time except at 0 (0 --> 2 --> 4 --> 8 --> 16, etc.)
*/

static void TokenArrAlloc(TokenArray* arr) {
	uint64 capacity = arr->Capacity > 0
		? arr->Capacity * 2
		: 2;
	Token* buffer = malloc(capacity * sizeof(Token));

	for (uint64 i = 0; i < arr->Capacity; i++) {
		buffer[i] = arr->Buffer[i];
	}

	free(arr->Buffer);
	arr->Buffer = buffer;
	arr->Capacity = capacity;
}

/*
	Create a TokenArray struct
*/

TokenArray* TokenArrayInit() {
	TokenArray* arr = calloc(1, sizeof(TokenArray));
	arr->Buffer = NULL;
	arr->Length = 0;
	arr->Capacity = 0;

	return arr;
}

/*
	Append a token to a token array
*/

void TokenArrayAppend(TokenArray* arr, Token token) {
	if (arr->Length >= arr->Capacity) {
		TokenArrAlloc(arr);
	}

	arr->Buffer[arr->Length] = token;
	arr->Length++;
}

/*
	Delete a TokenArray struct
*/

inline void TokenArrayDelete(TokenArray* arr) {
	free(arr->Buffer);
	free(arr);
}
