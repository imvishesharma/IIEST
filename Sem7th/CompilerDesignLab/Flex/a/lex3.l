%{
    #include <stdio.h>
    #include "tokendef.h"
%}

digit [0-9]
letter [a-zA-Z]

%%
char {return CHAR_TKN;}
bool {return BOOL_TKN;}
short {return SHORT_TKN;}
int {return INT_TKN;}
long {return LONG_TKN;}
float {return FLOAT_TKN;}
double {return DOUBLE_TKN;}
void {return VOID_TKN;}
auto {return AUTO_TKN;}

"signed" {return SIGNED_TKN;}
"unsigned" {return UNSIGNED_TKN;}
"const" {return CONST_TKN;}
"static" {return STATIC_TKN;}

"if" {return IF_TKN;}
"else" {return ELSE_TKN;}

#include {return INCLUDE_TKN;}
#define {return DEFINE_TKN;}
#ifndef {return IFNDEF_TKN;}
#endif {return ENDIF_TKN;}

"for" {return FOR_TKN;}
"while" {return WHILE_TKN;}
"break" {return BREAK_TKN;}
"continue" {return CONTINUE_TKN;}
"goto" {return GOTO_TKN;}
"do" {return DO_TKN;}

"switch" {return SWITCH_TKN;}
"case" {return CASE_TKN;}
"default" {return DEFAULT_TKN;}

"struct" {return STRUCT_TKN;}
"union" {return UNION_TKN;}
"typedef" {return TYPEDEF_TKN;}
"enum" {return ENUM_TKN;}
"register" {return REGISTER_TKN;}

"extern" {return EXTERN_TKN;}
"return" {return RETURN_TKN;}

"sizeof" {return SIZEOF_TKN;}
"volatile" {return VOLATILE_TKN;}

"[" {return LEFT_BRACES_TKN;}
"(" {return LEFT_BRACKETS_TKN;}
"{" {return LEFT_PARENTHESIS_TKN;}

"]" {return RIGHT_BRACES_TKN;}
")" {return RIGHT_BRACKETS_TKN;}
"}" {return RIGHT_PARENTHESIS_TKN;}

"+" {return OPERATOR_PLUS_TKN;}
"-" {return OPERATOR_MINUS_TKN;}
"*" {return OPERATOR_MULT_TKN;}
"\/" {return OPERATOR_DIV_TKN;}
"\%" {return OPERATOR_MOD_TKN;}

"++" {return OPERATOR_INC_TKN;}
"--" {return OPERATOR_DEC_TKN;}

"+=" {return OPERATOR_PLUS_EQUAL_TKN;}
"-=" {return OPERATOR_MINUS_EQUAL_TKN;}
"*=" {return OPERATOR_MULT_EQUAL_TKN;}
"/=" {return OPERATOR_DIV_EQUAL_TKN;}
"%=" {return OPERATOR_MOD_EQUAL_TKN;}

"|" {return OPERATOR_BITOR_TKN;}
"&" {return OPERATOR_BITAND_TKN;}
"^" {return OPERATOR_XOR_TKN;}
"!" {return OPERATOR_NOT_TKN;}

"|=" {return OPERATOR_BITOR_EQUAL_TKN;}
"&=" {return OPERATOR_BITAND_EQUAL_TKN;}
"^=" {return OPERATOR_XOR_EQUAL_TKN;}
"!=" {return OPERATOR_NOT_EQUAL_TKN;}

"||" {return OPERATOR_OR_TKN;}
"&&" {return OPERATOR_AND_TKN;}

"=" {return OPERATOR_ASSIGN_TKN;}
"==" {return OPERATOR_EQUAL_TKN;}

{digit}+([.]{digit}+)? {return REALNO_TKN;}

({letter})+({letter}|{digit})+ {return VARIABLE_TKN;}

[_]({letter}|{digit})+ {return VARIABLE_TKN;}

[\"]({letter})+[\"] {return STRINGLITERAL_TKN;}

[\'].[\'] {return CHARLITERAL_TKN;}
.
%%

int yywrap() {
    return 1;
}
int main() {
    int token;

    yyin = fopen("test3.c", "r");
    
    printf("%15s %30s\n", "TOKEN", "YYTEXT");
    while((token = yylex()) > 0) {
        printf("%15d %30s\n", token, yytext);
    }

    fclose(yyin);

    return 0;
}
