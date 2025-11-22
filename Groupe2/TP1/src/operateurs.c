#include <stdio.h>

int main(){
    int a = 16;
    int b = 3;
    printf("a+b : %u\n", a+b);
    printf("a-b : %u\n", a-b);
    printf("b-a : %d\n", b-a);
    printf("a*b : %u\n", a*b);
    printf("a/b : %.2f\n", (float) a/b);
    printf("a%%b : %u\n", a%b);
    printf("Comparaison : \n");
    if(a==b) printf("a=b\n");
    else printf("a différent de b\n");
    if(a>b) printf("a>b\n");
    else printf("b>a\n");

    return 0;
}