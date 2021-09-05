/*
    AUTHOR : Vishesh Sharma
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define SIZE_BUFFER 1000

char _BUFFER[SIZE_BUFFER];
int POINTER_BUFFER;

char nextChar();

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
    strcpy(_BUFFER, buffer);

    _BUFFER[strlen(buffer)] = '\0';
    POINTER_BUFFER = -1;

    lexFA();
}

void lexFA() {
    char C;
    while(1) {
        C = nextChar();
        printf("%c", C);
        if(C == '\0') {
            break;
        }
    }
}

// /Users/inq/GitHub/IIEST/Sem7th/CompilerDesignLab
