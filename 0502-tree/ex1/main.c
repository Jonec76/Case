#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "in2post.h"
struct et
{
	char value;
	struct et* left, *right;
};

// A utility function to check if 'c'
// is an operator
bool isOperator(char c)
{
	if (c == '+' || c == '-' ||
			c == '*' || c == '/')
		return true;
	return false;
}

// Utility function to do inorder traversal
void inorder(struct et*t)
{
	if(t)
	{
		inorder(t->left);
		printf("%c ", t->value);
		inorder(t->right);
	}
}

void postorder(struct et*t)
{
	if(t)
	{
		postorder(t->left);
		postorder(t->right);
		printf("%c ", t->value);
	}
}

void preorder(struct et*t)
{
	if(t)
	{
		printf("%c ", t->value);
		preorder(t->left);
		preorder(t->right);
	}
}

// A utility function to create a new node
struct et* newNode(char v)
{
	struct et* temp = (struct et*) malloc(sizeof(struct et));

	temp->left = temp->right = NULL;
	temp->value = v;
	return temp;
};

// Returns root of constructed tree for given
// postfix expression
struct et* constructTree(char postfix[], int len)
{
    struct et** st = (struct et**)malloc(len * sizeof(struct et*));
    int stack_top = -1;
	struct et*t, *t1, *t2;

	// Traverse through every character of
	// input expression
	for (int i=0; i<len; i++)
	{
		// If operand, simply push into stack
		if (!isOperator(postfix[i]))
		{
			t = newNode(postfix[i]);
            stack_top++;
			st[stack_top] = t;
		}
		else // operator
		{
			t = newNode(postfix[i]);

			// Pop two top nodes
			t1 = st[stack_top]; // Store top
            stack_top--;
			t2 = st[stack_top];
            stack_top--;

			// make them children
			t->right = t1;
			t->left = t2;

            stack_top++;
			st[stack_top] = t;
		}
	}

	// only element will be root of expression
	// tree
	t = st[stack_top];
    stack_top--;

	return t;
}

// Driver program to test above
int main()
{
	char exp[256];

	printf("Enter expresion: ");
	scanf("%s", exp);
	int len = strlen(exp);
    char* postfix = (char*)malloc(len *sizeof(char));
    infix_postfix(&postfix, exp);

	struct et* r = constructTree(postfix, strlen(postfix));
	printf("inorder expression :\n ");
	inorder(r);
    printf("\n");

	printf("preorder expression :\n ");
	preorder(r);
    printf("\n");

	printf("postorder expression :\n ");
	postorder(r);
    printf("\n");

	return 0;
}
