#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "parseur.h"

const char operators[] = "+-*/";
const char separators[] = ",.";


int lexer(char* args) {
    char p1[50] = "";
    char p2[50] = "";
    char operateur;
    int length = strlen(args);
    int pos = 0;
    
    int foundp = 0; 
    int foundop = 0;

    while (pos < length) {
        
        if (foundp == 0 && (isdigit((unsigned char)args[pos]) || args[pos] == '-' || strchr(separators, args[pos]))) {
            int posp = 0;
            int nbSep = 0;
            
            if (args[pos] == '-') {
                p1[posp++] = args[pos++];
            }

            while (pos < length) {
                char c = args[pos];
                
                if (isdigit((unsigned char)c)) {
                    p1[posp++] = args[pos++];
                } 
                else if (strchr(separators, c)) {
                    if (nbSep >= 1) break; 
                    nbSep++;
                    p1[posp++] = args[pos++];
                } 
                else {
                    break; 
                }
            }
            p1[posp] = '\0';

            if (strlen(p1) == 0 || (strcmp(p1, ".") == 0) || (strcmp(p1, "-") == 0) || (strcmp(p1, "-.") == 0)) {
                 printf("Erreur: Nombre mal formé (p1)\n");
                 return 1;
            }

            foundp = 1;
            continue;
        }
        else if (foundp == 1 && foundop == 0 && strchr(operators, args[pos])) {
            operateur = args[pos++];
            foundop = 1;
            continue;
        }
        else if (foundp == 1 && foundop == 1 && (isdigit((unsigned char)args[pos]) || args[pos] == '-' || strchr(separators, args[pos]))) {
            int posp = 0;
            int nbSep = 0;

            if (args[pos] == '-') {
                p2[posp++] = args[pos++];
            }

            while (pos < length) {
                char c = args[pos];
                
                if (isdigit((unsigned char)c)) {
                    p2[posp++] = args[pos++];
                } 
                else if (strchr(separators, c)) {
                    if (nbSep >= 1) break; 
                    nbSep++;
                    p2[posp++] = args[pos++];
                } 
                else {
                    break;
                }
            }
            p2[posp] = '\0';
            if (strlen(p2) == 0 || (strcmp(p2, ".") == 0) || (strcmp(p2, "-") == 0) || (strcmp(p2, "-.") == 0)) {
                 printf("Erreur: Nombre mal formé (p2)\n");
                 return 1;
            }

            foundp = 2; 
            continue;
        }
        else if (isspace((unsigned char)args[pos])) {
            pos++;
            continue;
        }
        else {
            printf("Argument non reconnu ou ordre incorrect: %c\n", args[pos]);
            return 1;
        }
    }

    if (!foundop || foundp < 2) {
         printf("Trop peu d'arguments \n");
         return 1;
    }

    char opStr[2] = {operateur, '\0'};
    char* tokens[] = { p1, opStr, p2, NULL };
    
    parser(tokens);
    return 0;
}

int main(){
    int keep = 1;
    char args[100];
    while(keep){
        printf("Entrez les arguments ( exit pour quitter): ");
        if (!fgets(args, sizeof args, stdin)) return 1;
        if (strncmp(args, "ex",2) == 0) return 0;
        size_t len = strlen(args);
        if (len && args[len-1] == '\n') args[len-1] = '\0';
        lexer(args);
    }
    return 0;
}