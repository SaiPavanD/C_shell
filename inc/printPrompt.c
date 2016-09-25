#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define size 1024

char* printPrompt()
{
  char cwd[1024];
  char *ret=(char*)malloc(2*size*sizeof(char));
  getcwd(cwd,sizeof(cwd));
  sprintf(ret, "username @ pcname : %s $ ",cwd);
  return ret;
}

// int main(int argc, char *argv[]) {
//   printPrompt();
//   chdir("inc");
//   printPrompt();
//   return 0;
// }
