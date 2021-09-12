/*
    AUTHOR : Vishesh Sharma
    /Users/inq/GitHub/IIEST/Sem7th/CompilerDesignLab
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define SIZE_BUFFER 1000

typedef int STATE;

char _BUFFER[SIZE_BUFFER];
int POINTER_BUFFER;
char _TEXT[100];

char nextChar();

void generateLex(char* buffer);
void lexFA();
void commentsFA();

char nextChar() {
    if(POINTER_BUFFER + 1 >= strlen(_BUFFER)) {
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
    char C = nextChar();
    STATE state = 0;
    bool f = true;
    while(f) {
        switch(state) {
            case 0:
                if(C == '\0') {
                    f = false;
                }
                else if(C == '/') {
                    state = 1;
                }
                break;
            case 1:
                commentsFA();
                printf("%s\n", _TEXT);
                state = 0;
                break;
        }
        C = nextChar();
    }
}

void commentsFA() {
    int i = 0;
    STATE state = 2;
    _TEXT[i] = '/';
    i++;
    char c = nextChar();

    bool f = true;
    while(f) {
        _TEXT[i] = c;
        switch(state) {
            case 2:
                if(c == '/') {
                    state = 3;
                } else if(c == '*') {
                    state = 4;
                }
                break;
            case 3:
                if(c == '\0' || c == '\n') {
                    f = false;
                }
                break;
            case 4:
                if(c == '*') {
                    state = 5;
                }
                break;
            case 5:
                if(c == '/') {
                    _TEXT[i] = c;
                    f = false;
                }
                break;
        }
        c = nextChar();
        i++;
    }
}
