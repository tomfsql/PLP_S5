#ifndef EVALUATEUR_H
#define EVALUATEUR_H

#include "lexer.h"
//utile dans repl
extern int calcul_erreur;


double evaluateur(TokenTab);
void substituer_lambda(char *dest, const char *expr, const char *param, const char *valeur);

#endif