/* adv01.c: A-code kernel - copyleft Mike Arnautov 1990-2007.
 *
 * 24 May 07   Stuart Munro    Added check for _MSC_EXTENSIONS.
 *                             Also define __STDC__ explicitly as 1.
 * 14 May 07   MLA             Split off from adv00.c (M$ sucks!)
 */
 
#if (defined(__cplusplus) || defined(_MSC_EXTENSIONS)) && !defined(__STDC__)
#  define __STDC__ 1
#endif

#include <stdio.h>
#include <string.h>

#define ADV01
#include "adv1.h"

#ifdef __STDC__
extern void outchar (int);
#else
extern void outchar ();
#endif

#define PRINTF(X)    { char *ptr = X; while (*ptr) outchar(*ptr++); }

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef GLK
#ifdef _WIN32

char* arglist[1] = { "" };
extern char **argv;
extern int argc;

int winglk_startup_code(const char* cmdline)
{
   char name[80];
   char *nptr = name;
   char *cptr = GAMEID;
   
   while (isalnum (*cptr) && (nptr - name) < 78)
      *nptr++ = *cptr++;
   *nptr = '\0';
   winglk_app_set_name(name);
   winglk_window_set_title(GAMEID);
   argc = 1;
   argv = arglist;
   return 1;
}
/* Entry point for all Glk applications */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  /* Attempt to initialise Glk */
  if (InitGlk(0x00000601) == 0)
    exit(0);

  /* Call the Windows specific initialization routine */
  if (winglk_startup_code(lpCmdLine) != 0)
  {
/* Run the application */
    glk_main();

/* There is no return from this routine */
    glk_exit();
  }

  return 0;
}
#endif /* _WIN32 */
#endif /* GLK */

/*===========================================================*/

#if (defined(MSDOS) || defined (_WIN32)) && !defined(DJGPP)

#if !defined(NO_SLOW) && !defined(READLINE) && !defined(GLK)
#ifdef __STDC__
void my_usleep (int delay)
#else
void my_usleep (delay)
int delay;
#endif
{ SleepEx(delay, 0); return; }
#endif /* SLOW */
#endif /* MSDOS || WIN32 || DJGPP */

/*===========================================================*/

#if (!defined(MSDOS) && !defined(_WIN32)) || defined (DJGPP)
#include <dirent.h>
#endif

#ifdef __STDC__
int list_saved (int action, char *last_name)
#else
int list_saved (action, last_name)
int action;
char *last_name;
#endif
{
   int cnt = 0;
   char buf[64];
#if (defined(MSDOS) || defined(_WIN32)) && !defined(DJGPP)
   WIN32_FIND_DATA wfd;
   HANDLE hFind; 
#else
   DIR *dp;
   struct dirent *de;
#endif
   char *sfx;
   *(buf + 63) = '\0';

#if (defined(MSDOS) || defined(_WIN32)) && !defined(DJGPP)
   if ((hFind = FindFirstFile ("*.adv", &wfd)) == INVALID_HANDLE_VALUE)
#else
   if ((dp = opendir(".")) == NULL)
#endif
      return (0);

   while (1)
   {
#if (defined(MSDOS) || defined(_WIN32)) && !defined(DJGPP)
      if (cnt) 
      {
         if (FindNextFile(hFind, &wfd) == 0)
            break;
      }
      strncpy(buf, wfd.cFileName, 63);
#else
      if ((de = readdir(dp)) == NULL)
         break;
      strncpy (buf, de->d_name, 63);
#endif
      if (*buf != '.' &&
         strcmp (sfx = buf + strlen(buf) - 4, ".adv") == 0)
      {
         *sfx = '\0';
         if (action)
         {
            if (cnt) PRINTF (", ")
            PRINTF (buf)
         }
         if (last_name && cnt == 0)
            strcpy (last_name, buf);
         cnt++;
      }
   }
#if (defined(MSDOS) || defined(_WIN32)) && !defined(DJGPP)
      FindClose(hFind);
#else
      closedir (dp);
#endif

   if (cnt == 0) return (0);
   if (action) PRINTF (".\n")
   return (cnt);
}

/**********************************************************************/

