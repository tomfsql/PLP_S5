#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "parseur.h"
#include "lexer.h"
#include "evaluation.h"

int parser(char** token ){
    struct expression expr;
    float temp1, temp2;
    for(int i = 0; i < strlen(token[0]); i++){
        if((token[0][i]) == ','){
            token[0][i] = '.';
        }
    }
    for(int i = 0; i < strlen(token[2]); i++){
        if((token[2][i]) == ','){
            token[2][i] = '.';
        }
    }
    expr.operand1 = atof(token[0]);
    expr.operand = *(token[1]);
    expr.operand2 = atof(token[2]);
    evaluate(expr);
    return 0;
}