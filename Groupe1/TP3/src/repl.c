#include <stdio.h>
#include <string.h>
#include <time.h>
/**
 * Programme qui simule un interpréteur de commandes simple.
 * Il lit les commandes utilisateur et les traite en fonction de leur contenu.
 */

int version = 2.0;

struct function
{
    char* name;
    int (*func)(char*);
};


int afficher_version(char* args){
    printf("TP3 - REPL Simple - Version %d\n", version);
    return 0;
}

int afficher_date(char* args){
    time_t current_time = time(NULL);
    char date_string[20];
    strftime(date_string, 20, "%d-%m-%Y", localtime(&current_time));
    printf("La date actuelle est : %s\n", date_string);
    return 0;
}

int traiter_quit(char* args){
    printf("Arrêt...\n");
    return 0;
}

int traiter_echo(char* texte){
    printf("Commande saisie : %s\n", texte);
    for(int i = 5; i < strlen(texte); i++){
        putchar(texte[i]);
    }
    putchar('\n');
    return 0;
}

int afficher_aide(char* args){
    printf("Aide: Ce programme supporte les commandes suivantes:\n");
    printf("  echo <text> : Affiche le texte fourni.\n");
    printf("  date        : Affiche la date actuelle.\n");
    printf("  version     : Affiche la version du programme.\n");
    printf("  quit        : Quitte le programme.\n");
    return 0;
}

struct function list[] = {
    {"echo", traiter_echo},
    {"date", afficher_date},
    {"vers", afficher_version},
    {"quit", traiter_quit},
    {"help", afficher_aide},
};


int main(){
    int continuer = 1; // Variable pour contrôler la boucle principale

    // Boucle principale qui lit et traite les commandes utilisateur
    while (continuer)
    {
        printf("> "); // Affiche le prompt de commande

        // Buffer pour stocker la commande utilisateur
        char commande[1024];

        // Lit la commande utilisateur et la stocke dans le buffer
        fgets(commande, sizeof(commande), stdin);

        // Enlève le caractère de fin de ligne ajouté par fgets
        commande[strcspn(commande, "\n")] = 0;

        // Traite la commande en fonction de son contenu
        // 
        int found = 0;
        for(int i = 0; i < sizeof(list)/sizeof(list[0]); i++){
            if(strncmp(list[i].name, commande, 4) == 0){
                found=1;
                if(strcmp(list[i].name,"quit") == 0){
                    list[i].func("");
                    continuer = 0;
                    return 0;
                }
                else if(strcmp(list[i].name,"echo") != 0){
                    list[i].func("");
                    break;
                }
                else{
                    list[i].func(commande);
                }
            }
            continue;
        }
        if(!found){
            printf("Commande non reconnue. Essayez 'help' pour afficher l'aide, ou tapez 'quit' pour quitter.\n");
        }
        printf("\n"); // Saut de ligne après la sortie
    }
    return 0;
}
