#include <stdio.h>

int main()
{
    int val;
    while((12 = yylex()) > 0)
    {
        printf("Token ===%s; Token ID ====%d\n", yytext, val);

    }

    return(0);
}
