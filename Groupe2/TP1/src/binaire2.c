#include <stdio.h>

/*
pour un int, 16 octets, valeur du masque pour commencer par le premier octet : 2^(16-1)
*/

int main(){

    int var,masque = 32768,res_temp;
    printf("saisir var :\n");
    scanf("%d",&var);
    for(int i = 16; i>0; i--){
        if(i%4 == 0 && i!=16) printf(" "); //humain readable friendly
        res_temp = var & masque;
        if(res_temp != 0) res_temp = 1;
        printf("%i",res_temp);
        masque=masque >> 1;
    }
    printf("\n");
    return 0;
}