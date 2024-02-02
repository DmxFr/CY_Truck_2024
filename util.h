#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <stdbool.h>
#include <string.h>

#ifndef util
#define util


void* safeMalloc(size_t size);


void safeFree(void* ptr);


void error(char* message);


int lengthOfInt(int n);


void clear(FILE* stream);

`
bool strContains(char* str, char* part);


bool strContainsAtLeast(char* str, char* chars);


#endif
