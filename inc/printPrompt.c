#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define size 1024

char* printPrompt()
{
  char cwd[1024],username[50],hostname[50];
  char *ret=(char*)malloc(2*size*sizeof(char));
  strcpy(username,getenv("USERNAME"));
  gethostname(hostname,50);
  getcwd(cwd,sizeof(cwd));
  sprintf(ret, "%s @ %s : %s $ ",username,hostname,cwd);
  return ret;
}

// int main(int argc, char *argv[]) {
//   printPrompt();
//   chdir("inc");
//   printPrompt();
//   return 0;
// }
