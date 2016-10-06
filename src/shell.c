#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "../inc/inbuiltCommands.c"
#include "../inc/printPrompt.c"
#include "../inc/parse.c"

#define WORD_SIZE 100

int main(int argc, char const *argv[]) {
  int childPid, status,i=0,isBG=0, numBG=0, isPipe[WORD_SIZE];
  char *cmdLine , inPath[WORD_SIZE], outPath[WORD_SIZE];
  char ***cmd;
  char* printPromptStr;
  struct BG BGproc[WORD_SIZE];

  inPath[0]='\0';
  outPath[0]='\0';

  int fd[2],fd_old_in=0;

  while(1)
  {
    printPromptStr=printPrompt();

    cmdLine = readline(printPromptStr);
    // printf("cmdline = %s\n", cmdLine);

    add_history(cmdLine);

    setZero(isPipe,WORD_SIZE);
    cmd = parseMulti(cmdLine, isPipe);
    // printf("cmd[0] = %s\n", cmd[0]);

    for(i=0;cmd[i]!=NULL;i++)
    {
      // int j=0;
      // for(j=0;cmd[i][j]!=NULL;j++)  printf("%s",cmd[i][j] );

      if(cmd[i][0]==NULL) continue;

      if(isInbuilt(cmd[i][0]))
      {
        execInbuilt(cmd[i], BGproc, numBG);
      }
      else
      {
        isBG=0;
        if(hasAmpersand(cmd[i]))
        {
          // printf("hi\n" );
          isBG=1;
        }
        if(isPipe[i+1])pipe(fd);

        childPid = fork();

        if(childPid==0)
        {
          if(isPipe[i])
          {
            dup2(fd_old_in,0);
            close(fd[0]);
          }
          if(isPipe[i+1])  dup2(fd[1],1);

          parseRedir(cmd[i],inPath,outPath);

          if(strlen(outPath)>0)
          {
            close(1);
            open(outPath,O_RDWR | O_CREAT | O_APPEND, S_IRWXU | S_IRWXG | S_IRWXO);
            close(2);
            open(outPath,O_RDWR | O_CREAT | O_APPEND, S_IRWXU | S_IRWXG | S_IRWXO);
          }

          if(strlen(inPath)>0)
          {
            FILE *fp=fopen(inPath,"r");
            if(fp!=NULL)
            {
              close(0);
              open(inPath,O_RDONLY);
              fclose(fp);
            }
            else
            {
              printf("Cannot open file : %s\n", inPath);
              exit(0);
            }
          }

          if(isBG)
          {
            close(1);
            open("background_processes_output.txt",O_RDWR | O_CREAT | O_APPEND, S_IRWXU | S_IRWXG | S_IRWXO);
          }

          execvp(cmd[i][0],cmd[i]);

          printf("Couldn't execute command : %s\n",cmd[i][0]);
          exit(0);
        }
        else
        {
          if(!isBG)
          {
            waitpid(childPid,&status,0);
          }
          else
          {
            printf("Process %d (cmd : %s) is running in background\n", childPid,cmd[i][0]);
            BGproc[numBG].pid=childPid;
            strcpy(BGproc[numBG].cmd,cmd[i][0]);
            numBG++;
          }
          if(isPipe[i+1])
          {
            close(fd[1]);
            fd_old_in=fd[0];
          }
        }
      }
    }

  }
  return 0;
}
