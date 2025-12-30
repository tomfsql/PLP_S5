#ifndef VARIABLES_H
#define VARIABLES_H

//enum des types de variables possibles : int, réel, string et undefined
typedef enum {
    TYPE_INT,
    TYPE_REAL,
    TYPE_STRING,
    TYPE_UNDEFINED
} VarType;

// struct d'une variable
typedef struct {
    char name[64]; 
    VarType type;
    union {
        int i_val;
        double d_val;
        char s_val[128];
    } value;
} Variable;

// Table des variables
#define MAX_VARS 100
extern Variable variable_array[MAX_VARS];
extern int nb_vars;

// Fonctions de gestion, get and set
int find_variable(char* name);
void set_variable(char* name, char* value_str);
void get_variable(char* name);

#endif