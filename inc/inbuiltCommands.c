#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>

#define size 1024
#define WORD_SIZE 100

struct BG
{
  int pid;
  char cmd[WORD_SIZE];
};

int cd(char* inp)
{
  char path[size];

  if(inp==NULL)
  {
    strcpy(path,getenv("HOME"));
  }
  else
  {
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

void lsb(struct BG *BGproc,int numBG)
{
  int i=0,status;
  printf("PID\t\tCommand\t\tStatus\n");
  for(i=0;i<numBG;i++)
  {
    if(waitpid(BGproc[i].pid,&status,WNOHANG)==0){
      printf("%d\t\t%s\t\tRunning\n",BGproc[i].pid, BGproc[i].cmd );
    }
    else{
      printf("%d\t\t%s\t\tExited\n",BGproc[i].pid, BGproc[i].cmd );
    }
  }
  return;
}

int isInbuilt(char* inp)
{
  if(strcmp(inp,"cd")==0) return 1;
  if(strcmp(inp,"exit")==0) return 1;
  if(strcmp(inp,"lsb")==0) return 1;
  return 0;
}

void execInbuilt(char **inp,struct BG *BGproc,int numBG)
{
  if(strcmp(inp[0],"cd")==0)  cd(inp[1]);
  if(strcmp(inp[0],"exit")==0) exit(0);
  if(strcmp(inp[0],"lsb")==0) lsb(BGproc,numBG);
  return;
}
// int main(int argc, char *argv[]) {
//   char cwd[size];
//   cd(argv[1]);
//   getcwd(cwd,sizeof(cwd));
//   printf("cwd is %s\n",cwd );
//   return 0;
// }
