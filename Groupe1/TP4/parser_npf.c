#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char operators[] = "+-*/";
const char separators[] = ",.";
char pile[20];

int init_pile(){
    for(int j=0;j<19;j++){
        pile[j]=' '; 
    }
    pile[19]='\0';
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
    while(pile[p]  != '\0'){
        p++;
    }
    if(p == 19 && pile[19] != '\0'){
        return 0;
    }
    else{
        return p;
    }
}


int lexer(char* args) {
    init_pile();
    char output[100] = "";
    char operateur;
    int length = strlen(args);
    int pos = 0;
    int foundop = 0;
    int foundN = 0;
    while (pos < length) {        
        int posp = 0;
        if ((isdigit((unsigned char)args[pos]) || args[pos] == '-' || strchr(separators, args[pos]))) {
            int nbSep = 0;
            foundN++;
            output[posp++] = args[pos++];
            if (args[pos] == '-') {
                output[posp++] = args[pos++];
            }
            while (pos < length) {
                char c = args[pos];
                if (strchr(separators, c)) {
                    if (nbSep >= 1) break; 
                    nbSep++;
                } 
                output[posp++] = args[pos++];
            }
            continue;
        }
        else if (isspace((unsigned char)args[pos])) {
            pos++;
            continue;
        }
        else if(strchr(operators, args[pos]) && foundN > 0){
            if(size_pile() ==  0 || priorite_op(pile[size_pile()-1]) < priorite_op(args[pos])){
                output[posp++] = args[pos++];
            }
            else{
                while(size_pile() > 0 || priorite_op(pile[size_pile()-1]) >= priorite_op(args[pos])){
                    char op = pile[size_pile()-1];
                    pile[size_pile()-1] = ' ';
                    output[posp++] = op;
                }
                foundop++;
                pile[size_pile()] = args[pos++];
                continue;
            }
        }
        else {
            printf("Argument non reconnu ou ordre incorrect: %c\n", args[pos]);
            return 1;
        }
    }
    while(size_pile() > 0){
        char op = pile[size_pile()-1];
        pile[size_pile()-1] = ' ';
        output[pos++] = op;
    }
    output[pos] = '\0';
    printf("Output RPN: %s\n", output);

    if (!foundop || foundN < 2) {
         printf("Trop peu d'arguments \n");
         return 1;
    }

    char opStr[2] = {operateur, '\0'};
    //char* tokens[] = { p1, opStr, p2, NULL };
    
    //parser(tokens);
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