#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Token_nombre,
    Token_plus,
    Token_moins,
    Token_divise,
    Token_multiplie,
    Token_fin,
    Token_erreur
    */

/*Fonctionnement principal du lexer :
prend la string en entrée, et la parcours caractère par caractère. 
Tant que le caractère est différent des signes mathématiques, les caractères sont ajoutés à un premier string.
Lorsqu'on arrive au signe mathématique, le signe est détecté et enregistré dans un token.
On continue le scanning en ajoutant les caractères à un deuxième string.
On convertit ensuite les 2 strings en type int à l'aide de la fonction string_to_int
    
*/

double string_to_int(char*);

/* global variables*/
int string_to_int_ok = 0; // =0 if conversion is OK, 1 else.
char number_string[100]; //numbers in string
int number1 = 0;
int number2 = 0;

TokenTab tokenizer(const char* expression){
    printf("lexer.c starting\n");
    TokenTab liste;
    liste.Tokentab_size = 0;
    int i = 0;
    int string_index = 0;
    int number_index = 0;

    while(expression[i] !=  '\0'){
        if(expression[i] == '*' || expression[i] == '+' || expression[i] == '-' || expression[i] == '/'){
            if((expression[i+1] >= '0' && expression[i+1] <= '9') || expression[i+1] == ' '){ //si le nombre après l'opérateur est bien un chiffre ou un espace
                number_string[string_index] = '\0';
                liste.Token_i[liste.Tokentab_size].nombre = string_to_int(number_string);
                printf("Number detected : %2.2f , token %d\n",liste.Token_i[liste.Tokentab_size].nombre,liste.Tokentab_size);
                liste.Token_i[liste.Tokentab_size].type = Token_nombre;
                liste.Tokentab_size++;
                for(int j=0 ; j<100 ; j++)
                    number_string[j] = '\0';
                string_index = 0;

                switch(expression[i]){
                    case '*' :
                        liste.Token_i[liste.Tokentab_size].type = Token_multiplie;
                        printf("Operand detected : * , token %d\n",liste.Tokentab_size);
                    break;
                    case '+' :
                        liste.Token_i[liste.Tokentab_size].type = Token_plus;
                        printf("Operand detected : + ,token %d\n",liste.Tokentab_size);
                    break;
                    case '-' :
                        liste.Token_i[liste.Tokentab_size].type = Token_moins;
                        printf("Operand detected : - , token %d\n",liste.Tokentab_size);

                    break;
                    case '/' :
                        liste.Token_i[liste.Tokentab_size].type = Token_divise;
                        printf("Operand detected : / , token %d\n",liste.Tokentab_size);
                    break;
                }
                liste.Tokentab_size++;
                number_index++;

        }
    }
        if ((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '.' || expression[i] == ','){
                    number_string[string_index] = expression[i];
                    string_index++;
                 }
        i++;
    }
    liste.Token_i[liste.Tokentab_size].nombre = string_to_int(number_string);
            printf("Number detected : %2.2f , token %d\n",liste.Token_i[liste.Tokentab_size].nombre,liste.Tokentab_size);
            liste.Token_i[liste.Tokentab_size].type = Token_nombre;
            liste.Tokentab_size++;
    return liste;
}

double string_to_int(char* str){

    char* endptr;
    printf("string_to_int : %s\n", str);
    double num = strtod(str, &endptr);
    printf("strtod : %.2f\n",num);

    if (endptr == str )
        printf("Chaîne invalide\n");
    return num;
}