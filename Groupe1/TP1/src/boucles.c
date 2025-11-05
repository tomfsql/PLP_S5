#include <stdio.h>
#include <limits.h>  
#include <float.h>    

int main(void) {
    int v;
    printf("Entrez une valeur inférieure à 10 ?\n");
    scanf("%d", &v);
    if (v > 10){
        while ( v > 10){
           printf("Entrez une valeur inférieure à 10 ?\n");
           scanf("%d", &v); 
        }
    }
    /* pas la consigne mais c'est joli aussi */
    // for(int i=1;i< v;i++){
    //     for(int j=0;j< i;){
    //         if (j % 2 == 0){
    //             printf("*");
    //             j++;
    //         }
    //         else{
    //             printf("#");
    //             j++;
    //         }
    //     }
    //     printf("\n");
    // }
    for(int i=1;i< v;i++){
        for(int j=0;j< i;){
            if (j == 0 || j == i-1){
                printf(" * ");
                j++;
            }
            else{
                printf(" # ");
                j++;
            }
        }
        printf("\n");
    }
    for(int i=0;i < v;i++){
        printf(" * ");
    }
    printf("\n");   
}
