#include <stdio.h>
#include <limits.h>  
#include <float.h>    

int main(void) {
    signed char sc = -100;
    unsigned char uc = UCHAR_MAX;
    short s = -30000;
    unsigned short us = USHRT_MAX;
    int i = -2000000000;
    unsigned int ui = UINT_MAX;
    long int li = -9000000000L;
    unsigned long int uli = ULONG_MAX;
    long long int lli = -9000000000000000000LL;
    unsigned long long int ulli = ULLONG_MAX;
    float f = 3.14f;
    double d = 2.718281828;
    long double ld = 1.6180339887L;

    printf("signed char : %d\n", sc);
    printf("unsigned char : %u\n", uc);

    printf("short : %d\n", s);
    printf("unsigned short : %u\n", us);

    printf("int : %d\n", i);
    printf("unsigned int : %u\n", ui);

    printf("long int : %ld\n", li);
    printf("unsigned long int : %lu\n", uli);

    printf("long long int : %lld\n", lli);
    printf("unsigned long long int : %llu\n", ulli);

    printf("float : %f\n", f);
    printf("double : %lf\n", d);
    printf("long double : %Lf\n", ld);

    return 0;
}
