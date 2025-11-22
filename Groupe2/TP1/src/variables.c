#include <stdio.h>

int main(){
    char c = 'A';
    unsigned char uc = 'B';
    signed char sc = 'C';

    short s = 32767;
    unsigned short us = 32767;
    signed short ss = -32767;

    int i = 32767;
    unsigned int ui = 65535;
    signed int si = -32767;

    long int li = 2147483647;
    unsigned long int uli = 4294967295;
    signed long int sli = -2147483647;
    
    long long int lli = 9223372036854775807;
    unsigned long long int ulli = 18446744073709551615;
    signed long long int slli = -9223372036854775807;
    
    float f = -3.981982819;
    // float IS signed : unsigned float uf = 1281982.382;
    // same here : signed float sf = 
    
    double d = 1390883193139381.1039103981038;
    long double ld = 2*d;

    printf("Char c : %c \n",c);
    printf("unsigned char : %c\n",uc);
    printf("signed char : %c\n",sc);

    printf("short : %hd\n",s);
    printf("unsigned short : %hd\n",us);
    printf("signed short  : %hd\n",ss);

    printf("int : %i\n",i);
    printf("unsigned int : %d\n",ui);
    printf("signed int : %d\n",si);

    printf("long int : %li\n",li);
    printf("unsigned long int : %lu\n",uli);
    printf("signed long int : %li\n",sli);
    
    printf("long long int : %lli\n",lli);
    printf("unsigned long long int : %llu\n",ulli);
    printf("signed long long int : %lld\n",slli);
    
    printf("float : %f\n",f);

    
    printf("double : %lf\n",d);
    printf("long double : %Lf\n",ld);

    return 0;
}