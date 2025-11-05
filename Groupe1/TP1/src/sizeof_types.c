#include <stdio.h> 
int main() {  
    printf("Taille des types\n");
    printf("Size of char : %lu\n", sizeof(char));
    fflush(stdout);
    printf("Size of signed char : %lu\n", sizeof(signed char));
    printf("Size of unsigned char : %lu\n", sizeof(unsigned char));
    printf("Size of short : %lu\n", sizeof(signed short));
    printf("Size of unsigned short : %lu\n", sizeof(unsigned short));
    fflush(stdout);
    printf("Size of int : %lu\n", sizeof(int));
    printf("Size of unsigned int : %lu\n", sizeof(unsigned int));
    printf("Size of long int : %lu\n", sizeof(long int));
    printf("Size of unsigned long int : %lu\n", sizeof(unsigned long int));
    printf("Size of long long int : %lu\n", sizeof(long long int));
    printf("Size of float: %lu\n", sizeof(float));
    printf("Size of double: %lu\n", sizeof(double));
    printf("Size of long double: %lu\n", sizeof(long double));
    return 0;
}
