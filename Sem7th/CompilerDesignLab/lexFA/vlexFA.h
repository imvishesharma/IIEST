/**
 * TITILE : Lexical Analyzer
 * AUTHOR : Vishesh Sharma
 *
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "vUtil.h"

#define MAX_BUFFER_SIZE 10000
#define MAX_MSG_LENGTH 100

char _BUFFER[MAX_BUFFER_SIZE];
int POINTER_BUFF;

char _TOKEN[MAX_MSG_LENGTH];
char _ERROR[MAX_MSG_LENGTH];

int STATE, LINE, POS;

void INIT_P() {
    POINTER_BUFF = 0;
}
void INC_P() {
    if(CURR_CHAR() != '\0') {
        POINTER_BUFF++;
    }
}
void DEC_P() {
    if(POINTER_BUFF > 0) {
        POINTER_BUFF--;
    }
}
char CURR_CHAR() {
    return _BUFFER[POINTER_BUFF];
}

void lexIn(const char *input_file) {
    FILE *in = fopen(input_file, "r");
    char c;
    int i = 0;
    do {
        c = fgetc(in);
        if(feof(in)) {
            break;
        }
        CURR_CHAR() = c;
        i++;
    } while(true);
}

void vvlex() {
    INIT_P();
    LINE = 1;
    POS = 1;
    STATE = 0;

    bool RUNNING = true;

    while(RUNNING) {
        switch(STATE) {
            case 0:
                if(CURR_CHAR() == '\0') {
                    RUNNING = false;
                }
                else if(CURR_CHAR() == '\n') {
                    LINE++;
                    POS = 1;
                }
                else if(CURR_CHAR() == '/') {
                    STATE = 1;
                    commentsFA();
                }
                else if(CURR_CHAR() == 34 || CURR_CHAR() == 39) {
                    STATE = 105;
                    csLiteralFA();
                }
                else if(isAlphabet(CURR_CHAR())) {
                    STATE = 100;
                    keyvarFA();
                }
                else if(isBraces(CURR_CHAR())) {
                    _TOKEN[0] = CURR_CHAR();
                    _TOKEN[1] = '\0';
                    printf("%10d %10d %40s %10d\n", LINE, POS, _TOKEN, idBRACES(CURR_CHAR()));
                    INC_P();
                }
                else if(isDigit(CURR_CHAR())) {
                    STATE = 115;
                    rnLiteralFA();
                }
                else if(isOperator(CURR_CHAR())) {
                    STATE = 120;
                    operatorFA();
                }
                else {
                    POS++;
                    INC_P();
                }
                break;
        }
    }
}

void commentsFA() {
    bool RUNNING = true;
    int x = 0;
    int _pos = POS;
    int _l = lineNo;
    while(RUNNING) {
        switch (STATE) {
            case 1:
                if(CURR_CHAR == '/') {
                    STATE = 2;
                }
                break;
            case 2:
                if(CURR_CHAR() == '/') {
                    STATE = 3;
                } else if(CURR_CHAR() == '*') {
                    STATE = 5;
                } else if(CURR_CHAR() == '\0') {
                    STATE = -1;
                    RUNNING = false;
                } else {
                    STATE = -1;
                    run = false;
                }
                break;
            case 3:
                if(CURR_CHAR() == '\0' || CURR_CHAR() == '\n') {
                    printf("%10d %10d %40s %10d\n", _l, _pos, "Single line Comment", 1000);
                    if(CURR_CHAR() == '\n') {
                        lineNo++;
                        POS = 0;
                    }
                    STATE = 0;
                    run = false;
                }
                break;
            case 5:
                if(CURR_CHAR() == '*') {
                    STATE = 6;
                } else if(CURR_CHAR() == '\0') {
                    STATE = -1;
                    run = false;
                } else if(CURR_CHAR() == '\n') {
                    lineNo++;
                    POS = 0;
                }
                break;
            case 6:
                if(CURR_CHAR() == '/') {
                    STATE = 7;
                } else if(CURR_CHAR() == '\0') {
                    STATE = -1;
                    run = false;
                } else {
                    if(CURR_CHAR() == '\n') {
                        lineNo++;
                        POS = 0;
                    }
                    STATE = 5;
                }
                break;
            case 7:
                printf("%10d %10d %40s %10d\n", _l, _pos, "Multiline Comment", 1001);
                STATE = 0;
                run = false;
                break;
        }
        if(run) {
            _TEXT[x] = CURR_CHAR();
            i++;
            x++;
            POS++;
        } else {
            _TEXT[x] = '\0';
        }
    }
}
