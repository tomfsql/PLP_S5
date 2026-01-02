#ifndef PARSE_H
#define PARSE_H

extern const char operators[];
extern const char separators[];
extern const char parenthesis[];

int init_pile();
int priorite_op(char op);
int size_pile();
void push(char c);
char pop();
char look();
int is_negative_number(char* str, int pos);
char* lexer(char* args, char* output);

#endif