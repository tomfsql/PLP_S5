#include <stdio.h>
#include <limits.h>  
#include <float.h>    

int main(void) {
    int a = 16;
    int b = 3;
    printf("ADD : %d\n", a+b);
    printf("SUB : %d\n", a-b);
    printf("MUL : %d\n", a*b);
    printf("DIV : %d\n", a/b);
    printf("MOD : %d\n", a%b);
    printf("A EQU B : %b\n", a ==b );
    printf("A SUP B : %b\n", a > b );
    return 0;
}
