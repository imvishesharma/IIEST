#include <stdio.h>

int globalVar = 1;

int main() {
    char option = 'A';
    char x[7] = "Vishesh";
    int x = 123;
    float y = 12.07;
    int z = 12;
    int a = z++;
    int _12 = x;
    if(option == 'A') {
        printf("%s\n", "Option A");
    } else {
        printf("%s\n", "Invalid Option");
    }

    return 0;
}
