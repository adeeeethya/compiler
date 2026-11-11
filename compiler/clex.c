
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *keywords[] = {
    "int", "char", "float", "double", "for",
    "while", "do", "switch", "case", "static", "main"
};

int isKeyword(char str[])
{
    int n = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < n; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int main()
{
    FILE *fp, *out, *sym;
    char ch, buffer[100];
    char symbols[100][50];

    int count = 0;
    int i, tokenType, found;

    fp = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    sym = fopen("symtab.txt", "w");

    if (fp == NULL)
    {
        printf("Cannot open input file\n");
        return 0;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isspace(ch))
            continue;

        tokenType = 0;

        if (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '%' || ch == '=' ||
            ch == '>' || ch == '<' || ch == '!')
            tokenType = 1;

        else if (ch == '(' || ch == ')' ||
                 ch == '{' || ch == '}' ||
                 ch == '[' || ch == ']' ||
                 ch == ';' || ch == ',')
            tokenType = 2;

        else if (isalpha(ch) || ch == '_')
            tokenType = 3;

        else if (isdigit(ch))
            tokenType = 4;

        switch (tokenType)
        {
            case 1:
                fprintf(out, "OPERATOR : %c\n", ch);
                break;

            case 2:
                fprintf(out, "DELIMITER : %c\n", ch);
                break;

            case 3:
                i = 0;
                buffer[i++] = ch;

                while ((ch = fgetc(fp)) != EOF &&
                       (isalnum(ch) || ch == '_'))
                {
                    buffer[i++] = ch;
                }

                buffer[i] = '\0';

                if (ch != EOF)
                    ungetc(ch, fp);

                if (isKeyword(buffer))
                {
                    fprintf(out, "KEYWORD : %s\n", buffer);
                }
                else
                {
                    fprintf(out, "IDENTIFIER : %s\n", buffer);

                    found = 0;

                    for (i = 0; i < count; i++)
                    {
                        if (strcmp(symbols[i], buffer) == 0)
                        {
                            found = 1;
                            break;
                        }
                    }

                    if (!found)
                    {
                        strcpy(symbols[count], buffer);
                        count++;
                    }
                }

                break;

            case 4:
                i = 0;
                buffer[i++] = ch;

                while ((ch = fgetc(fp)) != EOF && isdigit(ch))
                {
                    buffer[i++] = ch;
                }

                buffer[i] = '\0';

                if (ch != EOF)
                    ungetc(ch, fp);

                fprintf(out, "NUMBER : %s\n", buffer);
                break;

            default:
                fprintf(out, "SPECIAL SYMBOL : %c\n", ch);
        }
    }

    fprintf(sym, "SYMBOL TABLE\n\n");
    fprintf(sym, "Index\tIdentifier\n");
    fprintf(sym, "--------------------\n");

    for (i = 0; i < count; i++)
    {
        fprintf(sym, "%d\t%s\n", i + 1, symbols[i]);
    }

    fclose(fp);
    fclose(out);
    fclose(sym);

    printf("Lexical analysis completed.\n");
    printf("Output stored in output.txt\n");
    printf("Symbol table stored in symtab.txt\n");

    return 0;
}

