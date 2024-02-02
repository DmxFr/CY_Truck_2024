#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <stdbool.h>
#include <string.h>

#ifndef util
#define util


//Safely allocate the given size. The program exits on failure.
void* safeMalloc(size_t size);

//Safely free the given pointer. The program exists on failure.
void safeFree(void* ptr);

//Print the given error message then exit with 1
void error(char* message);

//Return the textual length of the given integer.
int lengthOfInt(int n);

//Clear/Flush the given stream.
void clear(FILE* stream);

//Renvoie true si la chaine de caractère `str` contient la chaine `part`
bool strContains(char* str, char* part);

//Renvoie true si la chaine de caractère `str` contient au moins un élément de la chaine `chars`
bool strContainsAtLeast(char* str, char* chars);


#endif
