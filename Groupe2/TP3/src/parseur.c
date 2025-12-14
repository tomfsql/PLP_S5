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

Calcultab parseur(const TokenTab token_array){
    Calcultab tab;
    //première version : marche pour 1 seul calcul. Possibilité d'ajout de flottants
    // et plusieurs calculs plus tard.
    for(int i = 0 ; i< token_array.Tokentab_size;i++){
        printf("parseur token %d valeur : %s\n",i,token_array.Token_i[i].valeur);
        printf("parseur token %d nombre : %f\n",i,token_array.Token_i[i].nombre);
    
    if(token_array.Token_i[0].type == Token_nombre) //vérif. que le token soit un nombre
        tab.calcul_i[0].operande1 = token_array.Token_i[0].nombre;
    if(token_array.Token_i[2].type == Token_nombre) //vérif. que le token soit un nombre
        tab.calcul_i[0].operande2 = token_array.Token_i[2].nombre;
    switch (token_array.Token_i[1].type)
    {
    case Token_divise:
        tab.calcul_i[0].operateur = '/';
        break;
    case Token_moins:
        tab.calcul_i[0].operateur = '-';
        break;
    case Token_plus:
        tab.calcul_i[0].operateur = '+';
        break;
    case Token_multiplie:
        tab.calcul_i[0].operateur = '*';
        break;
    default:
        break;
    }
    }

    printf("Data : %f %c %f\n",tab.calcul_i[0].operande1,tab.calcul_i[0].operateur,tab.calcul_i[0].operande2);
    return tab;
}