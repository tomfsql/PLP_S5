#include <stdio.h>

int main(){
    int num1, num2;
    char op;
    printf("Entrer l'opération avec des espaces (ex : 2 + 4) :\n");
    scanf("%i %c %i", &num1,&op,&num2);
    switch(op){
        case '+' :
            num1 = num1 + num2;
            break;
        case '-': 
            num1 = num1 - num2;
            break;
        case '*': 
            num1 = num1 * num2;
            break;
        case '/': 
            if(num2 == 0){
                printf("Erreur : division par 0\n");
            }
            else{
                printf("Résultat : %.3f\n",(float)num1/num2);
            }
            return 1;
            break;
        case '%': 
            num1 = num1 % num2;
            break;
        case '&': 
            num1 = num1 & num2;
            break;
        case '|': 
            num1 = num1 | num2;
            break;
        case '~': 
            num1 = ~num1;
            break;
        default : printf("Mauvaise utilisation : recommencer");
    }
    printf("Résultat : %d\n",num1);


    return 0;
}