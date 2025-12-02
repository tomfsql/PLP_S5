#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parseur.h"

int evaluate(MExpression e){
    double p1 = e.operand1;
    char operateur = e.operand;
    double p2 = e.operand2;
    double result;
    switch(operateur){
        case '+':
            result = p1 + p2;
            break;
        case '-':
            result = p1 - p2;
            break;
        case '*':
            result = p1 * p2;
            break;
        case '/':
            if(p2 == 0){
                printf("Erreur: Division par zéro\n");
                return 1;
            }
            result = p1 / p2;
            break;
        default:
            printf("Opérateur inconnu: %c\n", operateur);
            return 1;
    }
    printf("Résultat: %.2f\n", result);
    return 0;
}