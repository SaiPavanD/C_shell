#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../inc/cd.c"
#include "../inc/printPrompt.c"
#include "../inc/parse.c"


// #define WORD_SIZE 100

int main(int argc, char const *argv[]) {
  int childPid, status;
  char *cmdLine;
  char **cmd;
  char sysPath[100];
  char* printPromptStr;


  while(1)
  {
    printPromptStr=printPrompt();

    cmdLine = readline(printPromptStr);
    // printf("cmdline = %s\n", cmdLine);
    cmd = parse(cmdLine);
    // printf("cmd[0] = %s\n", cmd[0]);
    if(cmd[0]==NULL) continue;

    if(strcmp(cmd[0],"cd")==0)
    {
      cd(cmd[1]);
    }
    else
    {
      childPid = fork();
      if(childPid==0)
      {
        sysPath[0]='\0';
        strcat(sysPath,"/bin/");
        strcat(sysPath,cmd[0]);
        execv(sysPath,cmd);
        printf("Error executing command\n");
      }
      else
      {

          waitpid(childPid,&status,0);
      }
    }

  }
  return 0;
}
