#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//fonction utilitaire pour vérifier si un caractère est un opérateur
int est_operateur(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')');
}

int print_data_lexer(TokenTab data){ //fonction  d'affichage des data qui sont envoyées au parseur
    
    printf("========== lexer finished ============== \n");
    printf("Data : ");
    for(int i=0 ; i<= data.Tokentab_size ; i++){
        switch (data.Token_i[i].type)
        {
        case Token_nombre:
            printf(" %.2f", data.Token_i[i].nombre);
            break;
        case Token_plus:
            printf(" +");
            break;
        case Token_moins:
            printf(" -");
            break;
        case Token_multiplie:
            printf(" *");
            break;
        case Token_divise:
            printf(" /");
            break;
        default:
            break;
        }
    }
    printf("\nTaille Token_tab : %d",data.Tokentab_size);
    printf("\n");
    return 1;
}

TokenTab tokenizer(const char* expression) {
    TokenTab liste;
    liste.Tokentab_size = 0;
    const char *p = expression;

    while (*p != '\0') {
        if (isspace(*p)) { 
            p++; 
            continue; 
        }

        // détecter si on doit lire un nombre :
        // un nombre commence par un chiffre OU par un '-' suivi d'un chiffre (nombre négatif)
        // mais le '-' fait partie d'un nombre seulement s'il est au début ou après un autre opérateur
        if (isdigit(*p) || (*p == '.' && isdigit(*(p+1)))) {
            char *fin;
            liste.Token_i[liste.Tokentab_size].nombre = strtod(p, &fin);
            liste.Token_i[liste.Tokentab_size].type = Token_nombre;
            liste.Tokentab_size++;
            p = fin;
            continue;
        }

        // Détection des identifiants (variables & UTF-8)
        if (isalpha(*p) || (unsigned char)*p > 127) {
            int j = 0;
            while (isalnum(*p) || (unsigned char)*p > 127 || *p == '_') {
                liste.Token_i[liste.Tokentab_size].nom_variable[j++] = *p++;
            }
            liste.Token_i[liste.Tokentab_size].nom_variable[j] = '\0';
            liste.Token_i[liste.Tokentab_size].type = Token_identifiant;
            liste.Tokentab_size++;
            continue;
        }

        // pour détecter les opérateurs et les parenthèses
        if (est_operateur(*p)) {
            switch(*p) {
                case '+': liste.Token_i[liste.Tokentab_size].type = Token_plus; break;
                case '-': liste.Token_i[liste.Tokentab_size].type = Token_moins; break;
                case '*': liste.Token_i[liste.Tokentab_size].type = Token_multiplie; break;
                case '/': liste.Token_i[liste.Tokentab_size].type = Token_divise; break;
                case '(': liste.Token_i[liste.Tokentab_size].type = Token_par_ouv; break;
                case ')': liste.Token_i[liste.Tokentab_size].type = Token_par_fer; break;
            }
            liste.Token_i[liste.Tokentab_size].valeur = *p;
            liste.Tokentab_size++;
            p++;
            continue;
        }
        p++; // ignorer le reste
    }
    liste.Token_i[liste.Tokentab_size].type = Token_fin;
    return liste;
}
