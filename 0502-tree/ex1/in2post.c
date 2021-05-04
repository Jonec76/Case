#include<stdio.h>
#include<ctype.h>
#include "in2post.h"

char stack[100];
int top = -1;

void push(char x)
{
    stack[++top] = x;
}

char pop()
{
    if(top == -1)
        return -1;
    else
        return stack[top--];
}

int priority(char x)
{
    if(x == '(')
        return 0;
    if(x == '+' || x == '-')
        return 1;
    if(x == '*' || x == '/')
        return 2;
    return 0;
}

void infix_postfix(char** value, char exp[])
{
    int i=0;
    char *e, x;
    // printf("Enter the expression : ");
    // scanf("%s",exp);
    // printf("\n");
    e = exp;
    
    while(*e != '\0')
    {
        if(isalnum(*e)){
            (*value)[i] = *e;
            i++;
        }
        else if(*e == '(')
            push(*e);
        else if(*e == ')')
        {
            while((x = pop()) != '('){
                (*value)[i] = x;
                i++;
            }
        }
        else
        {
            while(priority(stack[top]) >= priority(*e)){
                char c = pop();
                (*value)[i] = c;
                i++;
            }
            push(*e);
        }
        e++;
    }
    
    while(top != -1)
    {
        (*value)[i] = pop();
        i++;
    }
}