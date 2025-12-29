/* ========= EXPLANATIONS ========= */
/*
coder un algorithe qui transforme une chaine de caractères contenant une expression infixée en postfixée. Par exemple :
infixée :  3+4*(5-2)
postfixée : 3452-*+

fonctionnement :
initialisation : pile qui est vide, qui contiendra les opérateurs
parcours de l'expression : 
    si nombre rencontré, on l'ajoute à la sortie
    si opérateur rencontré :
        si pile vide ou opérateur a une prio plus élevée que le dernier item de la pile, on empile l'opérateur
        sinon, on dépile la pile jusqu'à trouver un opérateur avec moins de prio, et on ajoute ces opérateurs à la sortie
    si parenthèse ouvrante : on la pousse sur la pile
    si parenthèse fermante : on dépile la pile et on ajoute à la sortie les opérateurs jusqu'à une parenthèse ouvrante, et la supprimer
à la fin, dépiler tous les opérateurs de la pile

*/
/* ========= INCLUDES ========= */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

/* ========= FUNCTIONS ========= */
int op_prio(char operator);

char pile_handler(int way, char operator);

/* ========= GLOBAL VARIABLES ========= */
char pile[256]; //pile d'opérateurs
int pile_i = 0;

int main(){

    printf("> "); // Affiche le prompt de commande

    // Buffer pour stocker la commande utilisateur
    char commande[1024];
    char sortie[1024]; //chaine de sortie
    int token_i = 0;
    int sortie_i = 0;


    // Lit la commande utilisateur et la stocke dans le buffer
    fgets(commande, sizeof(commande), stdin);
    /*
    pile[0] = 'a';
    pile[1] = 'b';
    pile[2] = 'c';
    pile[3] = 'd';
    pile_i=4;
    for(int i = 0 ; i < pile_i ; i++){
        printf("Pile[%d] : %c\n",i,pile[i]);
    }
    pile_handler(0,'z');
    printf("Empilage\n");
    for(int i = 0 ; i < pile_i ; i++){
        printf("Pile[%d] : %c\n",i,pile[i]);
    }
    char c = pile_handler(1,'z');
    printf("dépilage\n");
    for(int i = 0 ; i < pile_i ; i++){
        printf("Pile[%d] : %c\n",i,pile[i]);
    }
    printf("retour dépilage : %c\n",c);
    */


    TokenTab token_array = tokenizer(commande); //renvoie l'expression en tokens 
    while(token_i < token_array.Tokentab_size){
        Token curr_token = token_array.Token_i[token_i]; //pour simplifier la lecture; on manipule le token courant
        if( curr_token.type == Token_nombre )
        {
             sortie[strlen(sortie)] == curr_token.nombre;
        }

        if( curr_token.type == Token_divise || curr_token.type == Token_multiplie || curr_token.type == Token_moins || curr_token.type == Token_plus )
        {
            if(strlen(pile) == 0 || op_prio(curr_token.valeur) > op_prio(pile[pile_i]) ){
                pile_handler(0,curr_token.valeur);
            }else{
                do{
                    char c = pile[]

                }while()
            }
        }
    }

    return 0;
}

int op_prio(char operator){
    if(operator == '-' || operator == '+')
        return 1; //prio basse
    if(operator == '/' || operator == '*')
        return 2; //prio moyenne
    if(operator == '(' || operator == ')')
        return 3; //prio haute
    return 0; //default : prio nulle
}


char pile_handler(int way, char operator){
    if(way == 0){ // signifie que l'on doit empiler
        for(int j = pile_i ; j >= 0 ; j--){
            pile[j+1] = pile[j];
        }
        pile[0] = operator;
        pile_i++;
        return '\0';
    }
    else if(way == 1){ //signifie que l'on doit dépiler
        char res = pile[0];
        for(int j = 0 ; j <= pile_i ; j++){
            pile[j] = pile[j+1];
        }
        pile_i--;
        return res;
    }else{
        return '\0';
    }
}