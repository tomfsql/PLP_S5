#include <stdio.h>

int main(){
    int taille;
    char version;
    printf("Saisir un entier inférieur à 10 : ");
    scanf("%d",&taille);
    getchar();
    printf("saisir quelle version for (f) ou while (w) : ");
    scanf("%c", &version);
    getchar();
    if(version=='f'){
        printf("* \n");
        for(int i = 1 ; i < taille ; i++){
            printf("* ");
            if(i == (taille-1)){
                for(int k = 1; k < taille; k++) printf("* ");
            }
            else{
                for(int j = 1 ; j < i ; j++){
                    printf("# ");
                }
                printf("*\n");
            }          
        }
        printf("\n");
    }

    if(version=='w'){
        printf("*\n");
        int i = 1 ,j = 1,k = 0;
        while(i<(taille-1)){
            printf("* ");
            while(j<i){
                printf("# ");
                j++;
            }
            printf("*\n");
            i++;
            j = 1;
        }
        while(k<taille){ 
            printf("* ");
            k++;
        }
        printf("\n");
    }
    return 0;
}