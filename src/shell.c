#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../inc/inbuiltCommands.c"
#include "../inc/printPrompt.c"
#include "../inc/parse.c"


// #define WORD_SIZE 100

int main(int argc, char const *argv[]) {
  int childPid, status,i=0;
  char *cmdLine;
  char ***cmd;
  // char sysPath[100];
  char* printPromptStr;


  while(1)
  {
    printPromptStr=printPrompt();

    cmdLine = readline(printPromptStr);
    // printf("cmdline = %s\n", cmdLine);
    cmd = parseMulti(cmdLine);
    // printf("cmd[0] = %s\n", cmd[0]);

    for(i=0;cmd[i]!=NULL;i++)
    {
      // int j=0;
      // for(j=0;cmd[i][j]!=NULL;j++)  printf("%s",cmd[i][j] );

      if(cmd[i][0]==NULL) continue;

      if(isInbuilt(cmd[i][0]))
      {
        execInbuilt(cmd[i]);
      }
      else
      {
        childPid = fork();
        if(childPid==0)
        {
          // sysPath[0]='\0';
          // strcat(sysPath,"/bin/");
          // strcat(sysPath,cmd[i][0]);
          execvp(cmd[i][0],cmd[i]);
          // If binary is not there in /bin, try /usr/bin
          // sysPath[0]='\0';
          // strcat(sysPath,"/usr/bin/");
          // strcat(sysPath,cmd[i][0]);
          // execv(sysPath,cmd[i]);
          printf("Error executing command\n");
          exit(0);
        }
        else
        {
            waitpid(childPid,&status,0);
        }
      }
    }

  }
  return 0;
}
