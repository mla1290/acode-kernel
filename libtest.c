/* libtest.c: A-code kernel -- copyright Mike Arnautov 1990-2018, licensed
 * under GPL (version 3 or later) or the Modified BSD Licence, whichever
 * is asserted by the supplied LICENCE file.
 *
 * This is a simple front-end program for testing library mode builds
 * of A-code games. It is used automatically by the advmake script when
 * invoked with the -L option.
 * 
 * See library-mode.html in the A-code tarball (or at https://mipmip.org/acode)
 * for details of the library mode interface.
 */
#define LIBTEST_VERSION "12.03, 16 Nov 2017"
/*
 * 20 Aug 16   MLA        Initial coding.
 */ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *advturn(char *cmd); // A-code kernel interface function

int main(int argc, char **argv)
{
  char *list[100];    // Array of menu options
  char buf[100];
  char **lptr = list;
  char *ptr;
  char *cptr;
  char *sptr;
  int html = 0;       // Default is plain text
  int cnt = 1;
  int tcnt;
  int i;
  
  if (argc > 2 || (argc == 2 && strcmp (*(argv + 1), "-html") != 0))
  {
    printf ("Usage: %s [-html]\n", *argv);
    return 1;
  }
  html = argc == 2;   // Note HTML mode
/*
 * Set 1st menu entry.
 */
  *lptr++ = html ? "_START_HTML_" : "_START_TEXT_";
/*
 * Request '|' separated list of saved games (if any).
 */
  sptr = advturn("_LIST_");
  ptr = sptr;
  if (*ptr)
  {
    while (ptr)
    {
 /*
  * Saved game names cannot start with (or contain) '.'. except
  * for the automatic, persistent state save -- if present, it
  * will be the first list entry.
  */
      if (*ptr == '.' && (*(ptr + 1) < 'A' || *(ptr + 1) > 'Z'))
      {
         *lptr++ = html ? "_RESUME_HTML_" : "_RESUME_TEXT_"; 
         cnt++;
      }
      if ((ptr = strchr(ptr, '|'))) ptr++;
    }
    cptr = sptr;
/*
 * The rest of the list consiste of genuine player saves.
 */
    while (cptr)
    {
      ptr = cptr;
      cptr = strchr(ptr, '|');
      if (cptr) *cptr++ = '\0';
      if (*ptr != '.')
      {
         *lptr = malloc (12 + strlen(ptr));
         sprintf(*lptr++, "_LOAD_%s_%s", (html ? "HMTL" : "TEXT"), ptr);
         cnt++;
      }
    }
  }
  tcnt = cnt; // Temporary copy of the command list count
  i = 0;      // Counts of menu entrie
/*
 * Show the menu, numbering individual options from 1 up.
 */
  lptr = list;
  while (tcnt--)
  {
    cptr = *lptr;
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
      cptr += 11;                         // Point at actual game name
      printf("'%s'\n", cptr);
    }
    lptr++;
  }
/*
 * Get player's choice as an option number.
 */
  printf("Your choice: ");
  fgets(buf,10, stdin);
  i = *buf - '0';
  if (i > cnt)
  {
    printf("Bad choice: %d!\n", i);
    return 1;
  }
  cptr = list[i - 1];
  if (*cptr == '_')
    strcpy(buf, cptr);
  else
  {
    strcpy(buf, "_LOAD_TEXT_");
    strcat(buf, cptr);
  }
/*
 * Let us play!
 */
  while (1)
  {
    i = 0;                  // Default to game is in progress
    ptr = advturn(buf);     // Supply player command and get game's response
    if (*ptr == 'f') i = 1; // Final response, i.e. end of game
    if (*ptr) 
      printf ("\n%s", ++ptr);             // Show the response, if there is one
    if (i) break;           // Finish play
    if (html || !*ptr) 
      printf("%s\n? ", html ? "\n" : ""); // Issue a prompt, if necessary
    fgets(buf,99, stdin);   // Get player's command
  }
  puts("");
}
/*
/*======================================================================*/
