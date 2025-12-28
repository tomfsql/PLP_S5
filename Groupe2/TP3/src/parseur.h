#ifndef PARSEUR_H
#define PARSEUR_H

#include "lexer.h"

//définition d'un type struct calcul qui contient 2 opérandes et 1 operateur
typedef struct{
    double operande1;
    double operande2;
    char operateur;
} Calcul;

//je définis une structure qui contient un tableau de calculs et sa taille
//(pour la scalabilité, possibilité de faire plusieurs calculs à la suite (par ex 2+3+4+5))
typedef struct{ 
    Calcul calcul_i[32];
    int Calcultab_size;
} Calcultab;

Calcultab parseur(const TokenTab token_array);

#endif