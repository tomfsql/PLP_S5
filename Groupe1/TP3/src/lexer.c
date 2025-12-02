#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"


int lexer(char* args){
    char p1[50] = "";
    char p2[50] = "";
    char operateur;
    int length = strlen(args);
    int pos = 0;
    int foundp = 0;
    int foundop = 0;
    while ( pos < length ) {
        int posp = 0;
        if ((isdigit((unsigned char)args[pos]) || strchr(separators, args[pos])) && !foundp) {
            while (pos < (int)length && (isdigit((unsigned char)args[pos]) || strchr(separators, args[pos]))) {
                p1[posp++] = args[pos++];
            }
            p1[posp] = '\0';
            foundp = 1;
            continue;
        } 
        else if ((isdigit((unsigned char)args[pos]) || strchr(separators, args[pos])) && foundp){
            posp = 0;
            while (pos < (int)length && (isdigit((unsigned char)args[pos]) || strchr(separators, args[pos]))) {
                p2[posp++] = args[pos++];
            }
            p2[posp] = '\0';
            continue;
        }
        else if (!foundop && strchr(operators, args[pos])) {
            operateur = args[pos++];
            foundop = 1;
            continue;
        }
        else if(isspace((unsigned char)args[pos])){
            pos++;
            continue;
        }
        else {
            printf("Argument non reconnu: %c\n", args[pos]);
            return 1;
            
        }
    }
    if(!foundop || !foundp || strlen(p2) == 0){
        printf("Trop peu d'arguments \n");
        return 1;
    }
    char token[100];
    snprintf(token, sizeof token, "%s%c%s", p1, operateur, p2);
    printf("Token: %s\n", token);
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