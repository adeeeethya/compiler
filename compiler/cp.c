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
        if (op[i][0] == '=')
        {
            for (int j = i + 1; j < n; j++)
            {
                if (strcmp(res[i], a1[j]) == 0)
                    strcpy(a1[j], a1[i]);

                if (strcmp(res[i], a2[j]) == 0)
                    strcpy(a2[j], a1[i]);
            }

            strcpy(op[i], "#");
        }
    }

    fprintf(out, "Constant propagated code:\n");
    fprintf(out, "OPR\tA1\tA2\tRES\n");

    for (int i = 0; i < n; i++)
    {
        if (op[i][0] != '#')
            fprintf(out, "%s\t%s\t%s\t%s\n",
                    op[i], a1[i], a2[i], res[i]);
    }

    fclose(out);
    return 0;
}
