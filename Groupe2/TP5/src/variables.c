/* ========= EXPLANATIONS ========= */
/*
Contient les 3 fonctions principales pour la gestion des variables :
- find_variable : cherche une variable par son nom et retourne son index dans la table des symboles
- set_variable : crée ou met à jour une variable avec le nom et la valeur donnés
- get_variable : récupère et affiche la valeur d'une variable par son nom
*/

/* ========= INCLUDES ========= */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "variables.h"

/* ========= MACROS ========= */

/* ========= GLOBAL VARIABLES ========= */
Variable variable_array[100];
int nb_vars = 0;

/* ========= FUNCTIONS ========= */

// Cherche l'index d'une variable par son nom
int find_variable(char* name) {
    for (int i = 0; i < nb_vars; i++) {
        if (strcmp(variable_array[i].name, name) == 0) return i;
    }
    return -1;
}

// Détecte le type d'une chaîne (ex: "12" -> INT, "12.3" -> REAL)
VarType detect_type(char* s) {
    if (s[0] == '"') return TYPE_STRING;
    if (strchr(s, '.') || strchr(s, ',')) return TYPE_REAL;
    return TYPE_INT;
}

void set_variable(char* name, char* value_raw) {
    int idx = find_variable(name);
    VarType new_type = detect_type(value_raw);

    // Vérification du changement de type interdit
    if (idx != -1 && variable_array[idx].type != new_type) {
        printf("Erreur : changement de type non autorisé pour la variable %s\n", name);
        return;
    }

    // Si nouvelle variable, on l'ajoute
    if (idx == -1) {
        idx = nb_vars++;
        strcpy(variable_array[idx].name, name);
        variable_array[idx].type = new_type;
    }

    // Stockage de la valeur selon le type
    if (new_type == TYPE_STRING) {
        // On enlève les guillemets
        sscanf(value_raw, "\"%[^\"]\"", variable_array[idx].value.s_val);
        printf("Variable %s définie (chaîne)\n", name);
    } else if (new_type == TYPE_REAL) {
        variable_array[idx].value.d_val = atof(value_raw);
        printf("Variable %s définie avec %.2f (réel)\n", name, variable_array[idx].value.d_val);
    } else {
        variable_array[idx].value.i_val = atoi(value_raw);
        printf("Variable %s définie avec %d (entier)\n", name, variable_array[idx].value.i_val);
    }
}

void get_variable(char* name) {
    int idx = find_variable(name);
    if (idx == -1) {
        printf("Erreur : la variable %s n'est pas définie\n", name);
        return;
    }
    if (variable_array[idx].type == TYPE_INT) printf("%d\n", variable_array[idx].value.i_val);
    else if (variable_array[idx].type == TYPE_REAL) printf("%.2f\n", variable_array[idx].value.d_val);
    else printf("%s\n", variable_array[idx].value.s_val);
}