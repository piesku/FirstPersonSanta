#include <stdlib.h>
#include <stdio.h>

void* xmalloc(size_t size)
{
	void* ptr = malloc(size);
	if (ptr == NULL) {
		printf("Out of memory, malloc failed.");
		abort();
	}
	return ptr;
}
