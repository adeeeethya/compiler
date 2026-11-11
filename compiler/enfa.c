#include <stdio.h>
#define MAX 20
#define SYMBOLS 10

int n, symbols;
char inputSymbols[SYMBOLS];

int epsilon[MAX][MAX];
int transition[MAX][SYMBOLS][MAX];

int finalState[MAX];
int newFinalState[MAX];

int closure[MAX][MAX];

// Find epsilon closure using stack
void findEpsilonClosure(int state)
{
    int stack[MAX];
    int top = -1;
    int visited[MAX] = {0};

    stack[++top] = state;
    visited[state] = 1;

    while (top >= 0)
    {
        int current = stack[top--];

        for (int i = 0; i < n; i++)
        {
            if (epsilon[current][i] && !visited[i])
            {
                visited[i] = 1;
                stack[++top] = i;
            }
        }
    }

    for (int i = 0; i < n; i++)
        closure[state][i] = visited[i];
}

int main()
{
    int count;

    // Read number of states
    printf("Enter number of states: ");
    scanf("%d", &n);

    // Read number of input symbols
    printf("Enter number of input symbols: ");
    scanf("%d", &symbols);

    // Read input symbols
    printf("Enter input symbols:\n");

    for (int i = 0; i < symbols; i++)
        scanf(" %c", &inputSymbols[i]);

    // Read epsilon transitions
    printf("\nEnter epsilon transitions:\n");

    for (int i = 0; i < n; i++)
    {
        printf("State %d: ", i);
        scanf("%d", &count);

        for (int j = 0; j < count; j++)
        {
            int destination;

            scanf("%d", &destination);

            epsilon[i][destination] = 1;
        }
    }

    // Read normal transitions
    printf("\nEnter transitions:\n");

    for (int i = 0; i < n; i++)
    {
        for (int s = 0; s < symbols; s++)
        {
            printf("State %d on %c: ",
                   i, inputSymbols[s]);

            scanf("%d", &count);

            for (int j = 0; j < count; j++)
            {
                int destination;

                scanf("%d", &destination);

                transition[i][s][destination] = 1;
            }
        }
    }

    // Read original final states
    printf("\nEnter number of final states: ");
    scanf("%d", &count);

    printf("Enter final states: ");

    for (int i = 0; i < count; i++)
    {
        int state;

        scanf("%d", &state);

        finalState[state] = 1;
    }

    // Calculate epsilon closure of every state
    for (int i = 0; i < n; i++)
        findEpsilonClosure(i);

    // Calculate new final states
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (closure[i][j] && finalState[j])
            {
                newFinalState[i] = 1;
                break;
            }
        }
    }

    // Display epsilon closures
    printf("\nEPSILON CLOSURE\n");

    for (int i = 0; i < n; i++)
    {
        printf("E-closure(%d) = { ", i);

        int first = 1;

        for (int j = 0; j < n; j++)
        {
            if (closure[i][j])
            {
                if (!first)
                    printf(", ");

                printf("%d", j);
                first = 0;
            }
        }

        printf(" }\n");
    }

    // Calculate NFA transitions without epsilon
    printf("\nNFA WITHOUT EPSILON TRANSITIONS\n");

    for (int i = 0; i < n; i++)
    {
        for (int s = 0; s < symbols; s++)
        {
            int result[MAX] = {0};

            for (int j = 0; j < n; j++)
            {
                if (closure[i][j])
                {
                    for (int k = 0; k < n; k++)
                    {
                        if (transition[j][s][k])
                        {
                            for (int l = 0; l < n; l++)
                            {
                                if (closure[k][l])
                                    result[l] = 1;
                            }
                        }
                    }
                }
            }

            printf("delta(%d, %c) = { ",
                   i, inputSymbols[s]);

            int first = 1;

            for (int j = 0; j < n; j++)
            {
                if (result[j])
                {
                    if (!first)
                        printf(", ");

                    printf("%d", j);
                    first = 0;
                }
            }

            printf(" }\n");
        }
    }

    // Display new final states
    printf("\nNEW FINAL STATES = { ");

    int first = 1;

    for (int i = 0; i < n; i++)
    {
        if (newFinalState[i])
        {
            if (!first)
                printf(", ");

            printf("%d", i);
            first = 0;
        }
    }

    printf(" }\n");

    return 0;
}

