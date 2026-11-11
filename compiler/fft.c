

void findfirst()
{
  int changed=1;
  while(changed)
  {
    changed=0;
    for(int p=0;p<n;p++)
    {
      int lhs=production[p][0]-'A';
      int i=2;
      int nullable=1;
      while(production[p][i]!='\0')
      {
        char symbol=production[p][i];
        if(symbol=="#")
        {
          if(addtoset(first[lhs],symbol))
          {
            changed=1;
            
          }
          break;
        }
        if(!isnonterminal(symbol))
        {
          if(addtoset(first[lhs],symbol)
          {
            changed=1;
          }
          nullable=0;
          break;
        }
        int index=symbol-'A'
        for(int j=0;first[index][j]!='\0';j++)
        {
          if(first[index][j]!="#")
          {
            if(addtoset(first[lhs],first[index][j])
            {
              changed=1;
            }
          }
        }
        if(strchr(first[index],"#")==NULL)
        {
          nullable=0;
          break
        }
        i++;
      }
      if(nullable)
      {
        if(addtoset(first[lhs],"#")
        {
          changed=1;
        }
      }
    }
  }
}

void findfollow()
{
  int start=production[0][0]-'A';
  addtoset(follow[start],"$");
  
  changed=1;
  while(changed)
  {
    changed=0;
    for(int p=0;p<n;p++)
    {
      int lhs=production[p][0]-'A';
      int len=strlen(production[p]);
      for(int i=2;i<len;i++)
      {
      if(!isnonterminal(production[p][i]))
      {
       continue; 
      }
      int current=production[p][i]-'A';
      int nullable=1
      for(int j=i+1;j<n;j++)
      {
        int next=production[p][j];
        if(!isnonterminal(next))
        {
          if(next!="#")
          {
            if(addtoset(follow[current],next))
            {
              changed=1;
            }
            nullable=0;
            break;
          }
        }
        int nextindex=index-'A';
        for(int k=0;first[nextindex][k]!='\0';k++)
        {
          if(first[nextindex][k]!="#")
          {
            if(addtoset(follow[current],first[nextindex][k]))
            {
              changed=1;
            }
          }
        }
        if(strchr(first[nextindex],"#")==0)
        {
          nullable=0;
          break;
        }
      }
      
      
    }
  }
}
