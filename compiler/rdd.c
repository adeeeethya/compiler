#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define SUCCESS 1
#define FAILED 0
const char *cursor;
int main()
{
  char string[64];
  printf("enter the expression : \n");
  scanf("%s",string);
  
  cursor=string;
  printf("INPUT                  ACTION");
  if(E() && (*cursor=='\0' || *cursor=='$'))
  {
    printf("string successfully parsed.. \n");
    return 0;
  }
  else
  {
    printf("Error occured while parsing the string.. \n");
    return 1;
  }
}

int E()
{
  printf("%-16s E-> T E'\n",cursor);
  if(T())
  {
    if(Edash())
    {
      return SUCCESS;
    }
    else
    {
      return FAILED;
    }
  }
  else
  {
    return FAILED;
  }
}

int Edash()
{
  if(*cursor=='+')
  {
    printf("%-16s E'->+TE'\n",cursor);
    cursor++;
    if(T())
    {
      if(Edash())
      {
        return SUCCESS;
      }
      else
      {
        return FAILED;
      }
    } 
    else
    {
      return FAILED;
    }
  } 
  else
  {  
    printf("%-16s E'->$",cursor);
    return SUCCESS;
  }
}

int
