/* libtest.c: A-code kernel -- copyright Mike Arnautov 1990-2016, licensed
 * under GPL (version 3 or later) or the Modified BSD Licence, whichever
 * is asserted by the supplied LICENCE file.
 */
#define LIBTEST_VERSION "12.02, 28 Dec 2016"
/*
 * 28 Dec 16   MLA        Show prompt is advturn() return null string.
 * 20 Aug 16   MLA        Initial coding.
 */ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *advturn(char *cmd);
int main()
{
  char *list[100];
  char buf[100];
  char **lptr = list;
  char *ptr;
  char *cptr;
  char *sptr;
  int cnt = 1;
  int tcnt;
  int i;
  *lptr++ = "_START_TEXT_";
//  advturn("_INFO_");
  sptr = advturn("_LIST_");
  ptr = sptr;
  if (*ptr)
  {
    while (ptr)
    {
      if (*ptr == '.' && (*(ptr + 1) < 'A' || *(ptr + 1) > 'Z'))
      {
         *lptr++ = "_RESUME_TEXT_";
         cnt++;
      }
      if ((ptr = strchr(ptr, '|'))) ptr++;
    }
    cptr = sptr;
    while (cptr)
    {
      ptr = cptr;
      cptr = strchr(ptr, '|');
      if (cptr) *cptr++ = '\0';
      if (*ptr != '.')
      {
         *lptr = malloc (12 + strlen(ptr));
         sprintf(*lptr++, "_LOAD_TEXT_%s", ptr);
         cnt++;
      }
    }
  }
  tcnt = cnt;
  i = 0;
  lptr = list;
  while (tcnt--)
  {
    cptr = *lptr;
    sptr = strstr(*lptr, "_TEXT_");
    if (!sptr) sptr = strstr(*lptr, "_HTML_");
    printf("%d: ", ++i);
    if (!strncmp(cptr, "_START_", 7))
    {
      printf("%s\n", "Start a new game");
      cptr += 6;
    }
    else if (!strncmp(cptr, "_RESUME_", 8))
    {
      printf("%s\n", "Resume your game in progress");
      cptr += 7;
    }
    else if (!strncmp(cptr, "_LOAD_", 6))
    {
      printf("%s", "Load game saved as ");
      cptr += 5;
      if (sptr) cptr += 6;
      printf("'%s'\n", cptr);
    }
    lptr++;
  }
  printf("Your choice: ");
  fgets(buf,10, stdin);
  i = *buf - '0';
  if (i > cnt)
  {
    printf("Bad choice: %d!\n", i);
    return;
  }
  cptr = list[i - 1];
  if (*cptr == '_')
    strcpy(buf, cptr);
  else
  {
    strcpy(buf, "_LOAD_TEXT_");
    strcat(buf, cptr);
  }
  printf("%s\n", buf);
  while (1)
  {
    i = 0;
    ptr = advturn(buf);
    while (*ptr == ' ' || *ptr == '?') ptr++;
    if (!*ptr) ptr = "? ";
    if (*ptr == 'f')
    {
      i = 1;
      ptr++;
    }
    printf ("\n%s", ptr);
    if (i) break;
    fgets(buf,99, stdin);
  }
}
