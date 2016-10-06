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


// struct BG
// {
//   int pid;
//   char cmd[WORD_SIZE];
// } BGproc[WORD_SIZE];


int main(int argc, char const *argv[]) {
  int childPid, status,i=0,isBG=0;
  char *cmdLine , inPath[WORD_SIZE], outPath[WORD_SIZE];
  char ***cmd;
  // char sysPath[100];
  char* printPromptStr;
  struct BG BGproc[WORD_SIZE];
  int numBG=0;

  inPath[0]='\0';
  outPath[0]='\0';

  while(1)
  {
    printPromptStr=printPrompt();

    cmdLine = readline(printPromptStr);
    // printf("cmdline = %s\n", cmdLine);

    add_history(cmdLine);

    cmd = parseMulti(cmdLine);
    // printf("cmd[0] = %s\n", cmd[0]);

    for(i=0;cmd[i]!=NULL;i++)
    {
      // int j=0;
      // for(j=0;cmd[i][j]!=NULL;j++)  printf("%s",cmd[i][j] );

      if(cmd[i][0]==NULL) continue;

      if(isInbuilt(cmd[i][0]))
      {
        execInbuilt(cmd[i],BGproc,numBG);
      }
      else
      {
        isBG=0;
        if(hasAmpersand(cmd[i]))
        {
          // printf("hi\n" );
          isBG=1;
        }
        childPid = fork();
        if(childPid==0)
        {
          // sysPath[0]='\0';
          // strcat(sysPath,"/bin/");
          // strcat(sysPath,cmd[i][0]);
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
        }
      }
    }

  }
  return 0;
}
