#ifndef LEXER_H
#define LEXER_H 


typedef enum {
    Token_nombre,
    Token_plus,
    Token_moins,
    Token_divise,
    Token_multiplie,
    Token_fin,
    Token_erreur
} TokenType;

typedef struct {
    TokenType type; //type du token
    char valeur; // si opérateur, l'opérateur
    double nombre; //si c'est un nombre, sa valeur
} Token;

typedef struct {
    Token Token_i[32]; //tableau de tokens
    int Tokentab_size; //taille du tableau
} TokenTab;

TokenTab tokenizer(const char* expression);

#endif