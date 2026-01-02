#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "parse.h"
char pile[20];

const char operators[] = "+-*/";
const char separators[] = ",.";
const char parenthesis[] = "()";

int init_pile(){
    for(int j=0;j<20;j++){
        pile[j]='\0';
    }
    return 0;
}

int priorite_op(char op){
    if(op == '+' || op == '-'){
        return 1;
    }
    else if(op == '*' || op == '/' || op == 'x'){
        return 2;
    }
    else{
        return 0;
    }
}
char* pile_ptr = pile;

int size_pile(){
    int p=0;
    while(pile[p] != '\0' && p < 20){
        p++;
    }
    return p;
}

void push(char c){
    int sz = size_pile();
    if(sz < 19){
        pile[sz] = c;
        pile[sz+1] = '\0';
    }
}

char pop(){
    int sz = size_pile();
    if(sz > 0){
        char temp = pile[sz-1];
        pile[sz-1] = '\0';
        return temp;
    }
    return '\0';
}

char look(){
    int sz = size_pile();
    if(sz > 0){
        return pile[sz-1];
    }
    return '\0';
}

char* lexer(char* args, char* output) {
    init_pile();
    int length = strlen(args);
    int pos = 0;
    int outpos = 0;
    while (pos < length) {
        char current = args[pos];
        if (isspace((unsigned char)args[pos])) {
            pos++;
            continue;
        }

        else if (isdigit((unsigned char)args[pos]) ||  is_negative_number(args, pos)) {

            int nbSep = 0;
            int neg = 0;

            if(strchr(separators, args[pos]) && nbSep == 0){
                nbSep = 1;
                output[outpos++] = args[pos++];
            }

            // Invalid separator usage
            if(strchr(separators, args[pos]) && nbSep == 1){
                printf("Argument non reconnu ou ordre incorrect: %c\n", args[pos]);
                return "1";
            }

            // Handle negative numbers
            if (is_negative_number(args, pos) && neg == 0) {
                neg = 1;
                output[outpos++] = args[pos++];
            }

            // Invalid '-' usage
            if (args[pos] == '-' && (!isdigit((unsigned char)args[pos + 1]) || neg == 1)) {
                printf("Argument non reconnu ou ordre incorrect: %c\n", args[pos]);
                return "1";
            }

            while (pos < length) {

                char c = args[pos];

                // Case of new separator
                if (strchr(separators, c)) {
                    if (nbSep > 1) break;
                    nbSep++;
                }

                // Too much separators or invalid character
                if(!isdigit((unsigned char)c) && !strchr(separators, c)) {
                    break;
                }
                output[outpos++] = args[pos++];

            }

            output[outpos++] = ' ';
            continue;
        }

        else if(current == '('){
            push(current);
            pos++;
        }
        else if(current == ')'){
            while(size_pile() > 0 && look() != '('){

                output[outpos++] = pop();
                output[outpos++] = ' ';

            }
            if(size_pile() == 0){
                printf("Parenthèse ouvrante manquante\n");
                return "1";
            }
            pop();
            pos++;
        }

        else if(strchr(operators, args[pos])){

            while(size_pile() > 0 && priorite_op(look()) >= priorite_op(current)){

                output[outpos++] = pop();
                output[outpos++] = ' ';

            }
            push(current);
            pos++;
        }
        else {
            printf("Argument non reconnu ou ordre incorrect: %c\n", args[pos]);
            return "1";
        }
    }
    while(size_pile() > 0){

        output[outpos++] = pop();
        output[outpos++] = ' ';
    }

    if(outpos > 0 && output[outpos - 1] == ' '){

        outpos--;
    }
    output[outpos] = '\0';
    return output;
}

/* int main(){
    int keep = 1;
    char args[100];
    while(keep){

        printf("Entrez les arguments ( exit pour quitter): ");
        if (!fgets(args, sizeof args, stdin)) return 1;
        if (strncmp(args, "ex",2) == 0) return 0;
        size_t len = strlen(args);
        if (len && args[len-1] == '\n') args[len-1] = '\0';
        char output[200];
        lexer(args, output);
    }
    return 0;
} */