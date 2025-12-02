#ifndef PARSEUR_H   
#define PARSEUR_H

int parser(char** token );

typedef struct expression
{
    double operand1;
    char operand;
    double operand2;
} MExpression;

#endif