#ifndef IN2POST_H
#define IN2POST_H
void push(char x);
char pop();
int priority(char x);
void infix_postfix(char** value, char exp[]);
#endif