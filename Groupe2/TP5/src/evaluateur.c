/* ========= EXPLANATIONS ========= */
/* prend en entrée un tableau de tokens (généré par tokenizer() via postfix.c), qui contient un calcul en notation postfixée, et renvoie le résultat de ce calcul.

Fonctionnement : 
Le programme parcourt le tableau de tokens. 
Si c'est un nombre, il l'empile.
Si c'est un opérateur, il réalise l'opération avec les 2 derniers nombres de la pile, et empile le résultat

 */

/* ========= INCLUDES ========= */
#include <stdio.h>
#include "lexer.h"

/* ========= MACROS ========= */

/* ========= GLOBAL VARIABLES ========= */
TokenTab token_stack; //contient uniquement des tokens type nombre ( pile de token nombre ).
int calcul_erreur = 0; // 0 = OK, 1 = Erreur

/* ========= FUNCTIONS ========= */
int print_token_tab(TokenTab);

double evaluateur(TokenTab input_tokens){
    token_stack.Tokentab_size = 0;
    calcul_erreur = 0; // On reset l'erreur au début
    
    int token_i;
    for(token_i = 0; token_i < input_tokens.Tokentab_size; token_i++){
        
        if(input_tokens.Token_i[token_i].type == Token_nombre){
            token_stack.Token_i[token_stack.Tokentab_size] = input_tokens.Token_i[token_i];
            token_stack.Tokentab_size++;
        } 
        else if (input_tokens.Token_i[token_i].type != Token_fin) {
            
            /* VERIFICATION : Il faut au moins 2 nombres pour un opérateur */
            if(token_stack.Tokentab_size < 2) {
                printf("Erreur : Expression mal formée (opérande manquante pour '%c')\n", input_tokens.Token_i[token_i].valeur);
                calcul_erreur = 1;
                return 0;
            }

            double op2 = token_stack.Token_i[token_stack.Tokentab_size - 1].nombre;
            double op1 = token_stack.Token_i[token_stack.Tokentab_size - 2].nombre;
            double res = 0;

            switch(input_tokens.Token_i[token_i].type){
                case Token_divise :
                    /* GESTION DIVISION PAR ZERO */
                    if(op2 == 0) {
                        printf("Erreur : Division par zéro impossible !\n");
                        calcul_erreur = 1;
                        return 0;
                    }
                    res = op1 / op2;
                    break;
                case Token_multiplie : res = op1 * op2; break;
                case Token_moins : res = op1 - op2; break;
                case Token_plus : res = op1 + op2; break;
                default : break;
            }

            token_stack.Tokentab_size -= 2;
            token_stack.Token_i[token_stack.Tokentab_size].nombre = res;
            token_stack.Token_i[token_stack.Tokentab_size].type = Token_nombre;
            token_stack.Tokentab_size++;
        }
    }

    /* VERIFICATION FINALE : Il ne doit rester qu'un seul nombre */
    if(token_stack.Tokentab_size != 1) {
        printf("Erreur : Trop de nombres ou opérateurs manquants.\n");
        calcul_erreur = 1;
        return 0;
    }
    
    return token_stack.Token_i[0].nombre;
}


int print_token_tab(TokenTab tab){
    for( int i = 0 ; i < tab.Tokentab_size ; i++ ){
        switch(tab.Token_i[i].type){
            case Token_nombre :
                printf("[%.2f] ", tab.Token_i[i].nombre);
                break;
            default: break;
        }
    }
    return 0;
}