#include <stdio.h>

/*
 Parcourez les nombres de 1 à 1000 et appliquez les conditions suivantes :

* Divisible par 4 mais pas par 6
* Nombre pair et divisible par 8
* Divisible par 5 ou 7 mais pas par 10
*/
/* 
Not very human readable output version, but quickest 

int main(){
    for(int i = 1; i<=1000;i++){
        if((i%4 == 0) && (i%6 != 0)) printf("Divisible par 4 mais pas par 6 : %i\n",i);
        if(i%8 == 0) printf("Pair et divisible par 8 : %i\n",i); // divisible par 8 est forcément pair
        if(((i%5 == 0) || (i%7 == 0)) && !(i%10 == 0)) printf("Divisible par 5 ou 7 mais pas par 10 : %i\n",i);
    }

    return 0;
}

*/

// more human friendly version
int main(){
    printf("=========\nDivisible par 4 mais pas par 6 : ========\n");
    for(int i = 1; i<=1000;i++){
    if((i%4 == 0) && (i%6 != 0)) printf("%i ; ",i);
    }
    printf("\n========Pair et divisible par 8 :======== \n");
    for(int i = 1; i<=1000;i++){
    if(i%8 == 0) printf("%i ; ",i); // divisible par 8 est forcément pair
    }
    printf("\n=======Divisible par 5 ou 7 mais pas par 10 :=======\n");
    for(int i = 1; i<=1000;i++){
        if(((i%5 == 0) || (i%7 == 0)) && !(i%10 == 0)) printf("%i ; ",i);
    }
    return 0;
}