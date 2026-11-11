void sameset
void findstate
void addstate
void printset

void sameset(int a[],int b[])
{
  for(int i=0;i<n;i++)
  {
    if(a[i] != b[i])
    {
      return 0;
    }
  }
  return 1;
}

void findstate(int state)
{
  for(int i=0;i<dfacount;i++)
  {
    if(dfastates[i]==state)
    {
      return -1
    }
  }
}

