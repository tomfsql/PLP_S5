#ifndef CALC_H
#define CALC_H

int init_pile_v();
int size_pile_v();
void push_v(float f);
float pop_v();
float calculation(float a, float b, char op);
int is_negative_number(char* str, int pos);
int priorite_op(char op);
int calc(char* args);
int main();

#endif