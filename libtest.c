#include "stdio.h"
#include "string.h"
extern char *advturn(char *);
int main()
{
  char command[1024];
  char *response;
  command[1023] = '\0';
  strcpy (command, "_START_TEXT_");
  while (1)
  {
    response = advturn(command);
    printf("\n%s", *response ? response + 1 : "? ");
    if (*response == 'f')
      break;
    fgets(command, 1023, stdin);
  }
  puts("");
}
