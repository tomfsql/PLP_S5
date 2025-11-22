#include <stdio.h>

/*
pour un int, 16 octets, valeur du masque pour commencer par le premier octet : 2^(16-1)
*/

int main(){

    int var,bin[16];
    printf("saisir var :\n");
    scanf("%d",&var);
    for(int i = 0; i<16; i++){
        if(var%2==0){
            bin[i]=0;
        }else{
            var--;
            bin[i] = 1;
        }
        var = var/2;
    }

    for(int i = 15; i>=0;i--){
        printf("%i",bin[i]);
        if(i%4==0 && i!=15) printf(" "); //human readable friendly
    }
    printf("\n");
    return 0;
}