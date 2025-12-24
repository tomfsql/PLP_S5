#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char operators[] = "+-*/";
const char separators[] = ",.";
char pile[20];

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
    else if(op == '*' || op == '/'){
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

void push(char op){
    int sz = size_pile();
    if(sz < 20){
        pile[sz] = op;
        pile[sz+1] = '\0';
    }
}

char pop(){
    int sz = size_pile();
    if(sz > 0){
        return pile[sz-1];
        pile[sz-1] = '\0';
    }
}

char peek(){
    int sz = size_pile();
    if(sz > 0){
        return pile[sz-1];
    }
    return '\0';
}

int lexer(char* args) {
    init_pile();
    char output[200] = "";
    int length = strlen(args);
    int pos = 0;
    int outpos = 0;
    while (pos < length) {
        char current = args[pos];
        int outpos = 0;
        if (isspace((unsigned char)args[pos])) {
            pos++;
            continue;
        }

        else if ((isdigit((unsigned char)args[pos]) || args[pos] == '-' || strchr(separators, args[pos]))) {

            int nbSep = 0;

            if(strchr(separators, args[pos])){
                nbSep++;
                output[outpos++] = args[pos++];
            }

            if (args[pos] == '-') {
                output[outpos++] = args[pos++];
            }

            while (pos < length) {

                char c = args[pos];
                if (strchr(separators, c)) {
                    if (nbSep > 1) break;
                    nbSep++;
                }
                output[outpos++] = args[pos++];

            }

            output[outpos++] = ' ';
            continue;
        }

        else if(strchr(operators, args[pos])){

            while(size_pile() > 0 && priorite_op(peek()) >= priorite_op(current)){

                output[pos++] = pop();
                output[pos++] = ' ';

            }
        }
        else {
            printf("Argument non reconnu ou ordre incorrect: %c\n", args[pos]);
            return 1;
        }
    }
    while(size_pile() > 0){

        output[pos++] = pop();
        output[pos++] = ' ';
    }

    if(outpos > 0 && output[outpos - 1] == ' '){

        outpos--;
    }
    output[pos] = '\0';
    printf("Output RPN: %s\n", output);
        return 0;
}

int main(){
    int keep = 1;
    char args[100];
    while(keep){

        printf("Entrez les arguments ( exit pour quitter): ");
        if (!fgets(args, sizeof args, stdin)) return 1;
        if (strncmp(args, "ex",2) == 0) return 0;
        size_t len = strlen(args);
        if (len && args[len-1] == '\n') args[len-1] = '\0';
        lexer(args);
    }
    return 0;
}