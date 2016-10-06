#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define size 1024

char** parse(char *inp)
{
  int i,n=strlen(inp),numWords=0;
  for(i=0;i<n;i++)
  {
    if(inp[i]!=' ' && (inp[i+1]==' ' || inp[i+1]=='\0' || inp[i+1]==EOF))
      numWords++;
  }
  char **ret = (char**)malloc((numWords+1)*sizeof(char*));
  for(i=0;i<=numWords;i++)
  {
    ret[i]=NULL;
  }
  char tempWord[100];

  int y=0,x=0;

  for(i=0;i<n;i++)
  {
    if(inp[i]!=' ')
    {
      tempWord[x]=inp[i];
      x++;
      if(inp[i+1]==' ' || inp[i+1]=='\0' || inp[i+1]==EOF)
      {
        tempWord[x]='\0';
        ret[y] = (char*)malloc((x+1)*sizeof(char));
        strcpy(ret[y],tempWord);
        y++;
        x=0;
      }
    }
  }

  // for(i=0;i<=numWords;i++)
  // {
  //   printf("%s\n",ret[i] );
  // }

  return ret;
}

char*** parseMulti(char *inp, int *isPipe)
{
  int i=0,numLines=1,n=strlen(inp),j=0,k=0;
  char temp[size];
  for(i=0;i<n;i++)
  {
    if(inp[i]==';')
      numLines++;
    if(inp[i]=='|')
      isPipe[numLines++]=1;
  }
  // printf("%d\n",numLines );
  char ***ret = (char***)malloc((numLines+1)*sizeof(char**));
  for(i=0;i<=numLines;i++)
  {
    ret[i]=NULL;
  }
  for(i=0;i<n;i++)
  {
    if(inp[i]!=';' && inp[i]!='|')
    {
      temp[j]=inp[i];
      j++;
    }
    else
    {
      temp[j]='\0';
      j=0;
      ret[k]=parse(temp);
      k++;
    }
  }
  temp[j]='\0';
  ret[k]=parse(temp);

  // for(j=0;j<=numLines;j++)
  // {
  //   for(i=0;ret[j][i]!=NULL;i++)
  //   {
  //     printf("%s ",ret[j][i] );
  //   }
  //   printf("\n");
  // }

  return ret;
}

int hasAmpersand(char **inp)
{
  int i;
  for(i=0;inp[i]!=NULL;i++)
  {
    if(strcmp(inp[i],"&")==0)
    {
      inp[i]=NULL;
      return 1;
    }
  }
  return 0;
}

int parseRedir(char** inp, char* inPath, char* outPath){
  int i,j;
  for(i=0;inp[i]!=NULL;i++)
  {
    if(strcmp(inp[i],"<")==0 && inp[i+1]!=NULL)
    {
      strcpy(inPath,inp[i+1]);
      for(j=i;inp[j+2]!=NULL;j++)
      {
        strcpy(inp[j],inp[j+2]);
      }
      inp[j++]=NULL;
      inp[j++]=NULL;
      break;
    }
    if(inp[i][0]=='<')
    {
      strcpy(inPath,inp[i]+1);
      for(j=i;inp[j+1]!=NULL;j++)
      {
        strcpy(inp[j],inp[j+1]);
      }
      inp[j++]=NULL;
      break;
    }
  }
  // printf("\n" );
  // for(i=0;inp[i]!=NULL;i++)
  // {
  //   printf("%s ", inp[i]);
  // }
  // printf("\n" );
  for(i=0;inp[i]!=NULL;i++)
  {
    if(strcmp(inp[i],">")==0 && inp[i+1]!=NULL)
    {
      strcpy(outPath,inp[i+1]);
      for(j=i;inp[j+2]!=NULL;j++)
      {
        strcpy(inp[j],inp[j+2]);
      }
      inp[j++]=NULL;
      inp[j++]=NULL;
      break;
    }
    if(inp[i][0]=='>')
    {
      strcpy(outPath,inp[i]+1);
      for(j=i;inp[j+1]!=NULL;j++)
      {
        strcpy(inp[j],inp[j+1]);
      }
      inp[j++]=NULL;
      break;
    }
  }
  // printf("\n" );
  // for(i=0;inp[i]!=NULL;i++)
  // {
  //   printf("%s ", inp[i]);
  // }
  // printf("\n" );
  return 0;
}

void setZero(int *arr, int n)
{
  int i;
  for(i=0; i<n;i++) arr[i] = 0;
  return;
}

// int main(int argc, char *argv[]) {
//   printPrompt();
//   chdir("inc");
//   printPrompt();
//   return 0;
// }
