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

int afficher_aide(char* args){
    printf("Aide: Ce programme supporte les commandes suivantes:\n");
    printf("  echo <text>     : Affiche le texte fourni.\n");
    printf("  afficher <text> : Affiche le texte fourni.\n");
    printf("  date            : Affiche la date actuelle.\n");
    printf("  version         : Affiche la version du programme.\n");
    printf("  quit            : Quitte le programme.\n");
    printf("  quitter         : Quitte le programme.\n");
    return 1;
}

struct function list[] = {
    {"echo", traiter_echo},
    {"afficher", traiter_echo},
    {"date", afficher_date},
    {"version", afficher_version},
    {"quit", traiter_quit},
    {"quitter", traiter_quit},
    {"help", afficher_aide},
    {"aide", afficher_aide},
};


int main(){
    int continuer = 1; // Variable pour contrôler la boucle principale

    // Boucle principale qui lit et traite les commandes utilisateur
    while (continuer){
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
        int list_size = sizeof(list) / sizeof(list[0]);

        for(int i = 0; i < list_size; i++){
            
            // 1. Get the length of the specific command we are checking (e.g., "echo" is 4, "version" is 7)
            int cmd_len = strlen(list[i].name);

            // 2. Check if the input starts with this command
            if(strncmp(list[i].name, commande, cmd_len) == 0){
                
                // 3. CRITICAL: Check if the next char is a space or end-of-line
                // This ensures "dates" doesn't trigger "date"
                if(commande[cmd_len] == ' ' || commande[cmd_len] == '\0'){
                    
                    found = 1;
                    
                    // 4. Execute generic. 
                    // We pass the FULL command string (e.g., "echo hello").
                    // The function itself decides what to do with it.
                    continuer = list[i].func(commande);
                    
                    break; // We found the command, stop looping
                }
            }
        }
    }
    return 0;
}
