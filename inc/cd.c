#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define size 1024

int cd(char* inp)
{
  char path[size];
  if(inp[0]!='~') strcpy(path,inp);
  else
  {
    if(inp[1]=='/')
    {
      strcpy(path,getenv("HOME"));
      strcat(path,"/");
      strcat(path,inp+2);
    }
    else if(inp[1]!='\0'){
      strcpy(path,"/home/");
      strcat(path,inp+1);
    }
    else{
      strcpy(path,getenv("HOME"));
    }
  }
  int status = chdir(path);
  if(status!=0)
  {
    // printf("%s\n", path);
    printf("Cannot change directory to : %s\n",inp );
    return 0;
  }
  else return 1;
}

// int main(int argc, char *argv[]) {
//   char cwd[size];
//   cd(argv[1]);
//   getcwd(cwd,sizeof(cwd));
//   printf("cwd is %s\n",cwd );
//   return 0;
// }
