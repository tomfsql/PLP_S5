#ifndef LEXER_H
#define LEXER_H 


typedef enum {
    Token_nombre,
    Token_plus,
    Token_moins,
    Token_divise,
    Token_multiplie,
    Token_par_ouv,
    Token_par_fer,
    Token_fin,
    Token_identifiant,
    Token_erreur
} TokenType;

typedef struct {
    TokenType type; //type du token
    char valeur; // si opérateur, l'opérateur
    double nombre; //si c'est un nombre, sa valeur
    char nom_variable[64]; //si c'est un identifiant, son nom
} Token;

typedef struct {
    Token Token_i[32]; //tableau de tokens
    int Tokentab_size; //taille du tableau
} TokenTab;

TokenTab tokenizer(const char* expression);

#endif