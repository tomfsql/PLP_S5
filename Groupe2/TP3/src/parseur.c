/* ========= INCLUDES ========= */
#include "parseur.h"
#include <stdio.h>
#include <string.h>

/* ========= FUNCTIONS ========= */
int print_data_parser(Calcultab);
char operator_type_to_char(TokenType);

/* ========= EXPLANATIONS ========= */
/*
schéma de fonctionnement :
le parseur va traiter les tokens 1 par 1. Ils sont stockés dans le tableau dans l'ordre suivant :
opérande1 opérateur1 opérande2 opérateur2 opérande3 opérateur3 opérande4...
pour les stocker dans des struct contenant 2 opérandes et 1 opérateur, je procède comme suit :
struct1_calcul => opérande1, opérateur1, opérande2
struct2_calcul => NULL , opérateur2, opérande3
struct3_calcul => NULL, opérateur3, opérande4
et ainsi de suite.

*/

/* ========= GLOBAL VARIABLES ========= */

Calcultab parseur(const TokenTab token_array){
    Calcultab tab;
    memset(&tab, 0, sizeof(Calcultab)); // init du tableau à 0
    tab.Calcultab_size = 1; //le nombre d'unités du tableau tab (nombre de calculs traités)
    //pour les 3 premiers tokens, ils vont automatiquement dans la première structure calcul
    tab.calcul_i[0].operande1 = token_array.Token_i[0].nombre;
    tab.calcul_i[0].operateur = operator_type_to_char(token_array.Token_i[1].type);
    tab.calcul_i[0].operande2 = token_array.Token_i[2].nombre;

    if(token_array.Tokentab_size > 3){ //vérif pour savoir si il ya plus que 2 opérandes et 1 opérateur
        for(int i = 3 ; i< token_array.Tokentab_size;i+=2){ //on parcours les token 1 par 1 en skippant les 3 premiers, déjà traités
            tab.calcul_i[tab.Calcultab_size].operande1 = 0; // on le met à 0
            tab.calcul_i[tab.Calcultab_size].operateur = operator_type_to_char(token_array.Token_i[i].type);
            tab.calcul_i[tab.Calcultab_size].operande2 = token_array.Token_i[i+1].nombre;
            tab.Calcultab_size++;
        }
    }


    tab.Calcultab_size = tab.Calcultab_size;
    print_data_parser(tab);
    return tab;
} 

int print_data_parser(Calcultab tab){
    printf("==========parseur finished============== \n");
    printf("Data : ");
    printf(" %.2f",tab.calcul_i[0].operande1);
    printf(" %c", tab.calcul_i[0].operateur);
    printf(" %.2f", tab.calcul_i[0].operande2);
    if(tab.Calcultab_size > 1){
        for(int i=1 ; i<= tab.Calcultab_size ; i++){
            printf(" %c", tab.calcul_i[i].operateur);
            printf(" %.2f", tab.calcul_i[i].operande2);
        }
    }
    printf("\nTaille Calcultab : %d",tab.Calcultab_size);
    printf("\n");
    return 1;
}

char operator_type_to_char(TokenType type){
    switch(type) {
        case Token_plus:      return '+'; break;
        case Token_moins:     return '-'; break;
        case Token_multiplie: return '*'; break;
        case Token_divise:    return '/'; break;
        default: return '\0'; break;
    }
}