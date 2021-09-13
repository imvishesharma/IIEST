/*
    AUTHOR : Vishesh Sharma
    /Users/inq/GitHub/IIEST/Sem7th/CompilerDesignLab
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define SIZE_BUFFER 1000

char _BUFFER[SIZE_BUFFER];
char _TEXT[SIZE_BUFFER];
char token[100];
int STATE = 0;
int lineNo = 1;
int POS = 0;

void generateLex(char* buffer);
void lexFA();

int commentsFA(int i);

bool isAlphabet(int i);
bool isDigit(int i);
int isKeyword(char *str);

int keyvarFA(int i);

int csLiteralFA(int i);
int rnLiteralFA(int i);

bool isBraces(char c);
int idBRACES(char bracket);

bool isOperator(int i);
int operatorFA(int i);

void generateLex(char* buffer) {
    strcpy(_BUFFER, buffer);

    _BUFFER[strlen(buffer)] = '\0';

    lexFA();
}

void lexFA() {
    bool run = true;
    int i = 0;
    printf("%10s %10s %40s %10s\n", "LINE", "POS", "TOKEN", "ID");

    while(run) {
        switch (STATE) {
            case -1:
                printf("%10d %10d %40s %10d\n", lineNo, POS, "Syntax Error", -1);
                STATE = 0;
                break;
            case 0:
                if(_BUFFER[i] == '\0') {
                    run = false;
                }
                else if(_BUFFER[i] == '/') {
                    STATE = 1;
                    i = commentsFA(i);
                }
                else if(isAlphabet(i)) {
                    STATE = 100;
                    i = keyvarFA(i);
                }
                else if(_BUFFER[i] == 34 || _BUFFER[i] == 39) {
                    STATE = 105;
                    i = csLiteralFA(i);
                }
                else if(isBraces(_BUFFER[i])) {
                    printf("%10d %10d %40s %10d\n", lineNo, POS, token, idBRACES(_BUFFER[i]));
                }
                else if(_BUFFER[i] == '\n') {
                    lineNo++;
                    POS = 0;
                }
                else if(isDigit(i)) {
                    STATE = 115;
                    i = rnLiteralFA(i);
                }
                else if(isOperator(i)) {
                    STATE = 120;
                    i = operatorFA(i);
                }
                else {
                    POS++;
                }
                break;
        }
        i++;
    }
}
// STATE 1-7
int commentsFA(int i) {
    bool run = true;
    int x = 0;
    int _pos = POS;
    int _l = lineNo;
    while(run) {
        switch (STATE) {
            case 1:
                if(_BUFFER[i] == '/') {
                    STATE = 2;
                }
                break;
            case 2:
                if(_BUFFER[i] == '/') {
                    STATE = 3;
                } else if(_BUFFER[i] == '*') {
                    STATE = 5;
                } else if(_BUFFER[i] == '\0') {
                    STATE = -1;
                    run = false;
                } else {
                    STATE = -1;
                    run = false;
                }
                break;
            case 3:
                if(_BUFFER[i] == '\0' || _BUFFER[i] == '\n') {
                    printf("%10d %10d %40s %10d\n", _l, _pos, "Single line Comment", 1000);
                    if(_BUFFER[i] == '\n') {
                        lineNo++;
                        POS = 0;
                    }
                    STATE = 0;
                    run = false;
                }
                break;
            case 5:
                if(_BUFFER[i] == '*') {
                    STATE = 6;
                } else if(_BUFFER[i] == '\0') {
                    STATE = -1;
                    run = false;
                } else if(_BUFFER[i] == '\n') {
                    lineNo++;
                    POS = 0;
                }
                break;
            case 6:
                if(_BUFFER[i] == '/') {
                    STATE = 7;
                } else if(_BUFFER[i] == '\0') {
                    STATE = -1;
                    run = false;
                } else {
                    if(_BUFFER[i] == '\n') {
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
            _TEXT[x] = _BUFFER[i];
            i++;
            x++;
            POS++;
        } else {
            _TEXT[x] = '\0';
        }
    }
    return i;
}

bool isAlphabet(int i) {
    char c = _BUFFER[i];

    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
bool isDigit(int i) {
    char c = _BUFFER[i];

    return (c >= '0' && c <= '9');
}
int isKeyword(char *str)
{
    const int _id = 200;
    char keywords[][10] = {"auto", "double", "int", "struct",
                        "break", "else", "long", "switch",
                        "case", "enum", "register", "typedef",
                        "char", "extern", "return", "union",
                        "const", "float", "short", "unsigned",
                        "continue", "for", "signed", "void",
                        "default", "goto", "sizeof", "volatile",
                        "do", "if", "static", "while", "bool"};

    for(int i = 0; i < 32; ++i) {
        if(strcmp(str, keywords[i]) == 0) {
            return _id + i;
        }
    }

    return 0;
}

// STATE 100
int keyvarFA(int i) {
    bool run = true;
    int x = 0;
    int _pos = POS;
    while (run) {
        switch (STATE) {
            case 100:
                if(isAlphabet(i) || isDigit(i)) {
                    STATE = 100;
                } else {
                    STATE = 0;
                    run = false;
                }
                break;
        }
        if(run) {
            _TEXT[x] = _BUFFER[i];
            i++;
            x++;
            POS++;
        } else {
            _TEXT[x] = '\0';
            i--;
        }
    }
    int keyid = isKeyword(_TEXT);
    if(keyid) {
        printf("%10d %10d %40s %10d\n", lineNo, _pos, _TEXT, keyid);
    } else {
        printf("%10d %10d %40s %10d\n", lineNo, _pos, _TEXT, keyid);
    }

    return i;
}
// STATES 105-109
int csLiteralFA(int i) {
    bool run = true;
    int x = 0;
    int _pos = POS;
    while (run) {
        switch (STATE) {
            case 105:
                if(_BUFFER[i] == 34) {
                    STATE = 106;
                } else if(_BUFFER[i] == 39) {
                    STATE = 107;
                }
                break;
            case 106:
                if(_BUFFER[i] == 34) {
                    STATE = 108;
                } else if(_BUFFER[i] == '\0') {
                    run  = false;
                    STATE = -1;
                }
                break;
            case 107:
                if(_BUFFER[i] == 39) {
                    STATE = 109;
                } else if(_BUFFER[i] == '\0') {
                    run  = false;
                    STATE = -1;
                }
                break;
            case 108:
                run = false;
                STATE = 0;
                _TEXT[x] = '\0';
                printf("%10d %10d %40s %10d\n", lineNo, _pos, _TEXT, 34);
                break;
            case 109:
                run = false;
                STATE = 0;
                _TEXT[x] = '\0';
                printf("%10d %10d %40s %10d\n", lineNo, _pos, _TEXT, 39);
                break;
        }
        if(run) {
            _TEXT[x] = _BUFFER[i];
            i++;
            x++;
            POS++;
        } else {
            _TEXT[x] = '\0';
        }
    }

    return i;
}

bool isBraces(char c) {
    if(c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']') {
        return true;
    }
    return false;
}

int idBRACES(char bracket) {
    switch (bracket) {
        case '(':
            strcpy(token, "LEFT_PARENTHESIS_TKN");
            return 91;
        case ')':
            strcpy(token, "RIGHT_PARENTHESIS_TKN");
            return 92;
        case '{':
            strcpy(token, "LEFT_BRACES_TKN");
            return 93;
        case '}':
            strcpy(token, "RIGHT_BRACES_TKN");
            return 94;
        case '[':
            strcpy(token, "LEFT_BRACKETS_TKN");
            return 95;
        case ']':
            strcpy(token, "RIGHT_BRACKETS_TKN");
            return 96;
        break;
    }

    return -1;
}
// STATES 115-116
int rnLiteralFA(int i) {
    bool run = true;
    int x = 0;
    int _pos = POS;
    while (run) {
        switch (STATE) {
            case 115:
                if(_BUFFER[i] == '.') {
                    STATE = 116;
                } else if(!isDigit(i)) {
                    i--;
                    run = false;
                    STATE = 0;
                }
                break;
            case 116:
                if(_BUFFER[i] == '.') {
                    STATE = -1;
                    run = false;
                } else if(!isDigit(i)) {
                    i--;
                    run = false;
                    STATE = 0;
                }
                break;
        }
        if(run) {
            _TEXT[x] = _BUFFER[i];
            i++;
            x++;
            POS++;
        } else {
            _TEXT[x] = '\0';
        }
    }
    printf("%10d %10d %40s %10d\n", lineNo, _pos, _TEXT, 50);
    return i;
}

bool isOperator(int i) {
    char c = _BUFFER[i];
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '>' || c == '<' || c == '=' || c == '%' || c == '&' || c == '|') {
        return true;
    }
    return false;
}

int operatorFA(int i) {
    bool run = true;
    int _l = lineNo, _pos = POS;
    while (run) {
        switch (STATE) {
            case 120:
                if(_BUFFER[i] == '+') {
                    STATE = 121;
                } else if(_BUFFER[i] == '-') {
                    STATE = 122;
                } else if(_BUFFER[i] == '*') {
                    STATE = 123;
                } else if(_BUFFER[i] == '/') {
                    STATE = 124;
                } else if(_BUFFER[i] == '^') {
                    STATE = 125;
                } else if(_BUFFER[i] == '%') {
                    STATE = 126;
                } else if(_BUFFER[i] == '&') {
                    STATE = 127;
                } else if(_BUFFER[i] == '|') {
                    STATE = 128;
                } else if(_BUFFER[i] == '=') {
                    STATE = 129;
                }
                break;
            case 121:
                run = false;
                STATE = 0;
                if(!isOperator(i)) {
                    i--;
                    strcpy(_TEXT, "OPERATOR_PLUS");
                } else if(_BUFFER[i] == '+') {
                    strcpy(_TEXT, "OPERATOR_INCREMENT");
                } else if(_BUFFER[i] == '=') {
                    strcpy(_TEXT, "OPERATOR_PLUS_EQUAL");
                } else {
                    STATE = -1;
                }
                break;
            case 122:
                run = false;
                STATE = 0;
                if(!isOperator(i)) {
                    i--;
                    strcpy(_TEXT, "OPERATOR_MINUS");
                } else if(_BUFFER[i] == '-') {
                    strcpy(_TEXT, "OPERATOR_DECREMENT");
                } else if(_BUFFER[i] == '=') {
                    strcpy(_TEXT, "OPERATOR_MINUS_EQUAL");
                } else {
                    STATE = -1;
                }
                break;
            case 123:
                run = false;
                STATE = 0;
                if(!isOperator(i)) {
                    i--;
                    strcpy(_TEXT, "OPERATOR_MULT");
                } else if(_BUFFER[i] == '=') {
                    strcpy(_TEXT, "OPERATOR_MULT_EQUAL");
                } else {
                    STATE = -1;
                }
                break;
            case 124:
                run = false;
                STATE = 0;
                if(!isOperator(i)) {
                    i--;
                    strcpy(_TEXT, "OPERATOR_DIV");
                } else if(_BUFFER[i] == '=') {
                    strcpy(_TEXT, "OPERATOR_DIV_EQUAL");
                } else {
                    STATE = -1;
                }
                break;
            case 125:
                run = false;
                STATE = 0;
                if(!isOperator(i)) {
                    i--;
                    strcpy(_TEXT, "OPERATOR_XOR");
                } else if (_BUFFER[i] == '=') {
                    strcmp(_TEXT, "OPERATOR_XOR_EQUAL");
                } else {
                    STATE = -1;
                }
            case 126:
                run = false;
                STATE = 0;
                if(!isOperator(i)) {
                    i--;
                    strcpy(_TEXT, "OPERATOR_MOD");
                } else if (_BUFFER[i] == '=') {
                    strcmp(_TEXT, "OPERATOR_MOD_EQUAL");
                } else {
                    STATE = -1;
                }
                break;
            case 127:
                run = false;
                STATE = 0;
                if(!isOperator(i)) {
                    i--;
                    strcpy(_TEXT, "OPERATOR_AND");
                } else if(_BUFFER[i] == '&') {
                    strcpy(_TEXT, "OPERATOR_AND_AND");
                } else if (_BUFFER[i] == '=') {
                    strcmp(_TEXT, "OPERATOR_AND_EQUAL");
                } else {
                    STATE = -1;
                }
                break;
            case 128:
                run = false;
                STATE = 0;
                if(!isOperator(i)) {
                    i--;
                    strcpy(_TEXT, "OPERATOR_OR");
                } else if (_BUFFER[i] == '|') {
                    strcmp(_TEXT, "OPERATOR_OR_OR");
                } else if (_BUFFER[i] == '=') {
                    strcmp(_TEXT, "OPERATOR_OR_EQUAL");
                } else {
                    STATE = -1;
                }
                break;
            case 129:
                run = false;
                STATE = 0;
                if(!isOperator(i)) {
                    i--;
                    strcpy(_TEXT, "OPERATOR_ASSIGNEMT");
                } else if (_BUFFER[i] == '=') {
                    strcmp(_TEXT, "OPERATOR_EQUAL_EQUAL");
                } else {
                    STATE = -1;
                }
                break;
            }
        if(run) {
            i++;
            POS++;
        }
    }
    if(STATE == 0) {
        printf("%10d %10d %40s %10d\n", _l, _pos, _TEXT, 256);
    }
    return i;
}


/*
printf("%10d %10d %40s %10d\n", lineNo, _pos, _TEXT, 39);
*/
