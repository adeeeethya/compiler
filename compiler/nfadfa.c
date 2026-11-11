#include <stdio.h>
#define MAX 20
#define SYMBOLS 10
#define MAX_DFA 1024

int n, symbols;
char inputSymbols[SYMBOLS];

int transition[MAX][SYMBOLS][MAX];
int finalState[MAX];

int dfaStates[MAX_DFA][MAX];
int dfaTransition[MAX_DFA][SYMBOLS];
int dfaFinalState[MAX_DFA];

int dfaCount = 0;

// Check whether two sets are equal
int sameSet(int a[], int b[])
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[i])
            return 0;
    }
    return 1; 
}

// Find whether a DFA state already exists
int findState(int set[])
{
    for (int i = 0; i < dfaCount; i++)
    {
        if (sameSet(dfaStates[i], set))
            return i;
    }

    return -1;
}

// Add a new DFA state if it does not exist
int addState(int set[])
{
    int index = findState(set);

    if (index != -1)
        return index;

    for (int i = 0; i < n; i++)
        dfaStates[dfaCount][i] = set[i];

    return dfaCount++;
}

// Print a set of NFA states
void printSet(int set[])
{
    int first = 1;

    printf("{ ");

    for (int i = 0; i < n; i++)
    {
        if (set[i])
        {
            if (!first)
                printf(", ");

            printf("%d", i);
            first = 0;
        }
    }

    printf(" }");
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

    // Read NFA transitions
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

    // Read final states
    printf("\nEnter number of final states: ");
    scanf("%d", &count);
 
    printf("Enter final states: ");

    for (int i = 0; i < count; i++)
    {
        int state;

        scanf("%d", &state);

        finalState[state] = 1;
    }

    // Create starting DFA state {0}
    int startSet[MAX] = {0};

    startSet[0] = 1;

    addState(startSet);

    // Perform subset construction
    for (int i = 0; i < dfaCount; i++)
    {
        for (int s = 0; s < symbols; s++)
        {
            int newSet[MAX] = {0};

            for (int j = 0; j < n; j++)
            {
                if (dfaStates[i][j])
                {
                    for (int k = 0; k < n; k++)
                    {
                        if (transition[j][s][k])
                            newSet[k] = 1;
                    }
                }
            }

            dfaTransition[i][s] = addState(newSet);
        }
    }

    // Display DFA states
    printf("\nDFA STATES\n");

    for (int i = 0; i < dfaCount; i++)
    {
        printf("D%d = ", i);

        printSet(dfaStates[i]);

        printf("\n");
    }

    // Display DFA transitions
    printf("\nDFA TRANSITIONS\n");

    for (int i = 0; i < dfaCount; i++)
    {
        for (int s = 0; s < symbols; s++)
        {
            printf("D%d on %c = D%d ",
                   i,
                   inputSymbols[s],
                   dfaTransition[i][s]);

            printSet(dfaStates[dfaTransition[i][s]]);

            printf("\n");
        }
    }

    // Identify DFA final states
    printf("\nDFA FINAL STATES = { ");

    int first = 1;

    for (int i = 0; i < dfaCount; i++)
    {
        int isFinal = 0;

        for (int j = 0; j < n; j++)
        {
            if (dfaStates[i][j] && finalState[j])
            {
                isFinal = 1;
                break;
            }
        }

        if (isFinal)
        {
            if (!first)
                printf(", ");

            printf("D%d", i);

            first = 0;
        }
    }

    printf(" }\n");

    return 0;
}

