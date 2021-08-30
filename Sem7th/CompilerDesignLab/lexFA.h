/*
    AUTHOR : Vishesh Sharma
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define SIZE_BUFFER 10e5

char _BUFFER[SIZE_BUFFER];
int POINTER_BUFFER;

void nextChar();

void generateLex(char* buffer);
void lexFA();
void single_line_commentsFA();

char nextChar() {
    if(POINTER_BUFFER + 1 == strlen(_BUFFER)) {
        return '\0';
    }
    POINTER_BUFFER++;
    return _BUFFER[POINTER_BUFFER];
}

void generateLex(char* buffer) {
    strcpy(buffer, _BUFFER);

    _BUFFER[strlen(buffer)] = '\0';
    POINTER_BUFFER = -1;

    lexFA();
}

void lexFA() {
    while(true) {
        if(CURR == '\0') {
            break;
        }
    }
}
