#include <stdio.h>
#include <string.h>

char op[32][2], a1[32][4], a2[32][4], res[32][4];
int n = 0;

int main()
{
    FILE *fp, *out;

    fp = fopen("in.txt", "r");
    out = fopen("output.txt", "w");

    if (fp == NULL || out == NULL)
    {
        printf("File error");
        return 1;
    }

    while (fscanf(fp, "%s %s %s %s",
                  op[n], a1[n], a2[n], res[n]) == 4)
        n++;

    fclose(fp);

    for (int i = 0; i < n; i++)
    {
        if (op[i][0] == '+' || op[i][0] == '*'
            || op[i][0] == '-' || op[i][0] == '/')
        {
            for (int j = i+1; j < n; j++)
            {
                if (strcmp(op[i], op[j]) == 0 &&
                    strcmp(a1[i], a1[j]) == 0 &&
                    strcmp(a2[i], a2[j]) == 0)
                {
                    strcpy(op[j], "=");
                    strcpy(a1[j], res[i]);
                    strcpy(a2[j], "-");
                    
                }
            }
        }
    }

    fprintf(out, "Common Subexpression Eliminated Code:\n");
    fprintf(out, "OPR\tA1\tA2\tRES\n");

    for (int i = 0; i < n; i++)
    {
        fprintf(out, "%s\t%s\t%s\t%s\n",
                op[i], a1[i], a2[i], res[i]);
    }

    fclose(out);
    return 0;
}
