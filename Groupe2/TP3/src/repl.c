#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 * Programme qui simule un interpréteur de commandes simple.
 * Il lit les commandes utilisateur et les traite en fonction de leur contenu.
 */

//====================== constantes ====================
// Program version :
#define CLI_MAIN_VERS 1
#define CLI_LOWER_VERS 5
//program version is CLI_MAIN_VERS.CLI_LOWER_VERS

//====================== variables globales ====================

typedef struct {
    char commande[50]; //nom
    int (*p_fonction)(char*); //pointeur vers la fonction
    char lang[3]; //en pour commande anglaise; fr pour cmd française, 2 char + \0  = 3
}struct_commandes;
char current_lang[3] = "en"; //en by default.Si une commande est entrée et n'est pas spécifique à
// la langue (ex. echo ou date), la langue de la dernière commande est utilisée (essayer avec date, aide, date)

//====================== fonctions ====================

int afficher_version(char*);
int afficher_aide(char*);
int traiter_echo(char*);
int traiter_quit(char*);
int traiter_date(char*);


int main()
{
    int continuer = 1; // Variable pour contrôler la boucle principale

    struct_commandes commandes_tab[]={
        {"echo",traiter_echo,"en"},
        {"quit", traiter_quit,"en"},
        {"version", afficher_version,"en"},
        {"help", afficher_aide,"en"},
        {"date",traiter_date,"en"},
        //ajout des commandes en français
        {"aide", afficher_aide,"fr"},
        {"quitter", traiter_quit,"fr"},
    };


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
        // parcours et compare le tableau avec les commandes dispo
        int nb_commandes = sizeof(commandes_tab) / sizeof(struct_commandes);
        int commande_trouvee = 0; // 0 si la commande n'a pas été trouvée dans le tableau, 1 si elle l'est
        for(int i=0 ; i < nb_commandes ; i++){
            size_t command_size = strlen(commandes_tab[i].commande);
            if(strncmp(commande, commandes_tab[i].commande, command_size) == 0 &&
               (commande[command_size] == '\0' || commande[command_size] == ' ')){
                strcpy(current_lang, commandes_tab[i].lang);
                commandes_tab[i].p_fonction(commande);
                commande_trouvee = 1; //commande trouvée dans le tableau
                break;
            }
        }
        if(commande_trouvee == 0){
            // Affiche un message d'erreur si la commande est inconnue
            printf("Commande non reconnue. Essayez 'echo <text>' pour afficher du texte, help pour afficher l'aide, ou tapez 'quit' pour quitter.\n");
        }
    }

    return 0;
}


int afficher_version(char*){
    printf("Version CLI : %d.%d\n", CLI_MAIN_VERS, CLI_LOWER_VERS);
    return 0;
}


int afficher_aide(char*){
    if(strcmp(current_lang,"fr") == 0)
    printf(
    "Commandes disponibles :\n"
    "aide         : afficher l'aide\n"
    "version      : afficher la version du programme\n"
    "date         : afficher la date système\n"
    "echo <texte> : afficher le texte entré\n"
    "quitter      : quitter le programme\n"
    );
    if(strcmp(current_lang, "en") == 0)
    printf(
    "Available commands:\n"
    "help       : display help\n"
    "version    : display program version\n"
    "date       : display system date\n"
    "echo <text>: display entered text\n"
    "quit       : exit the program\n"
    );
    return 0;
}

int traiter_echo(char* commande){
    // Traite la commande "echo" pour afficher du texte
    printf("Echo: ");

    // Imprime la chaîne
    for (int i = 5; commande[i] != '\0'; i++)
    {
        printf("%c", commande[i]);
    }
    printf("\n"); // Saut de ligne après la sortie
    return 0;
}

int traiter_quit(char*){
    if(strcmp(current_lang, "en") == 0) 
            printf("Stopping...\n");
        if(strcmp(current_lang, "fr") == 0) 
            printf("Arrêt...\n");
        return 0;
}

int traiter_date(char*){
    // traite la commande "date" pour afficher la date
    time_t now = time(NULL);         // Get current time
    struct tm *t = localtime(&now);  // Convert to local time structure
    
    if(strcmp(current_lang,"en")==0){
        printf("Current date : %d/%d/%d , %d:%d:%d\n", t->tm_year + 1900 , // Add 1900 to get the actual year
        t->tm_mon + 1,    // Months are numbered from 0 to 11, so add 1 to match real month numbers (1-12)
        t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
    }else if(strcmp(current_lang,"fr")==0){
        printf("Date actuelle : %d/%d/%d , %d:%d:%d\n", t->tm_year + 1900 , // Add 1900 to get the actual year
        t->tm_mon + 1,    // Months are numbered from 0 to 11, so add 1 to match real month numbers (1-12)
        t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
    }
    return 0;
}