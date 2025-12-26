#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

const char operators[] = "+-*/";
const char separators[] = ",.";
const char parenthesis[] = "()";
float pile_v[20];
int top_v = 0;
char pile_o[20];
int top_o = 0;

int init_pile_v(){
    for(int j=0;j<20;j++){
        pile_v[j]=0.0f;
        pile_o[j]='\0';
    }
    return 0;
}
float* pile_v_ptr = pile_v;

int size_pile_v(){
    int p=0;
    while(pile_v[p] != 0.0f && p < 20){
        p++;
    }
    return p;
}

int size_pile_o(){
    int p=0;
    while(pile_o[p] != '\0' && p < 20){
        p++;
    }
    return p;
}

void push_v(float f){
    if(top_v < 50) pile_v[top_v++] = f;
}

float pop_v(){
    if(top_v > 0) return pile_v[--top_v];
    return 0.0f;
}

void push_o(char c){
    if(top_o < 50) pile_o[top_o++] = c;
}

char pop_o(){
    if(top_o > 0) return pile_o[--top_o];
    return '\0';
}

char look_o(){
    if(top_o > 0) return pile_o[top_o-1];
    return '\0';
}

int is_negative_number(char* str, int pos) {
    return (str[pos] == '-' && isdigit((unsigned char)str[pos + 1]) &&
            (pos == 0 || strchr(operators, str[pos - 1])));
}

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

float calculation(float a, float b, char op){
    float res = 0.0f;
    switch(op){
        case '+':
            res = a + b;
            break;
        case '-':
            res = a - b;
            break;
        case '*':
            res = a * b;
            break;
        case '/':
            if(b == 0){
                printf("Erreur: Division par zéro\n");
                return 0.0f;
            }
            res = a / b;
            break;
    }
    return res;
}

void apply_stack_op() {
    char op = pop_o();
    float val2 = pop_v();
    float val1 = pop_v();
    float res = calculation(val1, val2, op);
    push_v(res);
}

int calc(char* args) {
    init_pile_v();
    float val = 0.0;
    int length = strlen(args);
    int pos = 0;
    while (pos < length) {
        int outpos = 0;
        char current = args[pos];
        if (isspace((unsigned char)args[pos])) {
            pos++;
            continue;
        }

        else if (isdigit((unsigned char)args[pos]) ||  is_negative_number(args, pos)) {

            char temp_float_str[20] = "";
            if(strchr(separators, args[pos])){
                temp_float_str[outpos++] = args[pos++];
            }

            // Handle negative numbers
            if (is_negative_number(args, pos)) {
                temp_float_str[outpos++] = args[pos++];
            }

            while ( pos < length && (strchr(separators, args[pos]) || isdigit((unsigned char)args[pos]))) {

                char c = args[pos];
                temp_float_str[outpos++] = args[pos++];

            }

            temp_float_str[outpos] = '\0';
            // Convert the string to a float and push it onto the stack
            float f = atof(temp_float_str);
            push_v(f);
        }

        else if(strchr(operators, args[pos])){

            while(top_o > 0 && look_o() != '(' && priority(look_o()) >= priority(current)){
                apply_stack_op();
            }
            
            push_o(current);
            pos++;
        }

        else if(strchr("(", args[pos])) {
            push_o(current);
            pos++;
        }

        else if(strchr(")", args[pos])) {
            while(look_o() != '('){
                char op = pop_o();
                float op1 = pop_v();
                float op2 = pop_v();
                float res = calculation(op2, op1, op);
                push_v(res);
            }
            pop_o();
            pos++;
        }

        else {
            printf("Argument non reconnu ou ordre incorrect: %c\n", args[pos]);
            return 1;
        }
    }

    while(top_o > 0){
        apply_stack_op();
    }

    float result = pop_v();
    printf("Result: %.2f\n", result);
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