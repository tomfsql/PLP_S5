#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "parse.h"
#include "calc.h"
#include <stdlib.h>
/**
 * Programme qui simule un interpréteur de commandes simple.
 * Il lit les commandes utilisateur et les traite en fonction de leur contenu.
 */

int version = 4.0;

struct function
{
    char* name;
    int (*func)(char*);
};

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int i;
        float f;
        char *str;
    } value;
    char* name;
} StoredValue;

StoredValue variables[100] = {0};

int is_numeric(const char *str){
    if (str == NULL || *str == '\0') return 0;
    int offset = 0;
    if(is_negative_number(str,0)) offset++;
    int foundsep = 0;
    while(str[offset] != '\0'){
        if(strchr(separators,str[offset])){
            if(foundsep) return 0;
            foundsep++;
        }
        else if (!isdigit(str[offset])){
            return 0;
        }
        offset++;
    }
    printf("Numerical data \n");
    return 1;
}

int nb_declared_variables(){
    int c = 0;
    while (c < 100){
        if(variables[c].name == NULL){
            break;
        }
        c++;
    }
    return c;
}

int lookup_variable(char* name){
    int c = 0;
    while (c < 100){
        if(variables[c].name == NULL){
            break;
        }
        if(strcmp(variables[c].name, name) == 0){
            return c;
        }
        c++;
    }
    return -1;
}

char* extract_variable_name(char* str){
    char* equals = strchr(str, '=');
    if(equals == NULL)return NULL;

    int length = equals - str;
    char* name = malloc(length+1);
    strncpy(name, str, length);
    name[length] = '\0';
    return name;
}

char* extract_variable_value(char* str){
    char* equals = strchr(str, '=');
    if(equals != NULL){
        return strdup(equals +1);
    }
    else{
        return strdup("");
    }
}

int traiter_affectation(char* str){
    char* var_value = extract_variable_value(str);
    char* var_name = extract_variable_name(str);
    printf("Variable name : %s.\n", var_name);
    printf("Variable value : %s.\n", var_value);
    StoredValue val;
    if(var_name == NULL){
        printf("Error in name assignment.\n");
        free(var_value);
        return -1;
    }
    val.name = var_name;
    if(is_numeric(var_value)){
        if(strchr(var_value, '.') != NULL){
            float f_value = atof(var_value);
            val.type = TYPE_FLOAT;
            val.value.f = f_value;
            printf("Value of %s is %f \n", var_name, f_value);
        } else {
            int i_value = atoi(var_value);
            val.type = TYPE_INT;
            val.value.i = i_value;
            printf("Value of %s is %d \n", var_name, i_value);
        }
    } else {
        val.type = TYPE_STRING;
        val.value.str = var_value;
    }

    if(val.type != TYPE_STRING) free(var_value);
    int pos = lookup_variable(var_name);
    if(pos != -1){
        if(variables[pos].type == TYPE_STRING) free(variables[pos].value.str);
        if (val.type == variables[pos].type){
            variables[pos] = val;
            return 1;
        } else {
            printf("Erreur: Type incompatible pour la variable %s\n", var_name);
            free(val.name);
            if(val.type == TYPE_STRING) free(val.value.str);
            return -1;
        }
    } else {
        int nb_vars = nb_declared_variables();
        if(nb_vars < 100){ 
            variables[nb_vars] = val;
        }
        else{
            printf("No more available space for variables.\n");
            free(val.name);
            return -1;
        }
        return 1;
    }
    return 1;
}

int traiter_affichage(char* str){
    int length = 0;
    while(!isspace(str[length]) && str[length] != '\0'){
        length++;
    }

    char* var_name = malloc(length+1);
    strncpy(var_name, str, length);
    var_name[length] = '\0';
    printf("variable name : %s.\n", var_name);

    int pos = lookup_variable(var_name);
    if(pos < 0){
        printf("Variable not found or not defined. \n");
        free(var_name);
        return 1;
    }
    free(var_name);
    StoredValue found_var = variables[pos];
    switch (found_var.type)
    {
    case TYPE_FLOAT:
        float fvalue = found_var.value.f;
        printf(" %.2f \n", fvalue);
        break;
    case TYPE_INT:
        int ivalue = found_var.value.i;
        printf(" %d \n", ivalue);
        break;
    case TYPE_STRING:
        char* svalue = found_var.value.str;
        printf(" %s \n", svalue);
        break;
    default:
        break;
    }
}

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
    printf("  <variable> = <valeur>     : Déclare ou modifie une variable.\n");
    printf("  <variable>     : Affiche la valeur d'une variable si existante.\n");
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
    {"aide", afficher_aide},
};


int main(){

    for(int i = 0; i < 100; i++){
        variables[i].name = NULL;
    }

    int nb_variables = 0;

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
            else if(strchr(commande, '=') != NULL){

                found = 1;
                traiter_affectation(commande);
                break;
            }
            else if(strchr(commande, '=') == NULL && strncmp(list[i].name, commande, cmd_len) != 0){

                found = 1;
                traiter_affichage(commande);
                break;
            }
        }
    }
    return 0;
}
