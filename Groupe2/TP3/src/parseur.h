#ifndef PARSEUR_H
#define PARSEUR_H

#include "lexer.h"

//définition d'un type struct calcul qui contient 2 opérandes et 1 operateur
typedef struct{
    double operande1;
    double operande2;
    char operateur1;
    char operateur2;
} Calcul;

//je définis une structure qui contient un tableau de calculs et sa taille
//(pour la scalabilité, en anticipant la suite de l'exercice)
typedef struct{ 
    Calcul calcul_i[32];
    int Calcultab_size;
} Calcultab;

Calcultab parseur(const TokenTab token_array);

#endif