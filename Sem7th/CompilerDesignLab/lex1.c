/*
    AUTHOR : Vishesh Sharma
*/

#include "lexFA.h"

#define BUFFER_SIZE 1000

int main(const int argc, const char *argv[])
{
    if(argc != 2)
    {
        printf("%s\n", "Usage ./lex <source_file>");
        exit(0);
    }

    FILE *src;
    src = fopen(argv[1], "r");

    if(src == NULL) {
        printf("%s\n", "Error Opening File");
        exit(0);
    }

    char buffer[BUFFER_SIZE], c;
    int i = 0;
    do {
        c = fgetc(src);
        if(feof(src)) {
            buffer[i] = '\0';
            break;
        }
        buffer[i] = c;
        i++;
    } while(true);

    generateLex(buffer);

    return 0;
}
