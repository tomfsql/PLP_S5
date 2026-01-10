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
    while (str < equals && isspace((unsigned char)*str)) {
        str++;
    }
    int length = equals - str;
    while (length > 0 && isspace((unsigned char)str[length - 1])) {
        length--;
    }
    char* name = malloc(length+1);
    strncpy(name, str, length);
    name[length] = '\0';
    return name;
}

char* extract_variable_value(char* str){
    char* equals = strchr(str, '=');
    if(equals == NULL) return NULL;
    char* start = equals+1;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        start++;
    }
    int length = strlen(start);
    while (length > 0 && isspace((unsigned char)start[length - 1])) {
        length--;
    }
    char* value = malloc(length+1);
    if(value){
        strncpy(value, start, length);
        value[length] = '\0';
    }
    return value;
}

int traiter_affectation(char* str){
    char* var_value = extract_variable_value(str);
    char* var_name = extract_variable_name(str);
    StoredValue val;
    if(var_name == NULL){
        printf("Erreur lors de l'affectation.\n");
        free(var_value);
        return -1;
    }
    val.name = var_name;
    if(is_numeric(var_value)){
        if(strchr(var_value, '.') != NULL){
            float f_value = atof(var_value);
            val.type = TYPE_FLOAT;
            val.value.f = f_value;
        } else {
            int i_value = atoi(var_value);
            val.type = TYPE_INT;
            val.value.i = i_value;
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
            printf("Aucun espace mémoire disponible pour stocker la variable.\n");
            free(val.name);
            return -1;
        }
        return 1;
    }
    return 1;
}

void sauvegarder_variables(){
    const char* filename = "variables.txt";
    FILE *file = fopen(filename,"w");

    if(file == NULL){
        printf("Impossible to open file %s for writing.\n", filename);
        return;
    }

    int count=0;
    for (int i = 0; i < 100; i++) {
        if (variables[i].name != NULL) {
            switch (variables[i].type) {
                case TYPE_INT:
                    fprintf(file, "%s=%d\n", variables[i].name, variables[i].value.i);
                    break;
                case TYPE_FLOAT:
                    fprintf(file, "%s=%.4f\n", variables[i].name, variables[i].value.f);
                    break;
                case TYPE_STRING:
                    fprintf(file, "%s=%s\n", variables[i].name, variables[i].value.str);
                    break;
            }
            count++;
        }
    }
    fclose(file);
    printf("%d variables sauvegardées dans '%s'.\n", count, filename);
}

void charger_variables() {
    const char* filename = "variables.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Pas de variables trouvées (fichier '%s' manquant).\n", filename);
        return;
    }

    char line[256];
    int count = 0;

    printf("Chargement des variables depuis '%s'...\n", filename);
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        if (strlen(line) == 0) continue;
        if (traiter_affectation(line) == 1) {
            count++;
        }
    }

    fclose(file);
    if(count > 0){
        printf("%d variables récupérées.\n", count);
    }
    else{
        printf("Pas de variables récupérées.\n");
    }
}

int traiter_affichage(char* str){
    int length = 0;
    while(!isspace(str[length]) && str[length] != '\0'){
        length++;
    }

    char* var_name = malloc(length+1);
    strncpy(var_name, str, length);
    var_name[length] = '\0';
    int pos = lookup_variable(var_name);
    if(pos < 0){
        printf("Variable non-trouvée ou indéfinie, ou commande indéfinie. \n");
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
    return 1;
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
    sauvegarder_variables();
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

void append_string(char* dest, size_t* idx, const char* src) {
    int i = 0;
    while(src[i] != '\0') {
        dest[*idx] = src[i];
        (*idx)++;
        i++;
    }
    dest[*idx] = '\0'; 
}

int parse_lambda(char* str, char* arg_name, float arg_val){
    size_t offset_w = 0;
    size_t offset_r = 0;
    char* new_expr = calloc(1024, sizeof(char));
    while(offset_r < strlen(str)){
        if(isalpha(str[offset_r])){
            int var_offset = offset_r;
            while(isalnum(str[offset_r])){
                offset_r++;
            }
            int len = offset_r - var_offset;
            char* token = strndup(str+var_offset, len);

            char value_text[64];
            if (strcmp(token, arg_name) == 0) {
                snprintf(value_text, 64, "%f", arg_val);
                append_string(new_expr, &offset_w, value_text);
            }
            else {
                int pos = lookup_variable(token);
                if (pos < 0){
                    printf("Erreur: La variable '%s' est non-définie.\n", token);
                    free(token);
                    free(new_expr);
                    return 2;
                }
                StoredValue existing = variables[pos];
                if (existing.type == TYPE_INT) {
                    snprintf(value_text, 64, "%d", existing.value.i);
                    append_string(new_expr, &offset_w, value_text);
                } else if (existing.type == TYPE_FLOAT) {
                    snprintf(value_text, 64, "%f", existing.value.f);
                    append_string(new_expr, &offset_w, value_text);
                }
            }
            free(token);
        }
        else{
            new_expr[offset_w] = str[offset_r];
            offset_r++;
            offset_w++;
        }
    }
    new_expr[offset_w]='\0';
    calcul(new_expr);
    return 1;
}


int traiter_lambda(char* str){
    char* dot = strchr(str, '.');
    char* end = NULL;
    int depth = 0;
    int found_start = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') {
            depth++;
            found_start = 1;
        }
        else if (str[i] == ')') {
            depth--;
        }

        if (found_start && depth == 0) {
            end = &str[i];
            break;
        }
    }
    if (dot == NULL || end == NULL || end < dot){
        printf("Mauvaise syntaxe ou paramètre.\n");
        return 1;
    }
    char* var_start = strchr(str, ' ');
    if(var_start == NULL || var_start > dot) {
        var_start = str + 7;
    } else {
        while(var_start < dot && isspace((unsigned char)*var_start)) {
            var_start++;
        }
    }
    int var_len = dot - var_start;
    // trimming the variable name
    while (var_len > 0 && isspace((unsigned char)var_start[var_len - 1])) {
        var_len--;
    }
    char* var_name = malloc(var_len + 1);
    strncpy(var_name, var_start, var_len);
    var_name[var_len] = '\0';
    char* val = end+1;
    while(*val != '\0' && isspace((unsigned char)*val)){
        val++;
    }

    float f_arg = 0.0;
    int found_arg =0;
    if (*val == '\0') {
        int pos = lookup_variable(var_name);
        if (pos >= 0) {
            StoredValue v = variables[pos];
            if (v.type == TYPE_FLOAT) f_arg = v.value.f;
            else if (v.type == TYPE_INT) f_arg = (float)v.value.i;
            found_arg = 1;
        } else {
            printf("Error: No argument provided and global variable '%s' is undefined.\n", var_name);
            free(var_name);
            return 1;
        }
    }
    else {
        if (isdigit(val[0]) || (val[0] == '-' && isdigit(val[1]))) {
            f_arg = atof(val);
            found_arg = 1;
        }
        else {
            int pos = lookup_variable(val);
            if (pos >= 0) {
                StoredValue v = variables[pos];
                if (v.type == TYPE_FLOAT) f_arg = v.value.f;
                else if (v.type == TYPE_INT) f_arg = (float)v.value.i;
                found_arg = 1;
            } else {
                printf("Erreur: l'argument '%s' est indéfini.\n", val);
                free(var_name);
                return 1;
            }
        }
    }
    if (found_arg) {
        int body_len = end - (dot + 1);
        char* expr = malloc(body_len + 1);
        strncpy(expr, dot + 1, body_len);
        expr[body_len] = '\0';

        parse_lambda(expr, var_name, f_arg);
        free(expr);
    }
    free(var_name);
    return 1;
}

int afficher_aide(char* args){
    printf("Aide: Ce programme supporte les commandes suivantes:\n");
    printf("  echo ou afficher <text>     : Affiche le texte fourni.\n");
    printf("  date            : Affiche la date actuelle.\n");
    printf("  version         : Affiche la version du programme.\n");
    printf("  <expression arithmétique> : Effectue le calcul.\n");
    printf("  <variable> = <valeur>     : Déclare ou modifie une variable.\n");
    printf("  <variable>     : Affiche la valeur d'une variable si existante.\n");
    printf("(lambda <variable>. <expression arithmétique ) <optional variable<     : Evalue l'expression fournie.\n");
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
    charger_variables();


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
        }
        if(!found){
            if(strncmp("(lambda", commande, 7) == 0){

                found = 1;
                traiter_lambda(commande);
            }
            else if(strchr(commande, '=') != NULL){

                found = 1;
                traiter_affectation(commande);
            }
            else if(!isalpha((unsigned char)commande[0])){
                found=1;
                calcul(commande);
            }
            else{

                found = 1;
                traiter_affichage(commande);
            }
        }
    }
    return 0;
}
