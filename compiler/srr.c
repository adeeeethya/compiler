#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
char input[64];
char stack[64];
int top=-1;
int ip=0;

void shift()
{
  char sym=input[ip];
  stack[++top]=sym;
  stack[top+1]='\0';
  ip++;
  
  printf("%-16s %-16s Shift %c",stack,&input[ip],sym);
}

void display()
{
  for(int i=0;i<=top;i++)
  {
    printf("%c",stack[i]);
  }
  printf("%-15s","");
  for(int j=ip;input[j]!='\0';j++)
  {
    printf("%c\n",input[j]);
  }
}

int reduce()
{
  //E->E+T
  if(top>=2 && stack[top-2]=='E' && stack[top-1]=='+' && stack[top]=='T')
  {
    top=top-2;
    stack[top]='E'
    stack[top+1]='\0';
    printf("%-16s %-16s Reduce E->E+T\n",stack,&input[ip]);
    return SUCCESS;
  }
}

int main()
{
  printf("enter the string : \n");
  scanf("%s",input);
  strcat(input,"$");
  printf("%-16s %-16s action","stack","input");
  stack[++top]=input[ip];
  stack[top+1]='\0';
  
  while(1)
  {
    display();
    if(reduce())
    {
      continue;
    }
    else if(stack[top]=='E' && input[ip]=='$')
    {
      display();
      printf("string is sucessfully parsed .. \n");
      return 0;
    }
    else if(input[ip]!='$')
    {
      shift();
    }
    else
    {
      printf("error in parsing the string .. \n");
      return 1;
    }
  }
}


