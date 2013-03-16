/* adv01.c: A-code kernel - copyleft Mike Arnautov 1990-2013.
 *
 * 10 Mar 13   MLA             Added MSDOS overrides.
 * 07 Mar 13   MLA             Bug: If FILE defined, undef it!
 * 03 Mar 13   MLA             bug: include arpa/inet.h
 *                             Bug: don't list game in progres on Windows!
 * 11 Nov 12   MLA             Bug: Fixed UNUX (sic.) typo!
 * 08 Nov 12   MLA             Use 127.0.0.1 instead of INADDR_ANY.
 * 03 Nov 12   MLA             Timout handling now done through conf[].
 * 14 Dec 11   MLA             All sockets code now in adv01, due
 *                             to Windows version now using them too.
 * 01 Apr 10   MLA             Added make_copy functionality.
 * 21 Jul 09   MLA             Allow for GNU automake builds.
 * 13 Feb 09   MLA             Don't need process_saved for styles < 11.
 * 24 May 07   Stuart Munro    Added check for _MSC_EXTENSIONS.
 *                             Also define __STDC__ explicitly as 1.
 * 14 May 07   MLA             Split off from adv00.c (M$ sucks!)
 */
 
#ifdef FILE
#  undef FILE
#endif

#ifdef MSDOS
#  ifndef CONSOLE
#     define CONSOLE
#  endif
#  ifndef NO_READLINE
#     define NO_READLINE
#  endif
#  ifndef NO_SLOW
#     define NO_SLOW
#  endif
#endif

#if defined(CONSOLE)&&defined(BROWSER)
#  undef BROWSER
#endif
#if !defined(MSDOS)&&(defined(WIN32)||defined(_WIN32)||defined(__WIN32)||defined (_WIN32_)||defined(__WIN32__))
#  define WINDOWS 1
#  define UNIX 0
#  define MACOS 0
#else
#  define WINDOWS 0
#  define UNIX 1
#  define MACOS 0
#  if defined(_MACH_)
#     undef MACOS
#     define MACOS 1
#  endif
#endif

#if (defined(__cplusplus) || defined(_MSC_EXTENSIONS)) && !defined(__STDC__)
#  define __STDC__ 1
#endif

#ifdef CONSOLE
#  ifdef BROWSER
#     undef BROWSER
#  endif
#else
#  define BROWSER
#endif

#if defined(HAVE_CONFIG_H)
#  include "config.h"
#  if defined (HAVE_STRING_H)
#     include <string.h>
#  else /* ! HAVE_STRING_H */
#     if defined(HAVE_STRINGS_H)
#        include <strings.h>
#     endif /* HAVE_STRINGS_H */
#  endif /* HAVE_STRING_H */
#  if defined(HAVE_STDLIB_H)
#     include <stdlib.h>
#  endif /* HAVE_STDLIB_H */
#  if defined (HAVE_SYS_STAT_H)
#     include <sys/stat.h>
#  endif /* HAVE_SYS_STAT_H */
#  if defined (HAVE_SYS_TYPES_H)
#     include <sys/types.h>
#  endif /* HAVE_SYS_TYPES_H */
#  if defined(HAVE_UNISTD_H)
#     include <unistd.h>
#  else /* ! HAVE_UNISTD_H */
#     if WINDOWS
#        define unlink _unlink
#     else /* !WINDOWS */
         int unlink(char *);
#     endif /* WINDOWS */
#  endif /* HAVE_UNISTD_H */
#else /* ! HAVE_CONFIG_H */
#  include <string.h>
#  include <stdlib.h>
#  if defined(HAVE_UNISTD_H)
#     include <unistd.h>
#  else
#     if WINDOWS
#        define unlink _unlink
#     else /* !WINDOWS */
         int unlink(char *);
#     endif /* WINDOWS */
#  endif
#  include <sys/types.h>
#  include <sys/stat.h>
#  include <fcntl.h>
#endif /* HAVE_CONFIG_H */
#include <time.h>

#include "adv0.h"
#define ADV01
#include "adv1.h"

#define PRINTF(X)    { char *ptr = X; while (*ptr) outchar(*ptr++); }


#if WINDOWS
#  include <windows.h>
#endif /* WINDOWS */

#ifdef BROWSER
#  if WINDOWS
#     include <winsock2.h>
#     include <ws2tcpip.h>
#     define sclose closesocket
#  else /* !WINDOWS */
#    include <sys/socket.h>
#    include <netinet/in.h>
#    include <arpa/inet.h>
#    include <netdb.h>
#    define sclose close
#  endif /* WINDOWS */
#endif

/*===========================================================*/

#if !defined(NO_SLOW) && WINDOWS
#ifdef __STDC__
void my_usleep (int delay)
#else
void my_usleep (delay)
int delay;
#endif
{ SleepEx(delay, 0); return; }
#endif /* !NO_SLOW && WINDOWS */

/*===========================================================*/

#if STYLE > 11

#if WINDOWS
#  define SEP '\\'
#else
#  define SEP '/'
#endif

#if !WINDOWS
#include <dirent.h>
#endif /* !WINDOWS */
#include <stdio.h>

#ifdef __STDC__
void make_copy (char *srcdir, char *name, char *sfx)
#else
void make_copy (srcdir, name, sfx)
char *srcdir;
char *name;
char *sfx;
#endif
{
   char path [128];
   FILE *infile;
   FILE *outfile;
   int c;
   
   sprintf (path, "%s%c%s.%s", srcdir, SEP, name, sfx);
   if ((infile = fopen (path, "rb")) == NULL) return;
   sprintf (path, "%s.%s", name, sfx);
   if ((outfile = fopen (path, "wb")) == NULL)
   {
      fclose (infile);
      return;
   }
   while ((c = fgetc (infile)) != EOF)
      fputc (c, outfile);
   fclose (infile);
   fclose (outfile);
}

/*====================================================================*/

#ifdef __STDC__
int process_saved (int action, char *name)
#else
int process_saved (action, name)
int action;
char *name;
#endif
{
   int cnt = 0;
   char buf[64];
#if WINDOWS
   WIN32_FIND_DATA wfd;
   HANDLE hFind; 
#else /* !WINDOWS */
   DIR *dp;
   struct dirent *de;
#endif /* WINDOWS */
   char *sfx;
   *(buf + 63) = '\0';

#if WINDOWS
   if (action < 1 && strlen (name) > 57)
      return (0);
   sprintf (buf, "%s\\*.adv", action >= 0 ? "." : name);
   if ((hFind = FindFirstFile (buf, &wfd)) == INVALID_HANDLE_VALUE)
#else /* !WINDOWS */
   if ((dp = opendir(action >= 0 ? "." : name)) == NULL)
#endif /* WINDOWS */
      return (0);

   while (1)
   {
#if WINDOWS
      if (cnt) 
      {
         if (FindNextFile(hFind, &wfd) == 0)
            break;
      }
      strncpy(buf, wfd.cFileName, 63);
      if (*buf == '.' || *buf == '_' ||
         strcmp (sfx = buf + strlen(buf) - 4, ".adv") != 0)
            continue;
#else /* !WINDOWS */
      if ((de = readdir(dp)) == NULL)
         break;
      strncpy (buf, de->d_name, 63);
      if (*buf == '.' ||
         strcmp (sfx = buf + strlen(buf) - 4, ".adv") != 0)
            continue;
#endif /* WINDOWS */
      if (action < 0)
      {
         struct stat stat_buf;
         if (stat (buf, &stat_buf) == -1)
         {
            *sfx = '\0';
            make_copy (name, buf, "adv");
            make_copy (name, buf, "adh");
         }
      }
      else 
      {
         *sfx = '\0';
         if (action > 0)
         {
            if (cnt) PRINTF (", ")
            PRINTF (buf)
         }
         else if (name && cnt == 0)
            strcpy (name, buf);
         cnt++;
      }
   }
#if WINDOWS
      FindClose(hFind);
#else /* !WINDOWS */
      closedir (dp);
#endif /* WINDOWS */

   if (cnt == 0) return (0);
   if (action > 0) PRINTF (".\n");
   return (cnt);
}

#endif /* STYLE */

/*====================================================================*/
#ifdef BROWSER

int lsock = 0;
int wsock = 0;
int port = 1978;

char *utf8 = "20 21!22\"23#25%26&27'28(29)2A*2B+2C,2F/3A:3B;3D=3F?40@5B[5D]";

/*====================================================================*/
/* Sets up listener socket lsock for browser operation.
 */
void set_up_listener (void)
{
   int one = 1;              /* Needed by setsockopt */
   struct protoent *pf;      /* Protocol family pointer */
   struct sockaddr_in ladr;  /* Local server address structure */
   int pcnt = 0;

   memset ((char *)&ladr, 0, sizeof(ladr));
   ladr.sin_family = AF_INET;
   ladr.sin_addr.s_addr = inet_addr("127.0.0.1");

   if ((pf = getprotobyname ("tcp")) == NULL)
   {
      fprintf (stderr, "Failed to find protocol TCP!\n");
      exit (-1);
   }

   if ((lsock = socket (AF_INET, SOCK_STREAM, pf->p_proto)) < 0)
   {
      perror("");
      fprintf (stderr, "Failed to create listennig socket!\n");
      exit (-1);
   }

   setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, 
      (void *)&one, sizeof(int));

   while (1)
   {
      ladr.sin_port = htons (port);
      if (bind (lsock, (struct sockaddr *)&ladr, sizeof(ladr)) == 0)
         break;
      port++;
      pcnt++;
      if (pcnt == 100)
      {       
         fprintf (stderr,"Failed to bind listening socket!\n");
         exit (-1);
      }
   }

   if (listen (lsock, 10) < 0)
   {
      fprintf (stderr,"Failed to set up listener!\n");
      exit (-1);
   }
}
/*====================================================================*/
/* Send the assembled response to the browser in 1KB chunks. (Possibly
 * unnecessary to split it like that these days.)
 */
void browser_write (char *cptr)
{
   int size;
   int len = 1024;
   
#ifdef DEBUG
   printf ("=== Entering %s\n", "browser_write"); 
#endif /* DEBUG */
   cptr = make_header (cptr);
   size = strlen (cptr);
   while (size > 0)
   {
      if (size < len)
         len = size;
      send (wsock, cptr, len, 0);
      cptr += len;
      size -= len;
   }
   sclose (wsock);
   wsock = 0;
#ifdef DEBUG
   printf ("=== Exiting %s\n", "browser_write"); 
#endif /* DEBUG */
}
/*====================================================================*/
/* Wait for the browser to call and either respond (to a keep-alive
 * request), or extract and return the player's command.
 */
int browser_read (char *command, int time_limit)
{
   int len;
   char combuf[4096];
   char *cptr = combuf;
   char *aptr;
   int retval = 'N';
   int lchar = ' ';
   int adrlen;               /* Length of socket address */
   struct sockaddr_in radr;  /* Remote client address structure */
   fd_set screen;
   struct timeval timeout;
   int ready;
   
#ifdef DEBUG
   printf ("=== Entering %s\n", "browser_read"); 
#endif /* DEBUG */
   FD_ZERO(&screen);
   FD_SET(lsock, &screen);
   while (1)
   {
      timeout.tv_sec = time_limit;
      timeout.tv_usec = 0;
      ready = select (FD_SETSIZE, &screen,
        (fd_set *) 0, (fd_set *) 0, &timeout);
      if (!ready)
      {
        fprintf (stderr, "*** No response from browser! ***\n");
        exit (1);
      }
      adrlen = sizeof(radr);
      if (wsock)
      {
         sclose (wsock);
         wsock = 0;
      }
      if ((wsock = accept (lsock, (struct sockaddr *)&radr, 
                                  (socklen_t *)&adrlen)) < 0)
      {
         fprintf(stderr, "Failed to accept incoming call!\n");
         exit (-1);
      }
      
      cptr = combuf;
      while (1)
      {
         len = recv (wsock, cptr, sizeof(combuf) - 1, 0);
         *(cptr + len) = '\0';
         aptr = cptr + 1;
         lchar = *cptr;
         cptr += len;
         while (aptr < cptr)
         {
            if (lchar == '\n' && *aptr == '\n')
            {
               len = 0;
               break;
            }
            if (*aptr != '\r')
               lchar = *aptr;
            aptr++;
         }
         if (len == 0)
            break;
      }
      if (strstr (combuf, "IE 5.0"))
      {
         fprintf (stderr,
            "*ERROR* Sorry, this setup does not work with IE 5.0.\n");
         exit (1);
      }
      if (strncmp (combuf, "GET", 3) != 0)
      {
         sclose (wsock);
         continue;
      }         
      if ((cptr = strstr (combuf, "status=")) != NULL)
      {
         aptr = cptr + 7;
         if (*aptr == '0' && *(aptr + 1) == 'x')
         {
            aptr += 2;
            if (*aptr == 'R' || *aptr == 'S')
               retval = *aptr;
            else
            {
               send_null ();
               continue;
            }
         }
         else
         {
            while (*aptr >= '0' && *aptr <= '9')
               aptr++;
            aptr++;
         }
      }
      if (strstr (combuf, "favicon") != NULL)
      {
         send (wsock, "HTTP/1.0 404 Not found\nContent-Length: 0\n\n", 42, 0);
         sclose (wsock);
         continue;
      }
      break;
   }
   if (command)
   {
      cptr = command;
      while (*aptr != ' ' && *aptr != '\n')
      {
         if (*aptr == '%')
         {
            char *uptr = utf8;
            while (*uptr)
            {
               if (*uptr == *(aptr + 1) && *(uptr + 1) == *(aptr + 2))
               {
                  *cptr++ = *(uptr + 2);
                  aptr += 3;
                  break;
               }
               uptr += 3;
            }
            if (*uptr)
               continue;
         }
         *cptr++ = *aptr;
         aptr++;
      }
      *cptr++ = '\n';
      *cptr = '\0';
   }
#ifdef DEBUG
   printf ("=== Exiting %s: '%s'\n", "browser_read", command); 
#endif /* DEBUG */
   return (retval);
}
/*====================================================================*/
/* Invokes the specified browser.
 */
void invoke_browser (char *exe, int timeout)
{
   char urlbuf [256];
   int rsp = 0;
   int tm = time(NULL) % 10000;

#if WINDOWS
   STARTUPINFO si;
   PROCESS_INFORMATION pi;
   WSADATA wsaData;
   WSAStartup(0x0101, &wsaData);
#endif /* WINDOWS */

#ifdef DEBUG
   printf ("=== Entering %s\n", "invoke_browser"); 
#endif /* DEBUG */

   set_up_listener ();

#if WINDOWS
   sprintf (urlbuf, "%s http://localhost:%d/%d/", exe, port, tm);
   ZeroMemory( &si, sizeof(si) );
   si.cb = sizeof(si);
   ZeroMemory( &pi, sizeof(pi) );
   if (!CreateProcess(NULL, urlbuf, NULL, NULL, 0, 0, NULL, NULL, &si, &pi))
   {
      printf ("*ERROR* Failed to kick off '%s'!\n", urlbuf);
      exit (-1);
   }
#else /* !WINDOWS */
   if (isatty (1)) 
      fputs ("Invoking browser...\n", stderr);
   
   if (fork () == 0)        /* I.e. this is the child process */
   {
      int fd;
      sclose (lsock);
      lsock = 0;
      sprintf (urlbuf, "http://localhost:%d/%d/", port, tm);
      fflush(stdout);
      close (0); close (1); fd = dup(2); close(2);
      execl (exe, exe, urlbuf, (char *)NULL);
      dup(fd); dup (fd);
      printf ("*ERROR* Failed to exec %s!\n", exe);
      exit (1);
   }

#if !defined(DEBUG) && !defined(DIRECT)
/* Daemonize, if necessary */
   if (getppid() != 1)
   {
      int i;
      if (isatty (1))
         fputs ("Daemonising game server...\n", stderr);
      if (fork() > 0) exit (0);  /* Parent process exits */
      setsid ();                 /* New process group */
      close (0); close (1); close (2); /* Close stdin, stdout, stderr */
      i = open ("/dev/null", O_RDWR); dup (i); dup (i); /* Reopen them */
   }
#endif /* ! DEBUG && ! DIRECT*/
#endif /* WINDOWS */

   rsp = browser_read (NULL, timeout); /* Accept initial call (page request?) */
   if (rsp != 'R')
   {
      if (rsp == 'N') send_page();          /* Send the initial page */
      while ((rsp = browser_read (NULL, timeout)) == 'N')
        send_null();
   }
#ifdef DEBUG
   printf ("=== Exiting %s\n", "invoke_browser"); 
#endif /* DEBUG */
}
#endif /* BROWSER */
/**********************************************************************/
