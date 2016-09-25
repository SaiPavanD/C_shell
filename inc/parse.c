#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// #define size 1024

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

// int main(int argc, char *argv[]) {
//   printPrompt();
//   chdir("inc");
//   printPrompt();
//   return 0;
// }
