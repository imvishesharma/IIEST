/*
    AUTHOR : Vishesh Sharma
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

char token[50];

void toUpper(char *str)
{
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] -= 32;
        }
    }
}

bool isAlphabet(char c) {
    if(c >= 'a' && c <= 'z') {
        return true;
    } else if(c >= 'A' && c <= 'Z') {
        return true;
    }
    return false;
}
bool isDigit(char c) {
    if(c >= '0' && c <= '9') {
        return true;
    }
    return false;
}
bool isBreakchar(char c)
{
    if(c == ' ' || c == '\t' || c == '\n' || c == ';') {
        return true;
    }
    return false;
}
bool isBraces(char c) {
    if(c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']') {
        return true;
    }
    return false;
}
bool isOperator(char c) {
    if(c == '+' || c == '-' || c == '%' || c == '/' || c == '*' || c == '^' || c == '=') {
        return true;
    }
    return false;
}
int idPREPROCESSOR(char *str)
{
    if(strcmp(str, "include") == 0) {
        strcpy(token, "PREPCSR_INCLUDE_TKN");
        return 701;
    }
    else if (strcmp(str, "define") == 0) {
        strcpy(token, "PREPCSR_DEFINE_TKN");
        return 702;
    }
    else if (strcmp(str, "ifndef") == 0) {
        strcpy(token, "PREPCSR_IFNDEF_TKN");
        return 703;
    }
    else if (strcmp(str, "undef") == 0) {
        strcpy(token, "PREPCSR_UNDEF_TKN");
        return 704;
    }

    return -1;
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

int idOPERATOR(char operator) {
    switch (operator) {
        case '+':
            strcpy(token, "OPERATOR_PLUS_TKN");
            return 71;
        case '-':
            strcpy(token, "OPERATOR_SUBT_TKN");
            return 72;
        case '/':
            strcpy(token, "OPERATOR_DIV_TKN");
            return 73;
        case '*':
            strcpy(token, "OPERATOR_MUL_TKN");
            return 74;
        case '%':
            strcpy(token, "OPERATOR_MOD_TKN");
            return 75;
        case '^':
            strcpy(token, "OPERATOR_XOR_TKN");
            return 76;
        case '=':
            strcpy(token, "OPERATOR_EQL_TKN");
            return 77;
        break;
    }

    return -1;
}

int isKeyword(char *str)
{
    const int val_keyword = 100;
    char keywords[][10] = {"auto", "double", "int", "struct",
                        "break", "else", "long", "switch",
                        "case", "enum", "register", "typedef",
                        "char", "extern", "return", "union",
                        "const", "float", "short", "unsigned",
                        "continue", "for", "signed", "void",
                        "default", "goto", "sizeof", "volatile",
                        "do", "if", "static", "while", "bool"};

    for(int i = 0; i < 32; ++i)
    {
        if(strcmp(str, keywords[i]) == 0)
        {
            strcpy(token, keywords[i]);
            toUpper(token);
            strcat(token, "_TKN");

            return val_keyword + i;
        }
    }

    return 0;
}

void _print(char *str, int id) {
    char gap[30];
    int i = 0;
    while(i < 30 - strlen(str)) {
        gap[i] = ' ';
        i++;
    }
    gap[i] = '\0';
    printf("%s %s %d\n", str, gap, id);
}

void _print1(char *str1, char *str2) {
    char gap[30];
    int i = 0;
    while(i < 30 - strlen(str1)) {
        gap[i] = ' ';
        i++;
    }
    gap[i] = '\0';
    printf("%s %s %s\n", str1, gap, str2);
}

void generateLex(char *str)
{
    char buffer[100], val;
    int key;

    int CURR_INDEX = 0;
    while(CURR_INDEX < strlen(str))
    {
        val = str[CURR_INDEX];
        if (val == '#') {
            // PRE-PROCESSORS;
            CURR_INDEX++;
            int i = 0;
            while(!isBreakchar(str[CURR_INDEX + i]))
            {
                buffer[i] = str[CURR_INDEX + i];
                i++;
            }
            buffer[i] = '\0';

            key  = idPREPROCESSOR(buffer);
            _print(token, key);

            CURR_INDEX += i;
        }
        else if (val == '<') {
            CURR_INDEX++;

            int i = 0;
            while(str[CURR_INDEX] != '>') {
                buffer[i] = str[CURR_INDEX];
                i++;
                CURR_INDEX++;
            }
            buffer[i] = '\0';
            _print1("HEADER_FILE", buffer);

            CURR_INDEX++;
        }
        else if (isBreakchar(val)) {
            CURR_INDEX++;
        }
        else if (isBraces(val)) {
            key = idBRACES(val);
            _print(token, key);

            CURR_INDEX++;
        }
        else if(isOperator(val)) {
            key = idOPERATOR(val);
            _print(token, key);

            CURR_INDEX++;
        }
        else if (val == 34 || val == 39) {
            CURR_INDEX++;
            int i = 0;
            buffer[i] = val;
            i++;
            while(str[CURR_INDEX] != 34) {
                buffer[i] = str[CURR_INDEX];
                CURR_INDEX++;
                i++;
            }
            buffer[i] = 34;
            buffer[i+1] = '\0';
            CURR_INDEX++;

            _print1("STRING_LITERAL" , buffer);
        }
        else if (isDigit(val)) {
            int i = 0;
            buffer[i] = val;
            i++;
            CURR_INDEX++;
            while(isDigit(str[CURR_INDEX])) {
                buffer[i] = str[CURR_INDEX];
                i++;
                CURR_INDEX++;
            }
            buffer[i] = '\0';

            _print1("INTEGER_CONSTANT", buffer);
        }
        else {
            int i = 0;
            while(!isBreakchar(str[CURR_INDEX]) && !isBraces(str[CURR_INDEX])) {
                buffer[i] = str[CURR_INDEX];
                i++;
                CURR_INDEX++;
            }
            buffer[i] = '\0';

            key = isKeyword(buffer);

            if(key) {
                _print(token, key);
            }
            else {
                _print1("VARIABLE_TKN", buffer);
            }
        }
    }
}
