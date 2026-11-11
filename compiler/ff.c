
#include <stdio.h>
#include <string.h>

#define MAX_PROD 50
#define MAX_LEN 50
#define MAX_NT 26

char production[MAX_PROD][MAX_LEN];
char first[MAX_NT][MAX_NT + 1];
char follow[MAX_NT][MAX_NT + 1];

int n;

// Check whether a character is a non-terminal
int isNonTerminal(char c)
{
    return c >= 'A' && c <= 'Z';
}

// Add a character to a set without duplicates
int addToSet(char set[], char c)
{
    int i = 0;

    while (set[i] != '\0')
    {
        if (set[i] == c)
            return 0;

        i++;
    }

    set[i] = c;
    set[i + 1] = '\0';

    return 1;
}

// Calculate FIRST sets
void findFirst()
{
    int changed = 1;
    while (changed)
    {
        changed = 0;

        for (int p = 0; p < n; p++)
        {
            int lhs = production[p][0] - 'A';
            int i = 2;
            int nullable = 1;

            while (production[p][i] != '\0')
            {
                char symbol = production[p][i];

                if (symbol == '#')
                {
                    if (addToSet(first[lhs], '#'))
                        changed = 1;

                    break;
                }

                if (!isNonTerminal(symbol))
                {
                    if (addToSet(first[lhs], symbol))
                        changed = 1;

                    nullable = 0;
                    break;
                }

                int index = symbol - 'A';

                for (int j = 0; first[index][j] != '\0'; j++)
                {
                    if (first[index][j] != '#')
                    {
                        if (addToSet(first[lhs], first[index][j]))
                            changed = 1;
                    }
                }

                if (strchr(first[index], '#') == NULL)
                {
                    nullable = 0;
                    break;
                }

                i++;
            }

            if (nullable)
            {
                if (addToSet(first[lhs], '#'))
                    changed = 1;
            }
        }
    }
}

// Calculate FOLLOW sets
void findFollow()
{
    int start = production[0][0] - 'A';

    addToSet(follow[start], '$');

    int changed = 1;

    while (changed)
    {
        changed = 0;

        for (int p = 0; p < n; p++)
        {
            int lhs = production[p][0] - 'A';
            int len = strlen(production[p]);

            for (int i = 2; i < len; i++)
            {
                if (!isNonTerminal(production[p][i]))
                    continue;

                int current = production[p][i] - 'A';
                int nullable = 1;

                for (int j = i + 1; j < len; j++)
                {
                    char next = production[p][j];

                    if (!isNonTerminal(next))
                    {
                        if (next != '#')
                        {
                            if (addToSet(follow[current], next))
                                changed = 1;

                            nullable = 0;
                            break;
                        }

                        // Epsilon does not make it non-nullable
                        continue;
                    }

                    int nextIndex = next - 'A';

                    for (int k = 0; first[nextIndex][k] != '\0'; k++)
                    {
                        if (first[nextIndex][k] != '#')
                        {
                            if (addToSet(follow[current],first[nextIndex][k]))
                                changed = 1;
                        }
                    }

                    if (strchr(first[nextIndex], '#') == NULL)
                    {
                        nullable = 0;
                        break;
                    }
                }

                if (i == len - 1 || nullable)
                {
                    for (int k = 0; follow[lhs][k] != '\0'; k++)
                    {
                        if (addToSet(follow[current],
                                     follow[lhs][k]))
                            changed = 1;
                    }
                }
            }
        }
    }
}

// Main function
int main()
{
    int used[MAX_NT] = {0};

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions:\n");
    printf("Use # for epsilon.\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%49s", production[i]);

        used[production[i][0] - 'A'] = 1;

        for (int j = 2; production[i][j] != '\0'; j++)
        {
            if (isNonTerminal(production[i][j]))
                used[production[i][j] - 'A'] = 1;
        }
    }

    findFirst();
    findFollow();

    printf("\nFIRST SETS\n");

    for (int i = 0; i < MAX_NT; i++)
    {
        if (used[i])
        {
            printf("FIRST(%c) = { ", 'A' + i);

            for (int j = 0; first[i][j] != '\0'; j++)
            {
                if (j > 0)
                    printf(", ");

                printf("%c", first[i][j]);
            }

            printf(" }\n");
        }
    }

    printf("\nFOLLOW SETS\n");

    for (int i = 0; i < MAX_NT; i++)
    {
        if (used[i])
        {
            printf("FOLLOW(%c) = { ", 'A' + i);

            for (int j = 0; follow[i][j] != '\0'; j++)
            {
                if (j > 0)
                    printf(", ");

                printf("%c", follow[i][j]);
            }

            printf(" }\n");
        }
    }

    return 0;
}

