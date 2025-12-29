#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

/* ========= MACROS ========= */
#define SIZE_MAX 16

/* ========= FUNCTIONS ========= */
int op_prio(char operator);
char stack_handler_char(int way, char operator);
int print_data_postfix(char* sortie);

// Helper pour convertir le caractère de la pile en type de token
TokenType char_to_type(char c) {
    if (c == '+') return Token_plus;
    if (c == '-') return Token_moins;
    if (c == '*') return Token_multiplie;
    if (c == '/') return Token_divise;
    return Token_erreur;
}

/* ========= GLOBAL VARIABLES ========= */
char pile[256]; //pile d'opérateurs
int pile_i = 0;

TokenTab postfix(char* commande){

    char sortie[1024]; //chaine de sortie, non utilisée si print_data_postfix(sortie) n'est pas appelée. Warning de compilation normal.
    int token_i = 0;
    int sortie_i = 0;
    TokenTab token_out; //tableau de tokens de sortie, destiné à l'évaluateur
    token_out.Tokentab_size = 0;

    TokenTab token_array = tokenizer(commande); //renvoie l'expression en tokens 
    while(token_i < token_array.Tokentab_size){
        Token curr_token = token_array.Token_i[token_i]; //pour simplifier la lecture
        token_i++;

        // gestion des nombres
        if( curr_token.type == Token_nombre )
        {
            sortie[sortie_i] = (char)((int)curr_token.nombre + '0'); // Debug string (limité à 0-9)
            
            // replissage du tokentab de sortie
            token_out.Token_i[token_out.Tokentab_size].nombre = curr_token.nombre;
            token_out.Token_i[token_out.Tokentab_size].type = Token_nombre;
            token_out.Tokentab_size++;
            
            sortie_i++;
            //printf("Nombre ajouté à la sortie %.2f \n",curr_token.nombre);
            continue;
        }

        // gestion des opérateurs
        if( curr_token.type == Token_divise || curr_token.type == Token_multiplie || curr_token.type == Token_moins || curr_token.type == Token_plus )
        {
            if(pile_i == 0 || op_prio(curr_token.valeur) > op_prio(pile[0]) ){
                stack_handler_char(0,curr_token.valeur);
                //printf("Opérateur %c empilé\n",curr_token.valeur);
            }else{
                // On dépile jusqu'à trouver un opérateur avec moins de priorité
                while(pile_i > 0 && op_prio(curr_token.valeur) <= op_prio(pile[0])) {
                    char d = stack_handler_char(1, '\0');
                    sortie[sortie_i] = d;
                    
                    // Ajout de l'opérateur dépilé au tokentab
                    token_out.Token_i[token_out.Tokentab_size].valeur = d;
                    token_out.Token_i[token_out.Tokentab_size].type = char_to_type(d);
                    token_out.Tokentab_size++;
                    
                    sortie_i++;
                }
                stack_handler_char(0, curr_token.valeur);
                //printf("Opérateur %c empilé après dépilage\n",curr_token.valeur);
            }
            continue;
        }

        // gestion de la par ouvrante
        if(curr_token.type == Token_par_ouv){
            stack_handler_char(0,curr_token.valeur);
            //printf("Parenthèse ouvrante empilée\n");
            continue;
        }

        // gestion de la par fermante
        if(curr_token.type == Token_par_fer){
            while(pile_i > 0 && pile[0] != '('){
                char d = stack_handler_char(1, '\0');
                sortie[sortie_i] = d;
                
                // Ajout au tokentab de sortie
                token_out.Token_i[token_out.Tokentab_size].valeur = d;
                token_out.Token_i[token_out.Tokentab_size].type = char_to_type(d);
                token_out.Tokentab_size++;
                
                sortie_i++;
            }
            if (pile_i > 0 && pile[0] == '(') {
                stack_handler_char(1, '\0'); // On supprime '(' sans l'ajouter à la sortie
            }
            //printf("Parenthèse fermante : dépilage terminé\n");
            continue;
        }
    }

    // On vide les opérateurs restants à la fin
    while(pile_i > 0){
        char d = stack_handler_char(1,'\0');
        sortie[sortie_i] = d;
        
        token_out.Token_i[token_out.Tokentab_size].valeur = d;
        token_out.Token_i[token_out.Tokentab_size].type = char_to_type(d);
        token_out.Tokentab_size++;
        
        sortie_i++;
    }

    sortie[sortie_i] = '\0'; 
    //print_data_postfix(sortie);
    
    // Ajout d'un token de fin pour la sécurité de l'évaluateur
    token_out.Token_i[token_out.Tokentab_size].type = Token_fin;

    return token_out;
}

int op_prio(char operator){
    if(operator == '-' || operator == '+')
        return 1;
    if(operator == '/' || operator == '*')
        return 2;
    if(operator == '(') 
        return 0; 
    return 0;
}

char stack_handler_char(int way, char operator){
    if(way == 0){ // Empiler
        for(int j = pile_i ; j > 0 ; j--){
            pile[j] = pile[j-1];
        }
        pile[0] = operator;
        pile_i++;
        return '\0';
    }
    else if(way == 1){ // Dépiler
        char res = pile[0];
        for(int j = 0 ; j < pile_i -1 ; j++){
            pile[j] = pile[j+1];
        }
        pile_i--;
        return res;
    }
    return '\0';
}

int print_data_postfix(char* sortie){
    printf("Sortie String : %s\n", sortie);
    return 0;
}