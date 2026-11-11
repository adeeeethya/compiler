#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int stk[100];
int top=-1;
char expr[100],pex[100];
int pcnt=0;
void push(char ch)
{
  stk[++top]=ch;
}
char pop()
{
  return stk[top--];
}
int rank(char ch, int stk_rank)
{
  if(ch=='=') return stk_rank ? 1 : 1;
  if(ch=='+' || ch=='-') return 2;
  if(ch=='*' || ch=='/') return 3;
  if(ch=='^') return stk_rank ? 4 : 5;
  if(ch=='(') return stk_rank ? 0 : 6;
  return -1;
}
void inpos()
{
  char symbol,temp;
  strcat(expr,")");
  push('(');
  for(int i=0;expr[i]!='\0';i++)
  {
    symbol=expr[i];
    if(isalpha(symbol))
    {
      pex[pcnt++]=symbol;
    }
    else if(symbol==')')
    {
      while((temp=pop())!='(')
      {
        pex[pcnt++]=temp;
      }
    }
    else
    {
      
        while(rank(stk[top],1)>=rank(symbol,0))
        {
          pex[pcnt++]=pop();
          
        }
        push(symbol);
    }
      
  }
  pex[pcnt]='\0';
  printf("postfix expression:%s\n",pex);
}

void icg()
{
  char ch;
  char a1,a2;
  char res='0';
  printf("op\ta1\ta2\tres\n");
  for(int i=0;pex[i]!='\0';i++)
  {
    ch=pex[i];
    if(isalpha(ch))
    {
      push(ch);
    }
    else if(ch=='=')
    {
    a2=pop();
    a1=pop();

    printf("=\t");

    if(isdigit(a2))
        printf("t");

    printf("%c\t-\t%c\n",a2,a1);
    }
    else
    {
      a2=pop();
      a1=pop();
      
      printf("%c\t",ch);
      if(isdigit(a1))
      {
        printf("t");
      }
      printf("%c\t",a1);
      if(isdigit(a2))
      {
        printf("t");
      }
      printf("%c\tt%c\n",a2,res);
      push(res++);
    }
    
  }
}

int main()
{
  printf("enter expression:\n");
  scanf("%s",expr);
  inpos();
  icg();
  return 0;
}
