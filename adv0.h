/* adv00.c: A-code kernel - copyright Mike Arnautov 1990-2017, licensed
 * under GPL (version 3 or later) or the Modified BSD Licence, whichever
 * is asserted by the supplied LICENCE file.
 *
 * 04 Apr 16   MLA             Added loop, to replace setjmp/longjmp.
 * 03 Mar 16   MLA             Removed non-ANSI C support.
 * 24 Feb 16   MLA             Moved more stuff in from adv00.c.
 * 05 Jan 15   MLA             Moved special char definitions from adv00.c.
 *                             Added html_ok as extern for use in adv01.c.
 * 22 Dec 14   BTB             Added IOS.
 * 24 May 07   Stuart Munro    Added check for _MSC_EXTENSIONS.
 *                             Also defined __STDC__ explicitly as 1.
 * 01 May 07   Stuart Munro    Bug: Added STDC definition of procs[]().
 */

#if defined(MSDOS)||defined(WIN32)||defined(_WIN32)||defined(__WIN32)||defined (_WIN32_)||defined(__WIN32__)
#  define WINDOWS 1
#  define UNIX 0
#  define OSX 0
#else
#  if defined(__MACH__) || defined(XCODE) || defined(IOS)
#     define WINDOWS 0
#     define UNIX 1
#     define OSX 1
#  else
#     if defined(__unix__) || defined(__linux__)
#        define WINDOWS 0
#        define UNIX 1
#        define OSX 0
#     endif
#  endif
#endif

/* HTTP can only be defined internally! */

#ifdef HTTP
#  undef HTTP
#endif

/* Javascript requires ADVLIB */

#ifdef JS
#  undef JS
#  define JS 1
#  ifndef ADVLIB
#    define ADVLIB
#  endif
#else
#  define JS 0
#endif


/* QT requires ADVLIB */

#ifdef QT
#  undef QT
#  define QT 1
#  ifndef ADVLIB
#    define ADVLIB
#  endif
#else
#  define QT 0
#endif

/* IOS needs ADVLIB and its own header file */

#ifdef IOS
#  include "ios.h"
#  ifndef ADVLIB
#    define ADVLIB
#  endif
#endif

/* CGI can be a compilation symbol. It is one of the four key symbols 
 * to be always defined as 0 or non-zero. It is kind of "external" ADVLIB.
 */
#ifdef TURN         /* CGI symbol is deprecated */
#  ifndef CGI
#    define CGI
#  endif /* CGI */
#endif /* TURN */
#ifdef CGI
#  undef CGI
#  define CGI 3
#  ifndef ADVLIB    /* Probably not necessary any longer */
#    define ADVLIB
#  endif
#else
#  define CGI 0
#endif /* CGI */

/* Now make sure that the other three key symbols (ADVLIB, CONSOLE and HTTP)
 * are defined as 0 or not 0 as appropriate. Also deal with sub-type symbols.
 * ADVLIB and CONSOLE can be a compilation symbols. HTTP cannot be. Actual
 * values must be unique and are assigned as follows:
 *   
 * HTTP       1
 * CONSOLE    2
 * CGI        3
 * ADVLIB     4
 */
#ifdef ADVLIB
#  undef ADVLIB
#  if CGI               /* Careful! CGI may already be defined a 0 */
#    define ADVLIB 0
#else
#    define ADVLIB 4
#  endif /* CGI */
#  ifndef NO_READLINE
#    define NO_READLINE
#  endif
#  ifdef CONSOLE
#    undef CONSOLE
#  endif
#  define CONSOLE   0
#  define HTTP      0
#else
#  define ADVLIB 0
#  define CGI    0
#  ifdef CONSOLE
#    undef CONSOLE
#    define CONSOLE 2
#    define HTTP    0
#  else /* !CONSOLE */
#    define CONSOLE 2
#    define HTTP    1
#    include <fcntl.h>
#    define HTTP_HEADER \
   "HTTP/1.0 200 OK\n" \
   "Host: localhost\n" \
   "Server: A-code/1.1\n" \
   "Cache-Control: no-store\n" \
   "Content-Type: text/html\n" \
   "Content-Length: "
#  endif /* CONSOLE */
#endif /* ADVLIB */

/* The mode variable may have the value of the current mode (1 to 4), or
 * (for CGI and ADVLIB) one of the following:
 */
#  define STARTGAME   5
#  define HAVECMD     6
#  define NEEDCMD     7
#  define LOADGAME    8
#  define RESUMEGAME  9
#  define LISTSAVES  10
#  define GAMEINFO   11

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef NO_UNISTD
#   if WINDOWS && !defined(MSDOS)
#      define unlink _unlink
#   else /* !WINDOWS */
       int unlink(char *);
#   endif /* WINDOWS */
#else
#  include <unistd.h>
#endif

#define SW_START     '\377'
#define SW_BREAK     '\376'
#define HOLDER       '\375'
#define IGNORE_EOL   '\373'
#define NEST_TEXT    '\372'
#define QUOTE_START  '\371'
#define TAG_START    '\370'
#define TAG_END      '\367'
#define NBSP         '\366'
#define BLOCK_START  '\365'
#define BLOCK_END    '\364'
#define CENTRE_START '\363'
#if STYLE >= 10
#  ifdef DWARVEN
#     define DWARVISH  '\362'
#  endif /* DWARVEN */
#  define VHOLDER      '\361'
#endif /* STYLE */
#define PARA_START     '\360'
#define PARA_END       '\357'

#ifdef FILE
#  undef FILE
#endif

extern void say (int key, int what, int qualifier);
extern int query (int textref);
extern void cgiquery (int textref, int qid);
extern int special (int key, int *var);
extern int ishere (int l1, int l2, int l3);
extern int isat (int l1, int l2, int l3, int l4);
extern int isnear (int l1, int l2, int l3);
extern void apport (int l1, int l2);
extern void set (char t1, int v1, char t2, int v2, int *lv, short *lb);
extern void lda (int l1, int l2);
extern void eval (int l1, int l2);
extern void deposit (int l1, int l2);
extern void locate (int l1, int l2);
extern int levar (int l1, int *l2, short *l3);
extern int evar (int l1);
extern short *bitword (int a1);
extern void lbitmod (int a0, char a1, int a2, int a3, int *a4, short *a5);
extern void bitmod (char a1, int a2, int a3);
extern int lbitest (int a1, int a2, int *a3, short *a4);
extern int bitest (int a1, int a2);
extern void outchar (char text_char);
#ifdef READLINE
   extern char *outline 
      (char *addr, int char_count, int break_count, int fill, int terminate);
#else /* ! READLINE */
   extern char *outline (char *addr, int char_count, int break_count, int fill);
#endif /* READLINE */
extern void finita (void);
extern int irand (int less_then);
extern int have (int l1, int l2, int l3);
extern void flush_command (void);
extern void input (int textref);
extern void default_to (int key, int place, int type);
extern void voc (int word, int what, int test, int text);
extern int anyof (int first, ...);
extern int keyword (int first, ...);
extern void move (int a1, int a2, ...);
extern void tie (int text, int holder);
extern int jrand (int limit);
extern void glue_text (void);
extern int randsel (int, ...);
extern void verbatim (int);
extern int memstore (int);
extern int test (char *);
extern void undo (void);
extern void redo (void);
extern void show_data (void);
extern int http_in (void);
extern int http_out (void);
extern void http_init (void);
extern int (*procs[])(void);
extern void pcall (int);
extern int typed (char *);
extern void svar (int, int *);
extern int getloc (int);
extern void browser_write (char *);
extern int browser_read (char *, int);
extern void invoke_browser (char *, int);
extern char *make_header (char *);
extern void send_null (void);
extern void send_page (void);
extern void input_store(int, int *);
extern void zap_text(void);
#ifdef __WIN32
extern void my_usleep (int);
#endif /* __WIN32 */
#ifdef OSX
extern void shutterm (int);
#endif /* OSX */

extern int *value;
extern int *location;
extern short *objbits;
extern short *placebits;
extern short *varbits;
#define AND "and"
#define THEN "then"
#include "adv1.h"
#ifdef ALL
extern int value_all;
#endif /* ALL */
extern int html_ok;
extern int loop;
#if ADVLIB
extern int rep;
extern int nrep;
#endif /* ADVLIB */
