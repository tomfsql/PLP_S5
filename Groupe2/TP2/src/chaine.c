#include <stdio.h>

int taille_chaine(char*);
char* concatene_chaine(char*, char*);
char chaine1chaine2[400];

int main(){

    char chaine1[200];
    char chaine2[200];

    printf("Saisir la première chaîne :\n");
    scanf(" %[^\n]",chaine1);
    printf("Saisir la deuxième chaîne :\n");
    scanf(" %[^\n]",chaine2); //space between " and % is important, it "flushes" the buffer

    printf("taille chaines total : %d\n",taille_chaine(chaine1)+taille_chaine(chaine2));

    printf("Chaines concaténées : %s\n", concatene_chaine(chaine1,chaine2));
    

    return 0;
}

int taille_chaine(char* chaine){
    int i = 0;
    while(*(chaine+i) != '\0'){
        i++;
    }
    return i;
}

char* concatene_chaine(char* chaine1, char* chaine2){
    int i = 0;
    while(*(chaine1+i)!='\0'){ 
        *(chaine1chaine2+i) = *(chaine1+i);
        i++;
    }
    int j = 0;
    while(*(chaine2+j)!='\0'){
        *(chaine1chaine2+i) = *(chaine2+j);
        i++;
        j++; 
    }
    *(chaine1chaine2+i+j)='\0'; //add end of string at the end
    return chaine1chaine2;
}