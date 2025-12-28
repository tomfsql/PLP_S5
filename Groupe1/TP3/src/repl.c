#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "parse.h"
#include "calc.h"
/**
 * Programme qui simule un interpréteur de commandes simple.
 * Il lit les commandes utilisateur et les traite en fonction de leur contenu.
 */

int version = 3.0;

struct function
{
    char* name;
    int (*func)(char*);
};


int afficher_version(char* args){
    printf("TP3 - REPL Simple - Version %d\n", version);
    return 1;
}

int afficher_date(char* args){
    time_t current_time = time(NULL);
    char date_string[20];
    strftime(date_string, 20, "%d-%m-%Y", localtime(&current_time));
    printf("La date actuelle est : %s\n", date_string);
    return 1;
}

int traiter_quit(char* args){
    printf("Arrêt...\n");
    return 0;
}

int traiter_echo(char* texte){
    int first_space = 0;
    for(int i = 0; texte[i] != '\0'; i++){
        if(texte[i] == ' '){
            first_space = i;
            break;
        }
    }
    if(first_space != 0){
        printf("%s\n", texte + first_space + 1);
    } 
    else {
        printf("\n");
    }
    return 1;
}

int calcul(char* str){
    char rpn[200] = "";
    lexer(str, rpn);
    if(strcmp(rpn, "") == 0){
        return 1;
    }
    float result = calc(rpn);
    return result;
}

int afficher_aide(char* args){
    printf("Aide: Ce programme supporte les commandes suivantes:\n");
    printf("  echo ou afficher <text>     : Affiche le texte fourni.\n");
    printf("  date            : Affiche la date actuelle.\n");
    printf("  version         : Affiche la version du programme.\n");
    printf("  <expression arithmétique> : Effectue le calcul.\n");
    printf("  quit ou quitter            : Quitte le programme.\n");

    return 1;
}

struct function list[] = {
    {"echo", traiter_echo},
    {"afficher", traiter_echo},
    {"date", afficher_date},
    {"version", afficher_version},
    {"quit", traiter_quit},
    {"quitter", traiter_quit},
    {"exit", traiter_quit},
    {"help", afficher_aide},
    {"<expression arithmétique>", calcul},
    {"aide", afficher_aide},
};


int main(){
    int continuer = 1; // Variable pour contrôler la boucle principale

    // Boucle principale qui lit et traite les commandes utilisateur
    while (continuer){
        printf("> "); // Affiche le prompt de commande

        char commande[1024];

        fgets(commande, sizeof(commande), stdin);

        commande[strcspn(commande, "\n")] = 0;
        int found = 0;
        int list_size = sizeof(list) / sizeof(list[0]);

        for(int i = 0; i < list_size; i++){
            int cmd_len = strlen(list[i].name);
            if(strncmp(list[i].name, commande, cmd_len) == 0){
                if(commande[cmd_len] == ' ' || commande[cmd_len] == '\0'){
                    
                    found = 1;
                    continuer = list[i].func(commande);
                    
                    break; 
                }
            }
            else if(!isalpha((unsigned char)commande[0])){
                found = 1;
                calcul(commande);
                break;
            }
        }
    }
    return 0;
}
