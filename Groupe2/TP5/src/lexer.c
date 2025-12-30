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
    const char *p = expression; // on utilise un pointeur pour parcourir la chaîne

    while (*p != '\0') { //on parcours la chaine entrée
        //Ignorer les espaces
        if (isspace(*p)) {
            p++;
            continue; //on retourne au début de la boucle
        }

        // détecter si on doit lire un nombre :
        // un nombre commence par un chiffre OU par un '-' suivi d'un chiffre (nombre négatif)
        // mais le '-' fait partie d'un nombre seulement s'il est au début ou après un autre opérateur
        if (isdigit(*p) || (*p == '-' && (liste.Tokentab_size == 0 || liste.Token_i[liste.Tokentab_size-1].type != Token_nombre))) {
            char *fin_nombre;
            double val = strtod(p, &fin_nombre);

            if (p != fin_nombre) { // si un nombre a bien été lu, on le rajoute au tableau de tokens
                liste.Token_i[liste.Tokentab_size].type = Token_nombre;
                liste.Token_i[liste.Tokentab_size].nombre = val;
                liste.Tokentab_size++;
                p = fin_nombre; // on avance le pointeur à la fin du nombre lu
                continue; //on retourne au début de la boucle
            }
        }

        // pour détecter les opérateurs
        if (est_operateur(*p)) {
            switch (*p) {
                case '+': liste.Token_i[liste.Tokentab_size].type = Token_plus; 
                    liste.Token_i[liste.Tokentab_size].valeur = '+'; 
                    break;
                case '-': liste.Token_i[liste.Tokentab_size].type = Token_moins; 
                    liste.Token_i[liste.Tokentab_size].valeur = '-';
                    break;
                case '*': liste.Token_i[liste.Tokentab_size].type = Token_multiplie; 
                    liste.Token_i[liste.Tokentab_size].valeur = '*';
                    break;
                case '/': liste.Token_i[liste.Tokentab_size].type = Token_divise; 
                    liste.Token_i[liste.Tokentab_size].valeur = '/';
                    break;
                case '(': liste.Token_i[liste.Tokentab_size].type = Token_par_ouv; 
                    liste.Token_i[liste.Tokentab_size].valeur = '(';
                    break;
                case ')': liste.Token_i[liste.Tokentab_size].type = Token_par_fer; 
                    liste.Token_i[liste.Tokentab_size].valeur = ')';
                    break;
            }
            liste.Tokentab_size++;
            p++;
            continue; //on retourne au début de la boucle
        }

        //gestion des variables
        if (isalpha(*p) || (unsigned char)*p > 127) { // isalpha ou début d'UTF-8
            int j = 0;
            char name[64];
            while (isalnum(*p) || (unsigned char)*p > 127 || *p == '_') {
                if (j < 63) name[j++] = *p++;
                else p++;
            }
            name[j] = '\0';
            
            liste.Token_i[liste.Tokentab_size].type = Token_identifiant;
            strcpy(liste.Token_i[liste.Tokentab_size].nom_variable, name); 
            liste.Tokentab_size++;
            continue;
        }
        // gestion des caractères non reconnus (autrement dit, erreur et exit)
        if (!isspace(*p) && *p != '\0') {
            printf("Erreur Lexer : Caractère non reconnu '%c'\n", *p);
            liste.Token_i[liste.Tokentab_size].type = Token_erreur;
            liste.Tokentab_size++;
            continue;
        }
        
        p++; 
    }

    // Ajout d'un token de fin (optionnel mais utile pour le parseur)
    liste.Token_i[liste.Tokentab_size].type = Token_fin;
    
    // Debug
    //print_data_lexer(liste); 
    return liste;
}