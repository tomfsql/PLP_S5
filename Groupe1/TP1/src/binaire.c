#include <stdio.h>

int main(void) {
    int num;
    int binaire[32]; 
    int index = 0;   

    printf("Entrez un nombre entier (positif ou nul) : ");
    scanf("%d", &num);

    int original_num = num;

    if (num == 0) {
        printf("Le binaire de 0 est : 0\n");
        return 0;
    }

    while (num > 0) {
        binaire[index] = num % 2;
        
        num = num / 2;
        
        index++;
    }
    
    printf("Le binaire de %d est : ", original_num);
    
    for (int i = index - 1; i >= 0; i--) {
        printf("%d", binaire[i]);
    }
    printf("\n");

    return 0;
}