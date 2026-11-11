#include <stdio.h>
#include <string.h>

#define SUCCESS 1
#define FAILED 0

char stack[64];
char input[64];

int top = -1;
int ip = 0;

void shift();
int reduce();
void display();

int main()
{
    printf("Enter the string\n");
    scanf("%62s", input);

    strcat(input, "$");

    printf("\n");
    printf("%-16s %-16s Action\n", "Stack", "Input");

    stack[++top] = '$';
    stack[top + 1] = '\0';

    while (1)
    {
        display();

        if (reduce())
        {
            continue;
        }

        if (stack[top] == 'E' && input[ip] == '$')
        {
            display();
            printf("String is successfully parsed\n");
            return 0;
        }

        if (input[ip] != '$')
        {
            shift();
        }
        else
        {
            printf("Error in parsing String\n");
            return 1;
        }
    }
}

void shift()
{
    char symbol = input[ip];

    stack[++top] = symbol;
    stack[top + 1] = '\0';

    ip++;

    printf("%-16s %-16s Shift %c\n",stack, &input[ip], symbol);
}

int reduce()
{
    // F -> a
    if (top >= 0 && stack[top] == 'a')
    {
        stack[top] = 'F';

        printf("%-16s %-16s Reduce F -> a\n",
               stack, &input[ip]);

        return SUCCESS;
    }

    // F -> ( E )
    if (top >= 2 &&
        stack[top - 2] == '(' &&
        stack[top - 1] == 'E' &&
        stack[top] == ')')
    {
        top -= 2;
        stack[top] = 'F';
        stack[top + 1] = '\0';

        printf("%-16s %-16s Reduce F -> ( E )\n",
               stack, &input[ip]);

        return SUCCESS;
    }

    // T -> T * F
    if (top >= 2 &&
        stack[top - 2] == 'T' &&
        stack[top - 1] == '*' &&
        stack[top] == 'F')
    {
        top -= 2;
        stack[top] = 'T';
        stack[top + 1] = '\0';

        printf("%-16s %-16s Reduce T -> T * F\n",
               stack, &input[ip]);

        return SUCCESS;
    }

    // T -> F
    if (top >= 0 && stack[top] == 'F')
    {
        stack[top] = 'T';

        printf("%-16s %-16s Reduce T -> F\n",
               stack, &input[ip]);

        return SUCCESS;
    }

    // E -> E + T
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '+' &&
        stack[top] == 'T')
    {
        top -= 2;
        stack[top] = 'E';
        stack[top + 1] = '\0';

        printf("%-16s %-16s Reduce E -> E + T\n",
               stack, &input[ip]);

        return SUCCESS;
    }

    // E -> T
    // Do not reduce T to E if next symbol is *
    if (top >= 0 &&
        stack[top] == 'T' &&
        (input[ip] == '+' ||
         input[ip] == ')' ||
         input[ip] == '$'))
    {
        stack[top] = 'E';

        printf("%-16s %-16s Reduce E -> T\n",
               stack, &input[ip]);

        return SUCCESS;
    }

    return FAILED;
}

void display()
{
    int i;

    for (i = 0; i <= top; i++)
        printf("%c", stack[i]);

    printf("%-15s ", "");

    for (i = ip; input[i] != '\0'; i++)
        printf("%c", input[i]);

    printf("\n");
}

