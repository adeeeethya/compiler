
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct table
{
    char op[2];
    char a1[10];
    char a2[10];
    char res[10];
} st[100];

int main()
{
    int sum=0;

    FILE *in,*out;

    in=fopen("in.txt","r");

    if(in==NULL)
    {
        printf("Input file error\n");
        return 1;
    }

    out=fopen("output.txt","w");

    if(out==NULL)
    {
        printf("Output file error\n");
        fclose(in);
        return 1;
    }

    int n=0;

    while(n<100 && fscanf(in,"%1s %9s %9s %9s",
          st[n].op,st[n].a1,st[n].a2,st[n].res)==4)
    {
        n++;
    }

    for(int i=0;i<n;i++)
    {
        if(strcmp(st[i].op,"+")==0 ||
           strcmp(st[i].op,"-")==0 ||
           strcmp(st[i].op,"*")==0 ||
           strcmp(st[i].op,"/")==0)
        {
            if(isdigit(st[i].a1[0]) &&
               isdigit(st[i].a2[0]))
            {
                int x=atoi(st[i].a1);
                int y=atoi(st[i].a2);

                if(strcmp(st[i].op,"+")==0)
                    sum=x+y;

                else if(strcmp(st[i].op,"-")==0)
                    sum=x-y;

                else if(strcmp(st[i].op,"*")==0)
                    sum=x*y;

                else if(strcmp(st[i].op,"/")==0)
                {
                    if(y==0)
                        continue;

                    sum=x/y;
                }

                strcpy(st[i].op,"=");
                sprintf(st[i].a1,"%d",sum);
                strcpy(st[i].a2,"-");
            }
        }
    }

    fprintf(out,"OP\tA1\tA2\tRES\n");

    for(int i=0;i<n;i++)
    {
        fprintf(out,"%s\t%s\t%s\t%s\n",
        st[i].op,st[i].a1,st[i].a2,st[i].res);
    }

    fclose(in);
    fclose(out);

    return 0;
}

