#include "parseur.h"
#include <stdio.h>

/* reminder
typedef struct {
    TokenType type; //type du token
    char valeur[50]; // chaine de caractères du token
    double nombre; //si c'est un nombre, sa valeur
} Token;

typedef struct {
    Token Token_i[32]; //tableau de tokens
    int Tokentab_size; //taille du tableau
} TokenTab;

typedef struct{
    double operande1;
    double operande2;
    char operateur;
} Calcul;

typedef struct{ 
    Calcul calcul_i[32];
    int Calcultab_size;
} Calcultab;
*/

int print_data(Calcultab);

Calcultab parseur(const TokenTab token_array){
    Calcultab tab;
    int expression_i = 0; // compte le nombre d'expressions (2+3)
    int operande_i = 0; //pour voir si il s'agit de la première ou seconde opérande
    int operateur_i = 0; //pour voir s'il s'agit du premier ou second operateur
    //deuxième version : modification pour faire plusieurs calculs (2+3+4 par exemple)
    for(int i = 0 ; i< token_array.Tokentab_size;i++){
        if(i%4==0 && i!=0) //si on a fini de remplir 1 calcul
            expression_i++; //on remplit le calcul suivant

        switch(token_array.Token_i[i].type){
            case Token_nombre :
                if(operande_i == 0){
                    tab.calcul_i[expression_i].operande1 = token_array.Token_i[i].nombre;
                    operande_i++;
                }else if(operande_i == 1){
                    tab.calcul_i[expression_i].operande2 = token_array.Token_i[i].nombre;
                    operande_i = 0;
                }
                break;
            case Token_divise :
                if(operateur_i == 0){
                    tab.calcul_i[expression_i].operateur1 = '/' ;
                    operateur_i++;
                }else if(operateur_i == 1 && token_array.Token_i[i+1].type == Token_nombre){
                    tab.calcul_i[expression_i].operateur2 = '/' ;
                    operateur_i = 0;
                }                
                break;
            case Token_moins :
                if(operateur_i == 0){
                    tab.calcul_i[expression_i].operateur1 = '-' ;
                    operateur_i++;
                }else if(operateur_i == 1 && token_array.Token_i[i+1].type == Token_nombre){
                    tab.calcul_i[expression_i].operateur2 = '-' ;
                    operateur_i = 0;
                }   
                break;
            case Token_multiplie :
                if(operateur_i == 0){
                    tab.calcul_i[expression_i].operateur1 = '*' ;
                    operateur_i++;
                }else if(operateur_i == 1 && token_array.Token_i[i+1].type == Token_nombre){
                    tab.calcul_i[expression_i].operateur2 = '*' ;
                    operateur_i = 0;
                }                   break;
            case Token_plus :
                if(operateur_i == 0){
                    tab.calcul_i[expression_i].operateur1 = '+' ;
                    operateur_i++;
                }else if(operateur_i == 1 && token_array.Token_i[i+1].type == Token_nombre){
                    tab.calcul_i[expression_i].operateur2 = '+' ;
                    operateur_i = 0;
                }
                break;
            default :
                break;
        }
    }
    tab.Calcultab_size = expression_i;
    print_data(tab);
    return tab;
} 

int print_data(Calcultab tab){
    
    printf("Data : ");
    for(int i=0 ; i<= tab.Calcultab_size ; i++){
        printf(" %.2f",tab.calcul_i[i].operande1);
        printf(" %c", tab.calcul_i[i].operateur1);
        printf(" %.2f", tab.calcul_i[i].operande2);
        if(tab.calcul_i[i].operateur1 == '\0' || tab.calcul_i[i].operateur2 == '\0'){
            printf("\n");
            return 1;

        }else{
            printf(" %c",tab.calcul_i[i].operateur2);
        }
    }
    printf("\n");
    return 1;
}

/*
int print_data(Calcultab tab){
    
    printf("Data : ");
    for(int i=0 ; i<= tab.Calcultab_size ; i++){
        printf("%.2f %c %.2f ",tab.calcul_i[i].operande1,tab.calcul_i[i].operateur1,tab.calcul_i[i].operande2);
        if(tab.calcul_i[i].operateur2 != '\0' ){
            printf("%c ",tab.calcul_i[i].operateur2);
        }
    }
    printf("\n");
    return 1;
}
    */