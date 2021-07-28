#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 256

typedef union
{
    float fData;
    char  cData;
} Item;

typedef struct
{
    Item values[MAX_SIZE];
    int top;
} Stack;

Stack * initialize()
{
    Stack *s = malloc(sizeof(Stack));
    s->top = 0;
    return s;
}

int isEmpty(Stack *s)
{
    return (s->top == 0);
}

Item top(Stack *s)
{
    return s->values[s->top - 1];
}

Item pop(Stack *s)
{
    s->top--;
    return s->values[s->top];
}

void push(Stack *s, Item val)
{
    s->values[s->top++] = val;
}
int priority(char c)
{
    switch(c)
    {
    case '+':
        return 0;
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;

    }
}
float evaluate(char x,float op1,float op2)
{
    if(x=='+')
        return(op1+op2);
    else if(x=='-')
        return(op1-op2);
    else if(x=='*')
        return(op1*op2);
    else if(x=='/')
        return(op1/op2);
    else if(x=='%')
        return(fmod(op1,op2));
    else if(x=='^')
        return(pow(op1,op2));
    else return 0;
}
float evaluatePostfix(char *postfix)
{
    Stack *s = initialize();
    Item value;

    int i;
    float a,b,x;
    char z;
    char *tok=strtok(postfix," ");
    while(tok!=NULL)
    {
        if(!tok[0]=='-'&&strlen(tok)>1)
        {
            if(!isdigit(tok[0]))
            {
                a = pop(s).fData;
                b = pop(s).fData;
                z = tok[0];
                x = evaluate(z, b, a);

                value.fData = x;
                push(s, value);
            }
            else
            {
                value.fData = atof(tok);
                push(s, value);
            }
        }
        else
            {
           if(isdigit(tok[1])||isdigit(tok[0]))
            {
                value.fData = atof(tok);
                push(s, value);

            }
            else
            {
                  a = pop(s).fData;
                b = pop(s).fData;
                z = tok[0];
                x = evaluate(z, b, a);

                value.fData = x;
                push(s, value);
            }
        }
            tok=strtok(NULL," ");
        }
        printf("result = %.2f\n",x);
    }

void infixToPostfix(char* infix ,char* postfix)
{
    Stack* s=initialize();
    char*tok;
    Item temp;
    tok =strtok(infix," ");
    int i;
    int k=0;
    while(tok!=NULL)
    {
        i=0;
        if(isdigit(tok[i]) || (tok[i]=='-' && strlen(tok)>1))
        {
            for(i=0;i<strlen(tok);i++){
                postfix[k++]=tok[i];
            }
                postfix[k++]=' ';
        }
        else
        {
            Item x;
            x.cData = tok[0];

            if(tok[0]==')')
            {
                while(!isEmpty(s) && top(s).cData!='(')
                {
                    postfix[k++]=pop(s).cData;
                    postfix[k++]=' ';
                }
                pop(s);
            }

            else if(isEmpty(s))
            {
                push(s,x);
            }
            else
            {
                while(!isEmpty(s) && priority(top(s).cData)>=priority(tok[0]) && top(s).cData!='('){
                        postfix[k++]=pop(s).cData;
                        postfix[k++]=' ';
                      }
                      push(s,x);

            }
        }
       tok=strtok(NULL," ");
    }
    while(!isEmpty(s)){
            postfix[k++] = pop(s).cData;
            postfix[k++] = ' ';

    }
    postfix[k]='\0';
     printf("the postfix: %s\n", postfix);
}



void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
int main()
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixToPostfix(infixExpr, postfixExpr);
        evaluatePostfix(postfixExpr);
        strcpy(postfixExpr, "");
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}
