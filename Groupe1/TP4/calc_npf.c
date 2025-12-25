#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char operators[] = "+-*/";
const char separators[] = ",.";
const char parenthesis[] = "()";
char pile_v[20];
char pile_o[20];

int init_pile_v(){
    for(int j=0;j<20;j++){
        pile_v[j]='\0';
        pile_o[j]='\0';
    }
    return 0;
}
char* pile_v_ptr = pile_v;

int size_pile_v(){
    int p=0;
    while(pile_v[p] != '\0' && p < 20){
        p++;
    }
    return p;
}

void push_v(char c){
    int sz = size_pile_v();
    if(sz < 19){
        pile_v[sz] = c;
        pile_v[sz+1] = '\0';
    }
}

char pop_v(){
    int sz = size_pile_v();
    if(sz > 0){
        char temp = pile_v[sz-1];
        pile_v[sz-1] = '\0';
        return temp;
    }
    return '\0';
}

char look_v(){
    int sz = size_pile_v();
    if(sz > 0){
        return pile_v[sz-1];
    }
    return '\0';
}

void push_o(char c){
    int sz = size_pile_v();
    if(sz < 19){
        pile_o[sz] = c;
        pile_o[sz+1] = '\0';
    }
}

char pop_o(){
    int sz = size_pile_v();
    if(sz > 0){
        char temp = pile_o[sz-1];
        pile_o[sz-1] = '\0';
        return temp;
    }
    return '\0';
}

char look_o(){
    int sz = size_pile_o();
    if(sz > 0){
        return pile_o[sz-1];
    }
    return '\0';
}

int is_negative_number(char* str, int pos) {
    return (str[pos] == '-' && isdigit((unsigned char)str[pos + 1]) &&
            (pos == 0 || strchr(operators, str[pos - 1])));
}

int calc(char* args) {
    init_pile_v();
    float val = 0.0;
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

            if(strchr(separators, args[pos])){
                pile_v[outpos++] = args[pos++];
            }

            // Handle negative numbers
            if (is_negative_number(args, pos)) {
                pile_v[outpos++] = args[pos++];
            }

            while (pos < length) {

                char c = args[pos];
                pile_v[outpos++] = args[pos++];

            }

            pile_v[outpos++] = ' ';
            continue;
        }

        else if(strchr(operators, args[pos])){

            push_o(current);
            pos++;
        }
        else {
            printf("Argument non reconnu ou ordre incorrect: %c\n", args[pos]);
            return 1;
        }
    }

    int sz_o = size_pile_o();
    for(int i=0; i<sz_o; i++){
        char op = pop_o();
        int j = 0;
        // extract first operand
        char s1[10] = '\0';
        int s = size_pile_v();
        while(j < s && pile_v[j] != ' '){
            s1[j] = pile_v[j];
            j++;
        }
        s1[j] = '\0';
        // remove first operand from pile_v
        for(int k=j+1; k<s; k++){
            pile_v[k - (j + 1)] = pile_v[k];
        }
        pile_v[s - (j + 1)] = '\0';
        j = 0;
        // extract second operand
        char s2[10] = '\0';
        s = size_pile_v();
        while(j < s && pile_v[j] != ' '){
            s2[j] = pile_v[j];
            j++;
        }
        s2[j] = '\0';
        // remove second operand from pile_v
        for(int k=j+1; k<s; k++){
            pile_v[k - (j + 1)] = pile_v[k];
        }
        pile_v[s - (j + 1)] = '\0';
        float v1 = atof(s1);
        float v2 = atof(s2);
        float res = 0.0;
        switch(op){
            case '+':
                res = v2 + v1;
                break;
            case '-':
                res = v2 - v1;
                break;
            case '*':
                res = v2 * v1;
                break;
            case '/':
                if(v1 == 0){
                    printf("Erreur: Division par zéro\n");
                    return 1;
                }
                res = v2 / v1;
                break;
        }
        char res_str[10];
        sprintf(res_str, "%f", res);
        int i = 0;
        while(res_str[i] != '\0'){
            pile_v[outpos++] = res_str[i++];
        }
        pile_v[outpos++] = ' ';
    }
    pile_v[outpos] = '\0';
    printf("Output RPN: %s\n", pile_v);
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
        calc(args);
    }
    return 0;
}