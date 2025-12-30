/* ========= EXPLANATIONS ========= */
/* prend en entrée un tableau de tokens (généré par tokenizer() via postfix.c), qui contient un calcul en notation postfixée, et renvoie le résultat de ce calcul.

Fonctionnement : 
Le programme parcourt le tableau de tokens. 
Si c'est un nombre, il l'empile.
Si c'est un opérateur, il réalise l'opération avec les 2 derniers nombres de la pile, et empile le résultat

 */

/* ========= INCLUDES ========= */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "variables.h"

/* ========= MACROS ========= */

/* ========= GLOBAL VARIABLES ========= */
TokenTab token_stack; //contient uniquement des tokens type nombre ( pile de token nombre ).
int calcul_erreur = 0; // 0 = OK, 1 = Erreur
//Variable variable_array[MAX_VARS];

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
        //gestion  des variables dans le calcul
        else if(input_tokens.Token_i[token_i].type == Token_identifiant) {
            int idx = find_variable(input_tokens.Token_i[token_i].nom_variable);
            if(idx == -1) {
                printf("Erreur : la variable %s n'est pas définie\n", input_tokens.Token_i[token_i].nom_variable);
                calcul_erreur = 1;
                return 0;
            }
            // On pousse la valeur de la variable sur la pile
            token_stack.Token_i[token_stack.Tokentab_size].type = Token_nombre;
            if(variable_array[idx].type == TYPE_INT) 
                token_stack.Token_i[token_stack.Tokentab_size].nombre = variable_array[idx].value.i_val;
            else if(variable_array[idx].type == TYPE_REAL)
                token_stack.Token_i[token_stack.Tokentab_size].nombre = variable_array[idx].value.d_val;
            
            token_stack.Tokentab_size++;
        }
        else if (input_tokens.Token_i[token_i].type != Token_fin) {
            
            /* verif : il faut au moins 2 nombres pour un opérateur */
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

    /* Il ne doit rester qu'un seul nombre */
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

// Remplace les occurrences de 'param' par 'valeur' dans 'expr'
void substituer_lambda(char *dest, const char *expr, const char *param, const char *valeur) {
    const char *p = expr;
    char *d = dest;
    size_t param_len = strlen(param);
    size_t val_len = strlen(valeur);

    while (*p) {
        // Si on trouve le paramètre (ex: x) et qu'il n'est pas collé à une autre lettre
        if (strncmp(p, param, param_len) == 0 && !isalnum(p[param_len])) {
            strcpy(d, valeur);
            d += val_len;
            p += param_len;
        } else {
            *d++ = *p++;
        }
    }
    *d = '\0';
}