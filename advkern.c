/* advkern.c (adventure) - copyleft Mike Arnautov 1990-2002.
 *
 * 30 Dec 02   MLA        bug: Use arg2 resolution on iterated objects.
 *                        Also added vocabulary search suppression.
 * 22 Dec 02   MLA        Suppress 'More?" if replaying from log.
 *                        Also preserve rseed sequence outside the A-code.
 * 21 Dec 02   MLA        Added isat().
 * 20 Dec 02   MLA        Bug: Allow for ARG1/ARG2 not having bits set to -1!
 * 12 Nov 02   MLA        Added "exec 30" to check for typos.
 * 28 Sep 02   MLA        Undo the fix suppressing end-of-buffer blanks
 *                        if buffer ends on a block end (why was it there???).
 * 13 Jul 02   MLA        Complete re-write of set().
 * 12 Jul 02   MLA        Don't use +1024 flag in have, ishere and isnear.
 * 10 Jul 02   MLA        kludge: Ignore description words ending in 'ing'.
 *                        kludge: Guess whether to capinitial # words.
 * 07 Jul 02   MLA        BUG: Fail memory restore if no memory image!
 * 23 Jun 02   MLA        Added jrand for "true" randomisation.
 * 11 May 02   MLA        Translate matched vocabulary words into Dwarvish too!
 * 14 Apr 02   MLA        Allow comma as command separator.
 *                        Disambiguate abbreviations.
 * 12 Feb 02   MLA        Added 'first' check in parse ().
 * 11 Jan 02   MLA        Added ARG1/ARG2 swap.
 * 05 Jan 02   MLA        Bug: Don't set JUGGLED unless old or new location
 *                        is INHAND!
 * 04 Jan 02   D.Pickton  Bug: Append '\n' to GLK-obtained commands!
 * 18 Dec 01   MLA        Bug: don't use cgi outside #ifdef CGI!
 * 11 Dec 01   D.Kinder   Fixed agrc (sic.) etc typos.
 * 09 Dec 01   MLA        Allowed increasing text counts without
 *                        invalidating old saved games or relaxing checks.
 * 04 Dec 01   MLA        Save old_comline in CGI mode.
 * 27 Nov 01   MLA        Rationalised command line keyword handling. 
 * 25 Nov 01   MLA        Bug: fixed short/long/detail description juggling.
 *                        Added IGNORE_EOL.
 * 19 Nov 01   MLA        Fixed the "More?" query in new output framework.
 * 17 Nov 01   MLA        Simplified in-memory plaintext operation.
 * 10 Nov 01   MLA        New output framework.
 * 07 Nov 01   D.Kinder   Tweaked to work with Visual C++.
 * 06 Nov 01   MLA        Adjusted handling of FULL, BRIEF and
 *                        TERSE for STYLE 1 compatibility.
 * 04 Nov 01   MLA        bug: Use of PLSCLARIFY must be conditional.
 * 03 Nov 01   MLA        Compress multiple LFs into at most two.
 * 02 Nov 01   MLA        Added BADSYNTAX handling;
 * 30 Oct 01   MLA        BUG: Even in STYLE == 1, implicit switches start 
 *                        from 0!
 * 20 Oct 01   MLA        BUG: Don't use AMBIGWORD when STYLE == 1 !
 * 18 Oct 01   MLA        Improved back compatibility with Platt's A-code.
 * 07 Oct 01   MLA        Bug: Fixed orphan handling (abandoning attempts
 *                        to make orphans work across "repeat").
 *                        bug: Wrap on hyphenation too!
 * 05 Aug 01   MLA        Bug: Defaulting sets 'it'.
 * 28 Jul 01   MLA        Bug: Remeber to copy typo stuff for continuations.
 * 24 Jul 01   MLA        BUG: Fixed find_word declaration in compatibility
 *                        mode.
 * 14 Jul 01   MLA        Bug: Apply dwarvish translation to separate command,
 *                        not to the whole command line!
 * 20 May 01   MLA        Bug: fixed new parser. Add scene text only if
 *                        no error.
 * 19 May 01   MLA        bug: Re-wrote parse() due to minor problems.
 *                        Bug: Check entity has flags before accesing a flag.
 *                        BUG: Fake checking the VERB flag.
 * 17 May 01   MLA        Added fake() for FAKECOM.
 * 16 May 01   MLA        Bug: HTML-quote angled brackets!
 * 12 May 01   MLA        Bug: condifionally switch off amatching for ARG2.
 * 06 May 01   MLA        bug: Fixed approximate matching.
 * 02 May 01   MLA        Bug: Fixed yet another "null command" bug. :-(
 * 16 Apr 01   MLA        Fixed zapping save file on initial restore.
 * 30 Mar 01   MLA        Added typo reporting
 * 25 Mar 01   MLA        Added scenery word matching.
 * 15 Mar 01   MLA        Added readline (but it don't work!).
 * 14 Mar 01   MLA        Added approximate matching.
 * 28 Feb 01   MLA        Allowed assigned text type. Added in-text
 *                        dwarvish tag. Added tied text type.
 * 26 Feb 01   MLA        Adjust hlead if not justifying.
 * 25 Feb 01   MLA        Added DWARVEN game/kernel integration.
 * 24 Feb 01   MLA        Added special for checking "do all" status.
 *                        Remapped quotes and underscores to blanks on input.
 * 20 Feb 01   MLA        bug: Fudged around the problem of blocks in switches.
 * 09 Feb 01   MLA        Yet better ANSI compliance!
 * 27 Jan 01   MLA        Replaced decrementing texts with cycling ones.
 * 21 Jan 01   MLA        Bug: if CGI, must use disk for memory save!
 * 12 Jan 01   MLA        Added random and inc/decrementing texts.
 *                        Allowed setting value of texts.
 * 07 Jan 01   MLA        Added CENTRE_START.
 * 05 Jan 01   MLA        Adapted to cgi-bin use.
 * 08 Dec 00   MLA        Save/restore player's verbatim input too!
 * 05 Dec 00   MLA        If special context, accept null input.
 * 21 Oct 00   MLA        Default creen size & margin can be specified at
 *                        compile time. Also changed command line format
 *                        to N[xN[-N]].
 * 30 Sep 00   MLA        Allow for no output between two prompts.
 *                        Added -b command line option. On Unix/Windows
 *                        dbs first sought in the executable's directory.
 * 18 Sep 00   MLA        Added screen length. Added command line parsing.
 * 17 Sep 00   MLA        Fixed justifying code. De-wired screen width
 *                        and offset.
 * 17 Dec 99   MLA        Added block handling.
 * 16 Sep 99   Jon Skeet  HERE and THERE need initialising.
 * 12 Dec 99   MLA        Ignore embedded HTML tags. Allow for "hard" spaces
 * 13 Oct 99   MLA        Allowed for Cygwin's strange sign promotion.
 * 30 Aug 99   MLA        Allowed text nesting.
 * 09 Aug 99   MLA        Don't give strcmp a NULL for an arg!
 *                        And don't search vocabulary for null words!
 * 06 Aug 99   MLA        Merged with chopped down advcust.c
 * 05 Aug 99   MLA        Don't close log file twice! (Linux don't like it.)
 *                        Also, added dwarven mode.
 * 29 Jul 99   MLA        Added "to exit press enter" for MS O/S.
 * 24 Jul 99   MLA        Eliminated spurious warnings.
 * 10 Apr 99   MLA        Strengthened encryption, added virgin mode,
 *                        checksummed dumpfiles.
 * 05 Apr 99   MLA        Added voc().
 * 01 Apr 94   MLA        Added dynamic log file handling.
 * 26 Mar 94   MLA        Fixed move() a2 handling.
 * 14 Mar 94   MLA        MOVED, JUGGLED and SCHIZOID now truly optional.
 * 16 Feb 94   MLA        Merged 10.04 with the experimental 11.00,
 *                        creating 10.05.
 * 12 Dec 91   MLA        The ? prompt overridden by pending text.
 *                        input() takes an optional argument.
 * 10 Mar 91   MLA        Added flush_command ().
 * 09 Mar 91   MLA        Stopped SCHIZOID confusion in INHAND.
 * 06 Mar 91   MLA        Allowed extra minute on checking restore lag.
 *                        Also, do own lowercasing to avoid trouble.
 * 26 Feb 91   MLA        Use flagged return instead of exit.
 * 23 Feb 91   MLA        Allowed variable bit fields.
 * 22 Feb 91   MLA        Corrected parser response to wrong syntax. 
 * 29 Dec 90   MLA        Reduced disk accesses via "locate buffers".
 * 27 Dec 90   MLA        Allowed flags and states with IFHERE/HAVE/NEAR.
 * 14 Dec 90   MLA        Allowed null keyword lists for (S)MOVE.
 * 12 Dec 90   MLA        New minor directive QUIP.
 * 11 Dec 90   MLA        Variable keyword counts for MOVE and SMOVE.
 * 25 Nov 90   MLA        Outline now checks for zero break_count.
 * 23 Nov 90   MLA        VMS compilation. Also, "unvoided" declarations
 *                        of advcpy and srand - Prime's CI -DEBUG didn't
 *                        like them being cast to voids subsequently.
 * 22 Nov 90   MLA        Changed 'here' and 'near' to 'ishere' and
 *                        'isnear' to avoid MSC clashes.
 * 17 Nov 90   MLA        Introduced NOVARARGS compilation symbol
 *                        to cope with a nasty Ultrix compiler.
 * 15 Sep 90   MLA        Initial coding.
 *
 */

#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifdef NEED_UNISTD
#include <unistd.h>
#endif

/* extern void *malloc(); */

#if defined(unix) || defined(linux) || defined(vms) || defined(__50SERIES) || defined (_WIN32) || defined (__CYGWIN__)
#  define MEMORY
#else
#  ifndef MSDOS
#     define MSDOS
#  endif /* MSDOS */
#endif

#if defined(MSDOS) && defined(MEMORY)
#  undef MEMORY
#endif

#if defined(unix) || defined(__CYGWIN__)
#  define SEP '/'
#else
#  if defined(MSDOS) || defined(_WIN32)
#     define SEP '\\'
#  else
#     ifdef __50SERIES
#        define SEP '>'
#     else
#        define SEP '?'
#     endif
#  endif
#endif

#ifdef __50SERIES
   extern int time ();
#  define RMODE "i"
#  define WMODE "o"
#  define unlink delete
#else /* not __50SERIES */
#  ifdef vms
#     define unlink delete
#     include <time.h>
#  else /* not vms */
#     include <sys/types.h>
#     include <sys/stat.h>
#  endif /* vms */
/*   extern time_t time(); */
#  define RMODE "rb"
#  define WMODE "wb"
#endif /* __50SERIES */
/*
 * extern char *strncpy ();
 * extern void exit ();
 */
#ifdef __STDC__
void shift_up (char *);
void shift_down (char *, int);
#else
void shift_up();
void shift_down();
#endif
#ifdef READLINE
#  include <termcap.h>
#  include <readline.h>
#  include <history.h>
#endif

FILE *text_file;
FILE *rape_file;
FILE *log_file = NULL;
char log_name [32];
#ifdef LOG
int log_wanted = 1;
#else
int log_wanted = 0;
#endif

FILE *com_file = NULL;
char *com_name = NULL;
char *dump_name = NULL;

#include "advkern.h"

#define SW_START     '\377'
#define SW_BREAK     '\376'
#define HOLDER       '\375'
#define IGNORE_EOL   '\373'
#if STYLE >= 10
#  define NEST_TEXT    '\372'
#  define NEST_VAR     '\371'
#  define TAG_START    '\370'
#  define TAG_END      '\367'
#  define NBSP         '\366'
#  define BLOCK_START  '\365'
#  define BLOCK_END    '\364'
#  define CENTRE_START '\363'
#  ifdef DWARVEN
#     define DWARVISH     '\362'
#  endif /* DWARVEN */
#endif /* STYLE */

#ifdef GLK
#  define putchar(X) glk_put_char(X)
#endif

#define PUTCHAR(X)   putchar(X);  if (log_file) (void)fputc(X,log_file)

/* The below text for BLOCK_END is a *horrible* fudge-around. The problem
 * is that BLOCK_END may get placed beyond the end of the appropriate
 * switch component! The proper solution is to re-do text parsing like
 * *COMPLETELY* (probably making it recursive). Hence the fudge!
 */
#ifdef BLOCK_END
#define PUTCHARA(X)  if (*X != BLOCK_END && *X != IGNORE_EOL) { \
                     if (log_file) (void)fputc(*X,log_file); \
                     (void)putchar(*X++);} else X++
#else
#define PUTCHARA(X)  if (*X != IGNORE_EOL) { \
                     if (log_file) (void)fputc(*X,log_file); \
                     (void)putchar(*X++);} else X++
#endif /* BLOCK_END */

void outbuf (int);
int value_all;
jmp_buf loop_back;
char data_file [128];
char *dbs_dir = NULL;
char exec [128];
char virgin;
int value [LTEXT]; /* Was LVARIABLE */
int location [LOBJECT + 1];
short objbits [OBJSIZE * (LOBJECT - FOBJECT + 1)];
short placebits [PLACESIZE * (LPLACE - FPLACE + 1)];
short varbits [VARSIZE * (LVARIABLE - FVERB + 1)];
char comline [161] = "\n";
char old_comline [161] = "\n";
char raw_comline [161];
int arg1, arg2;
int orphan;
int qvals [5];
int *qtext = &qvals[0];
int *qstat = &qvals [1];
int *qarg1 = &qvals [2];
int *qarg2 = &qvals [3];
int *qcon = &qvals [4];
#define WORDSIZE 20
char qwords [5 * WORDSIZE];
char *arg1_word = qwords;
char *arg2_word = qwords + WORDSIZE;
char *orphan_word = qwords + 2 * WORDSIZE;
char *qargw1 = qwords + 3 * WORDSIZE;
char *qargw2 = qwords + 4 * WORDSIZE;
char temp_word [WORDSIZE];
#if STYLE >= 11
   #define ORG1 -1
   #define ORG2 -2
   char orig1 [WORDSIZE];
   char orig2 [WORDSIZE];
   long ovoc1, ovoc2;
   int olen1, olen2;
#endif
long rseed;
long mainseed = 0;
int amatch = 1;
#ifdef DWARVEN
   int extra_dwarvish = 0;
#endif
#if defined(JUSTIFY) || STYLE == 10
   int justify = 1;
#else
   int justify = 0;
#endif
#if defined(COMPRESS) || STYLE == 1
   int compress = 1;
#else
   int compress = 0;
#endif
#if defined(PAUSE) || defined(MSDOS) || defined(_WIN32)
   int end_pause = 1;
#else
   int end_pause = 0;
#endif
#ifdef CONTEXT
   int cgi = 0;
   char cgicom [160];
   char *cgi_name = ".C.adv";
#endif

#include "autod1.h"
#include "autod3.h"
#include "autod4.h"
#include "autod2.h"
#include "autod0.h"

#ifdef AGAIN
   int fresh_line = 1;
#endif /* AGAIN */

#ifdef MEMORY
#  ifdef BUFFERS
#     undef BUFFERS
#  endif /* BUFFERS */
   char text [TEXT_BYTES];
#else /* not MEMORY */
#  define TEXT_CHUNK 1024
#  ifdef MSDOS
#     ifdef BUFFERS
#        if BUFFERS == 0
#           undef BUFFERS
#        endif /* BUFFERS == 0 */
#     else /* !BUFFERS */
#        define BUFFERS 31
#     endif /* BUFFERS */
#  endif /* MSDOS */
#  ifdef BUFFERS
      char text [BUFFERS * TEXT_CHUNK];
      long chunk_start [BUFFERS];
      long chunk_end [BUFFERS];
      long chunk_age [BUFFERS];
#  else /* not BUFFERS */
      char text [TEXT_CHUNK];
      long chunk_start;
      long chunk_end;
#  endif /* BUFFERS */
#endif /* MEMORY */

char *tp [100];
char separator [100];
short tindex;
#ifdef GLK
   short Screen = 32767;
   short Linlen = 32767;
   short Margin = 0;
#else
#if defined(HEIGHT) && (HEIGHT > 5 || HEIGHT == 0)
   short Screen = HEIGHT;
#else
   short Screen = 24;
#endif
#if defined(WIDTH) && (WIDTH > 15 || WIDTH == 0)
   short Linlen = WIDTH;
#else
   short Linlen = 80;
#endif
#if defined(MARGIN) && MARGIN >= 0
   short Margin = MARGIN;
#else
   short Margin = 1;
#endif
#endif
short Maxlen;
long ta;
long locate_faults;
long locate_demands;
#ifdef LOC_STATS
   long old_faults;
   long old_demands;
#endif /* LOC_STATS */
char *text_buf;
int text_buf_len = 4096;
#if STYLE >= 11
   short *word_buf = NULL;
   int upcase = 1;
#endif
char *lptr;
int text_len = 0;
int location_all;
int type_all;
char title [16];
int titlen;
int quitting;
int eol_count = 0;
#ifdef TAG_START
   int ignore_tag = 0;
#endif /* TAG_START */
char *lp;

#define PRINTF(X)    { char *ptr = X; while (*ptr) outchar(*ptr++); }
/*                   strncpy(lptr,X,text_buf_len-(lptr-text_buf)); \
                     text_len += strlen(X) */
#define PRINTF2(X,Y) printf(X,Y); if (log_file) (void)fprintf(log_file,X,Y);
#define CHKSUM(X,Y)  for (cptr=(char *)X,cnt=1;cnt<=Y;cnt++,cptr++) \
                     {chksum+=(*cptr+cnt)*(((long)(*cptr)+cnt)<<4)+Y; \
                     chksum&=07777777777L;} 
#ifdef GLK
#  include "glk.h"
   static winid_t mainwin = NULL;
#  ifdef __STDC__
void glkgets (char *buf, int buflen)
#  else
void glkgets (buf, buflen)
   char *buf;
   int buflen;
#  endif
{
   int gotline = 0;
   event_t event;
   
   memset (buf, '\0', buflen);
   glk_request_line_event(mainwin, buf, buflen, 0);
   while (!gotline)
   {
      glk_select(&event);
       
      switch (event.type) 
      {
         case evtype_LineInput:
            gotline = 1;
/* Glk doesn't put a '\n' before the terminating null! */               
            (void) strcat(buf,"\n");
         default:
            break;
      }
   }
}
#endif

#if !defined(NOVARARGS) && defined(__STDC__)
int anyof (int first, ...)
{
    va_list ap;
    int val;

    va_start (ap, first);
    val = first;
    while (val >= 0)
    {
       if (KEY (val))
       {
          va_end (ap);
          return (1);
       }
       val = va_arg (ap, int);
    }
    va_end (ap);
    return (0);
}

int keyword (int first, ...)
{
    va_list ap;
    int val;

    va_start (ap, first);
    val = first;
    while (val >= 0)
    {
       if (!KEY (val))
       {  
          va_end (ap);
          return (0);
       }
       val = va_arg (ap, int);
    }
    va_end (ap);
    return (1);
}
#else /* not (NOVARARGS && __STDC_)*/
#ifdef __STDC__
int anyof (int l0,int l1,int l2,int l3,int l4,int l5,int l6,int l7,
           int l8,int l9,int l10,int l11,int l12,int l13,int l14,int l15)
#else
int anyof (l0,l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15)
int l0,l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15;
#endif
{
   if (l0 == -1) return (0);
   if (KEY (l0)) return (1);
   if (l1 == -1) return (0);
   if (KEY (l1)) return (1);
   if (l2 == -1) return (0);
   if (KEY (l2)) return (1);
   if (l3 == -1) return (0);
   if (KEY (l3)) return (1);
   if (l4 == -1) return (0);
   if (KEY (l4)) return (1);
   if (l5 == -1) return (0);
   if (KEY (l5)) return (1);
   if (l6 == -1) return (0);
   if (KEY (l6)) return (1);
   if (l7 == -1) return (0);
   if (KEY (l7)) return (1);
   if (l8 == -1) return (0);
   if (KEY (l8)) return (1);
   if (l9 == -1) return (0);
   if (KEY (l9)) return (1);
   if (l10 == -1) return (0);
   if (KEY (l10)) return (1);
   if (l11 == -1) return (0);
   if (KEY (l11)) return (1);
   if (l12 == -1) return (0);
   if (KEY (l12)) return (1);
   if (l13 == -1) return (0);
   if (KEY (l13)) return (1);
   if (l14 == -1) return (0);
   if (KEY (l14)) return (1);
   if (l15 == -1) return (0);
   if (KEY (l15)) return (1);
   return (0);
}

#ifdef __STDC__
int keyword (int l0,int l1,int l2,int l3,int l4,int l5,int l6,int l7,
             int l8,int l9,int l10,int l11,int l12,int l13,int l14,int l15)
#else
int keyword (l0,l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15)
int l0,l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15;
#endif
{
   if (l0 == -1) return (1);
   if (!KEY (l0)) return (0);
   if (l1 == -1) return (1);
   if (!KEY (l1)) return (0);
   if (l2 == -1) return (1);
   if (!KEY (l2)) return (0);
   if (l3 == -1) return (1);
   if (!KEY (l3)) return (0);
   if (l4 == -1) return (1);
   if (!KEY (l4)) return (0);
   if (l5 == -1) return (1);
   if (!KEY (l5)) return (0);
   if (l6 == -1) return (1);
   if (!KEY (l6)) return (0);
   if (l7 == -1) return (1);
   if (!KEY (l7)) return (0);
   if (l8 == -1) return (1);
   if (!KEY (l8)) return (0);
   if (l9 == -1) return (1);
   if (!KEY (l9)) return (0);
   if (l10 == -1) return (1);
   if (!KEY (l10)) return (0);
   if (l11 == -1) return (1);
   if (!KEY (l11)) return (0);
   if (l12 == -1) return (1);
   if (!KEY (l12)) return (0);
   if (l13 == -1) return (1);
   if (!KEY (l13)) return (0);
   if (l14 == -1) return (1);
   if (!KEY (l14)) return (0);
   if (l15 == -1) return (1);
   if (!KEY (l15)) return (0);
   return (1);
}
#endif /* NOVARARGS && __STDC__*/

#ifdef __STDC__
int irand (int less_then)
#else
int irand (less_then)
int less_then;
#endif
{
   rseed = (((rseed << 10) + rseed) / 13) & 32767;
   return (rseed % less_then);
}

#ifdef __STDC__
int jrand (int less_then)
#else
int jrand (less_then)
int less_then;
#endif
{
   int rvalue;
   rvalue = (((rseed << 10) + (int) time (NULL)) / 13) & 32767;
   return (rvalue % less_then);
}

#if STYLE >= 11
#define BT_LSIB   -1
#define BT_UP      1
#define BT_RSIB    1
#define BT_BAL     3
#define BT_TXT     4
#define BT_STP  4096
#define BT_SIZE *((unsigned short *)(root + 2))

short *btinit (short *root)
{
   if (root == NULL)
   {
      if ((root = (short *)malloc(BT_STP * sizeof(short))) == NULL)
         return (NULL);
      *root = 3;
      *(root + 1) = 0;
      BT_SIZE = BT_STP;
   }
   else
   {
      if ((root = (short *)realloc 
         (root, (*(root + 2) + BT_STP) * sizeof(short))) == NULL)
            return (NULL);
      BT_SIZE += BT_STP;
   }
   return (root);
}

#ifdef DEBUG
void btshow (short *root, char *text)
{
   short *iptr;

   printf ("Show: %s, free: %hd, root: %hd\n", text, *root, *(root + 1));
   iptr = root + 3;
   while (iptr < root + *root)
   {
      fprintf (stderr, "Offset %d: Up %hd, L %hd, R %hd, B %hd, T: %s\n",
         iptr - root, *(iptr + BT_UP), *(iptr + BT_UP + BT_LSIB), 
            *(iptr + BT_UP + BT_RSIB), *(iptr + BT_BAL), 
               (char *)(iptr + BT_TXT));
      iptr += BT_TXT + 1 + strlen ((char *) (iptr + BT_TXT)) / 2;
   }
}
#endif /* DEBUG */

void btcopy (char *start, int len, short *new_rec)
{
   char *cptr = (char *) (new_rec + BT_TXT);
   while (len--)
      *cptr++ = tolower (*start++);
   *cptr = '\0';
}

int btcompare (char *word, char *cword)
{
   int cchar, wchar;

   while (*word)
   {
      wchar = tolower ((unsigned char) *word++);
      if (!isalpha (wchar))
         return (*cword ? -1 : 0);
      cchar = (unsigned char) *cword++;
      if (wchar != cchar)
         return (wchar > cchar ? 1 : -1);         
   }       
   return (0);
}

void sing_rot (short *root, int parent, int child, int dir)
{
   int gparent = *(root + parent + BT_UP);
   int gchild = *(root + child + BT_UP - dir);
   
   *(root + parent + BT_UP + dir) = *(root + child + BT_UP - dir);
   *(root + child + BT_UP - dir) = parent;
   *(root + parent + BT_BAL) -= *(root + child + BT_BAL);
   *(root + child + BT_BAL) = -(*(root + parent + BT_BAL));
   if (gparent > 0)
      *(root + gparent + BT_UP +
         (*(root + gparent + BT_UP + BT_LSIB) == parent ? BT_LSIB : BT_RSIB)) =
            child;
   else
      *(root + 1) = child;
   *(root + child + BT_UP) = gparent;
   *(root + parent + BT_UP) = child;
   if (gchild)
      *(root + gchild + BT_UP) = parent;
}

void dub_rot (short *root, int parent, int child, int dir)
{
   int gparent = *(root + parent + BT_UP);
   int gchild = *(root + child + BT_UP - dir);

   *(root + child  + BT_UP - dir) = *(root + gchild + BT_UP + dir);
   if (*(root + gchild + BT_UP + dir))
      *(root + *(root + gchild + BT_UP + dir) + BT_UP) = child;
   *(root + parent + BT_UP + dir) = *(root + gchild + BT_UP - dir);
   if (*(root + gchild + BT_UP - dir))
      *(root + *(root + gchild + BT_UP - dir) + BT_UP) = parent;
   *(root + gchild + BT_UP + dir) = child;
   *(root + gchild + BT_UP - dir) = parent;

   if (*(root + gchild + BT_BAL) == *(root + child + BT_BAL))
      *(root + child + BT_BAL) *= -1;
   else
      *(root + child + BT_BAL) = 0;
   if (*(root + gchild + BT_BAL) == *(root + parent + BT_BAL))
      *(root + parent + BT_BAL) *= -1;
   else
      *(root + parent + BT_BAL) = 0;
   *(root + gchild + BT_BAL) = 0;

   *(root + child + BT_UP) = gchild;
   *(root + parent + BT_UP) = gchild;
   *(root + gchild + BT_UP) = gparent;
   if (gparent > 0)
      *(root + gparent + BT_UP +
         (*(root + gparent + BT_UP + BT_LSIB) == parent ? BT_LSIB : BT_RSIB)) =
            gchild;
   else
      *(root + 1) = gchild;
}

short *btadd (short *root, char *word, int len)
{
   int parent = 0;
   int child = *(root + 1);
   int sib;
   int dir;
   char *cptr;
   short *new_rec;
   int reclen = BT_TXT  + 1 + len / 2;

   if (*(root + 1) > 0)
   {
      while (child > 0)
      {
         if ((dir = btcompare (word, (char *)(root + child + BT_TXT))) == 0)
            return (root);
         parent = child;
         child = *(root + child + BT_UP + dir);
      }
   }
   if (*root + reclen > BT_SIZE && 
      (BT_SIZE > 65535L - reclen || (root = btinit (root)) == NULL))
         return (NULL);
   new_rec = root + (child = *root);
   *(new_rec + BT_UP) = parent;
   *(new_rec + BT_UP + BT_LSIB) = *(new_rec + BT_UP + BT_RSIB) = 0;
   *(new_rec + BT_BAL) = 0;
   btcopy (word, len, new_rec);
   *root += reclen;
   if (parent)
   {
      *(root + parent + BT_UP + dir) = child;
      while (1)
      {
         dir = *(root + parent + BT_UP + BT_LSIB) == child ? BT_LSIB : BT_RSIB;
         if (*(root + parent + BT_BAL) == dir)
         {
            if (*(root + child + BT_BAL) == -dir)
               dub_rot (root, parent, child, dir);
            else 
               sing_rot (root, parent, child, dir);
            break;
         }
         if ((*(root + parent + BT_BAL) += dir) == 0)
            break;
         child = parent;
         parent = *(root + parent + BT_UP);
         if (parent == 0) break;
      }
   }
   else
      *(root + 1) = child;
   return (root);
}

int btfind (short *root, char *word)
{
   int node;
   int dir;
   
   if ((node = *(root + 1)) == 0)
      return (0);
   while (node)
   {
      if ((dir = btcompare (word, (char *)(root + node + BT_TXT))) == 0)
         return (node);
      node = *(root + node + BT_UP + dir);
   }
   return (0);
}

#if defined(BT_SPAN) && BT_SPAN != 0
void btaction (short *root, int node)
{
   puts ((char *)(root + node + BT_TXT));
}

void btspan (short *root)
{
   int state = 0;
   int node = *(root + 1);
   int next;
   
   if (node == 0)
      return;
      
   while (node)
   {
      switch (state)
      {
         case 0:
            if (next = *(root + node + BT_UP + BT_LSIB))
            {
               node = next;
            }
            else if (*(root + node + BT_UP + BT_RSIB))
               state = 1;
            else
               state = 3;
            break;
            
         case 1:
            btaction (root, node);
            if (next = *(root + node + BT_UP + BT_RSIB))
            {
               node = next;
               state = 0;
            }
            else
               state = 2;
            break;
            
         case 3:
            btaction (root, node);
            
         case 2:
            if (next = *(root + node + BT_UP))
            {
               if (*(root + next + BT_UP + BT_LSIB) == node)
                  state = 1;
               else
                  state = 2;
            }
            node = next;
            break;
      }
   }
}
#endif /* BT_SPAN */

#ifdef __STDC__
void word_update (void)
#else
void word_update ()
#endif
{
   char *aptr = text_buf;
   char *zptr;
   
   while (1)
   {
      while (*aptr && ! isalpha (*aptr)) aptr++;
      if (*aptr == '\0') break;
      zptr = aptr + 1;
      while (*zptr && isalpha (*zptr)) zptr++;
      if (zptr - aptr > 4 &&
         *(zptr - 3) != 'i' && *(zptr - 2) != 'n' && *(zptr - 1) != 'g')
            btadd (word_buf, aptr, zptr - aptr);
      if (*zptr == '\0') break;
      aptr = zptr + 1;
   }   
   return;
}
#endif /* STYLE */

#define MAX_BREAKS 100

#if defined(PLAIN) && defined(MEMORY)
#  define get_char(X) text[X]
#else /* !PLAIN || !MEMORY */
#ifdef __STDC__
char get_char (long char_addr)
#else
char get_char (char_addr)
long char_addr;
#endif
{
#ifndef PLAIN
   int mask;
#endif /* not PLAIN */
#ifdef MEMORY
#  ifdef PLAIN
      return (text [char_addr]);
#  else /* not PLAIN */
   mask = (char_addr >> 4) & 127;
   if (mask == 0)
      mask = char_addr & 127;
   if (mask == 0)
      mask = 'X';
   return (mask ^ text [char_addr] ^ title [char_addr % titlen]);
#  endif /* PLAIN */
#else /* not MEMORY */
#  ifdef BUFFERS
   int index;
   char *buf_ptr;
   int oldest_chunk;
   long new_addr;
   void file_oops ();
   
   oldest_chunk = 0;
   buf_ptr = text;
   for (index = 0; index < BUFFERS; index++)
   {
      if (char_addr >= chunk_start [index] && char_addr < chunk_end [index])
         goto gotit;
      buf_ptr += TEXT_CHUNK;
   }

   for (index = 0; index < BUFFERS; index++)
   {
      if (chunk_end [index] == 0)
         goto readit;
      if (chunk_age [oldest_chunk] > chunk_age [index])
         oldest_chunk = index;
   }
   index = oldest_chunk;

readit:
   locate_faults++;
   buf_ptr = text + TEXT_CHUNK * index;
   new_addr = (char_addr / TEXT_CHUNK) * TEXT_CHUNK ;
   if (fseek (text_file, new_addr, 0))
      file_oops ();
   chunk_start [index] = new_addr;
   chunk_end [index] = fread (buf_ptr, sizeof (char), 
      TEXT_CHUNK, text_file) + new_addr;
#ifdef LOC_STATS
   (void) printf ("Wanted %ld.  Buffer %d: from %ldK.\n",
      char_addr, index, new_addr / TEXT_CHUNK);
#endif /* LOC_STATS */
   if (chunk_start [index] > chunk_end [index])
      file_oops ();

gotit:
   chunk_age [index] = locate_demands;
#ifdef PLAIN
   return (*(buf_ptr + char_addr - chunk_start [index]));
#else /* not PLAIN */
   mask = (char_addr >> 4) & 127;
   if (mask == 0)
      mask = char_addr & 127;
   if (mask == 0)
      mask = 'X';
   return 
      (*(buf_ptr + char_addr - chunk_start [index]) ^ mask ^ 
         title [char_addr % titlen]);
#endif /* PLAIN */
#else /* not BUFFERS */
   void file_oops ();

   if (char_addr < chunk_start || char_addr >= chunk_end)
   {
      locate_faults++;
      if (fseek (text_file, char_addr, 0))
         file_oops ();
      chunk_start = char_addr;
      chunk_end = fread (text, sizeof (char), TEXT_CHUNK, text_file)
         + chunk_start - 1;
      if (chunk_start > chunk_end)
         file_oops ();
   }
#ifdef PLAIN
   return (text [char_addr - chunk_start]);
#else /* not PLAIN */
   mask = (char_addr >> 4) & 127;
   if (mask == 0)
      mask = char_addr & 127;
   if (mask == 0)
      mask = 'X';
   return (text [char_addr - chunk_start] ^ mask ^ title [char_addr % titlen]);
#endif /* PLAIN */

#endif /* BUFFERS */
}

#ifdef __STDC__
void file_oops (void)
#else
void file_oops ()
#endif
{
   PRINTF ("\n \nUnable to retrieve required data! Sorry...\n");
   outbuf (1);
   (void) fclose (text_file);
   if (log_file) (void) fclose (log_file);
   exit (0);
#endif /* MEMORY */
}
#endif /* PLAIN && MEMORY */

#ifdef __STDC__
void voc (int word, int what, int test, int vtext)
#else
void voc (word, what, test, vtext)
int word;
int what;
int test;
int vtext;
#endif
{
   int index;
   int tc;
   static int vc = 0;
   
   if (word == 0)
   {
      vc = 0;
      return;
   }
   if (what == 0)
      what = word;
   if (test >0 && bitest (word, test) == 0)
      return;
   if (vc++ > 0)
   {
      outchar (',');
      outchar (' ');
   }      
   index = (vtext == 0) ? word : vtext;
   ta = textadr [index];
   tc = get_char (ta);
   if (tc == '!')
      tc = get_char (++ta);
   while (tc != '\0')
   {
      outchar (tc);
      tc = get_char (++ta);
   }
}

#ifdef __STDC__
int scrchk (int clear)
#else
int scrchk (clear)
int clear;
#endif
{
#ifdef GLK
   return (0);
#else /* !GLK */
   static int lincnt = 0;
   char reply [160];
   int need;

#ifdef CONTEXT
   if (cgi) return (0);
#endif
   if (clear || com_name) 
      lincnt = 0;
   else if (++lincnt >= Screen)
   {
      need = Margin;
      while (need--)
         putchar (' ');
      PRINTF2 ("[More?] ", 0);
      fgets (reply, sizeof (reply) - 1, com_file ? com_file : stdin);
      if (log_file)
         fprintf (log_file, "\nREPLY: %s", reply);
      lincnt = 1;
      if (*reply == 'n' || *reply == 'N' || *reply == 'q' || *reply == 'Q')
      {
         lptr = text_buf;
         strcpy (text_buf,"OK.\n");
         if (!compress) strcat (text_buf, "\n");
         strcat (text_buf, "? ");
         return (1);
      }
   }
   return (0);
#endif /* GLK */
}

#ifdef BLOCK_END
#ifdef __STDC__
char *doblock (
   char type,
   char* tptr)
#else
char *doblock (type, tptr)
char type;
char *tptr;
#endif
{
   int maxlen = 0;
   int lead = 1000;
   int hlead;
   int skip;
   int len;
   int trulen;
   char *aptr = tptr;
   
#ifdef CONTEXT
   if (cgi)
   {
      printf ("<center>");
      if (type == BLOCK_START)
         printf ("<table><tr><td>");
      putchar ('\n');
   }
#endif
   while (*aptr && *aptr != BLOCK_END)
   {
      skip = 0;
      while (*aptr == ' ' || *aptr == '\t')
      {
         skip++;
         aptr++;
      }
      trulen = len = skip;
      while (*aptr && *aptr != '\n' && *aptr != BLOCK_END)
      {
         len++;
         if (*aptr != ' ' && *aptr != '\t')
            trulen = len;
         aptr++;
      }

      if (skip < len)
      {
         if (skip < lead)
            lead = skip;
         if (trulen > maxlen)
            maxlen = trulen;
      }
      if (*aptr == BLOCK_END)
         break;
      aptr++;
   }

   maxlen -= lead;
   hlead = -lead;
   if (maxlen < Linlen)
      hlead += (Linlen - maxlen + 1) / 2;
      
   if (justify == 0 && hlead > 1)
      hlead = (9 * hlead) / 10;

#ifdef GLK
   glk_set_style (style_Preformatted);
   hlead = 0;   /* Was 5! */
#endif
   while (*tptr && *tptr != BLOCK_END)
   {
      scrchk (0);
#ifdef GLK
      tptr += lead;
#endif
      if (hlead < 0)
         tptr += hlead;
      else if (hlead > 0)
      {
         for (len = 0; len < hlead; len++)
         {
            PUTCHAR (' ');
         }
      }
      while (*tptr && *tptr != '\n' && *tptr != BLOCK_END)
      {
         PUTCHARA (tptr);
      }
      if (*tptr == '\n')
      {
#ifdef CONTEXT
         if (cgi)
         {
            if (type == BLOCK_START) 
               printf ("<block>");
            else
               printf ("<br>");
         }
#endif
         PUTCHARA (tptr);
      }
#if defined(CONTEXT)
      if (cgi && *tptr == BLOCK_END)
            printf ("<br>");
#endif
   }
#ifdef CONTEXT
   if (cgi)
   {
      if (type == BLOCK_START)
         printf ("</td></tr></table>");
      printf ("</center>\n");
   }
#endif
#ifdef GLK
   glk_set_style (style_Normal);
#endif
   if (*tptr)
      tptr++;

   return (tptr);
}
#endif /* BLOCK_END */

#ifdef __STDC__
void outbuf (int terminate)
#else
void outbuf (terminate)
int terminate;
#endif
{
   int break_point;
   int break_count;
   char *tptr = text_buf;
   char last_char = '\0';
   int wrapped = 0;
   int line_len = 0;
   int ignore_eol = 0;
   char lastchar = '\0';
   char text_char;
   
   eol_count = 0;

   while (*(lptr - 1) == ' ')
   {
      lptr--;
      text_len--;
   }
   *lptr = '\0';
   if (*(lptr - 1) == '\n')
   {
      while (*(lptr - 1) == '\n')
      {
         lptr--;
         text_len--;
      }
      if (! terminate)
      {      
#if STYLE > 1
#ifdef BLOCK_END
/*         if (!compress && *(lptr - 1) != BLOCK_END) */
         if (!compress)
#else
         if (!compress)
#endif /* BLOCK_END */
         {
            PRINTF ("\n ");
         }
#endif /* STYLE */
         PRINTF ("\n? ")
      }
   }

   if (*(lptr - 1) != ' ')
   {
      *lptr++ = ' ';
      text_len++;
   }
      
   if (*tptr == '\n')
   {
      while (*tptr == '\n')
         tptr++;
      if (!compress)
         tptr--;
   }
      
   *lptr = '\0';
   lptr = tptr;
   break_point = 0;
   break_count = -1;

#if STYLE >= 11
   if (value [ARG1] < BADWORD && value [ARG2] < BADWORD)
      word_update ();
#endif /* STYLE */

   while (text_char = *tptr++)
   {
      if (text_char == IGNORE_EOL)
      {
         ignore_eol = 1;
         line_len++;
         continue;
      }
      if (text_char == '\n' && ignore_eol)
      {
         *(tptr - 1) = IGNORE_EOL;
         ignore_eol = 0;
         line_len++;
         continue;
      }
         
      if (text_char == ' ' && wrapped && line_len == 0)
      {
         wrapped = 0;
         while ((text_char = *tptr++) == ' '); 
         lptr = --tptr;
         lastchar = ' ';
      }
      else
         line_len++;
         

#ifdef BLOCK_START
      if (text_char == BLOCK_START || text_char == CENTRE_START)
      {
         lptr = tptr = doblock (text_char, tptr);
         if ((text_char = *tptr++) == '\0')
            break;
         line_len = 0;
      }
#endif /* BLOCK_START */
      
      if (text_char == '\n')
      {
         if (*tptr == '\n' && *(tptr + 1) == '\n') 
            continue;
         if (line_len > 0)
         {
            lptr = outline (lptr, line_len, 0, 0);
/*            if (lptr == NULL) return; */
            line_len = 0;
            tptr = lptr;
         }
         else if (!wrapped)
         {
            (void) PUTCHAR ('\n');
            lptr = tptr;
         }
         break_point = 0;
         break_count = -1;
         lastchar = ' ';
         line_len = 0;
         wrapped = 0;
#ifdef CONTEXT
         if (cgi) printf ("<br>");
#endif
         continue;
      }

      wrapped = 0;
      
      if (text_char == ' ' || text_char == '-')
      {
         if (lastchar != text_char)
         {
            break_point = line_len - (text_char == ' ' ? 1 : 0);
            break_count++;
         }
         if (line_len >= Maxlen)
         {
            while (*tptr == ' ')
               tptr++;
            lptr = outline (lptr, break_point, break_count, 1);
/*            if (lptr == NULL) return; */
            break_point = 0;
            break_count = -1;
            (void) PUTCHAR ('\n');
            line_len = 0;
            tptr = lptr;
            wrapped = 1;
            lastchar = ' ';
            continue;
         }
         lastchar = text_char;
         continue;
      }

      if (line_len >= Maxlen)
      {
         if (break_count < 0)
         {
            lptr = outline (lptr, Maxlen, 0, 0);
/*            if (lptr == NULL) return; */
         }
         else
         {
            lptr = outline (lptr, break_point, break_count, 1);
/*            if (lptr == NULL) return; */
            (void) PUTCHAR ('\n');
            wrapped = 1;
         }
         last_char = '\0';
         break_point = 0;
         break_count = -1;
         line_len = 0;
         tptr = lptr;         
      }
      else
         lastchar = text_char;
   }
   if (line_len > 0)
      (void) outline (lptr, line_len, 0, 0);

   lptr = text_buf;
   *lptr++ = '\n';
   *lptr = '\0';
   text_len = 1;
   fflush (stdout);
}

#ifdef NEST_TEXT
#ifdef __STDC__
void nested_say (long addr, int key, int type, int qualifier)
#else
void nested_say (addr, key, type, qualifier)
long addr;
int key;
int type;
int qualifier;
#endif
{
   int refno;
   
   if (key &= 14)
      key = 8;
   refno = get_char (addr++) << 8;
   refno |= (get_char (addr) & 255);
   refno += (type == NEST_TEXT ? FTEXT : FVARIABLE);
   say (key, refno, qualifier);
   ta = addr;
}
#endif /* NEST_TEXT */

#ifdef __STDC__
void say (int key, int what, int qualifier)
#else
void say (key, what, qualifier)
int key;
int what;
int qualifier;
#endif
{
   int index;
   int offset;
   int value_flag;
   int qual_flag;
   int var_what_flag;
   int var_qual_flag;
   int quip_flag;
   int brief_flag = 0;
#ifdef FULL
   int full_flag;
#endif /* FULL */
#if defined(DETAIL) || STYLE >= 11
   int detail_flag;
#endif /* DETAIL */
   int switch_size;
   int textqual;
   int swqual;
   int given_qualifier;
   int given_key = key;
   char auxbuf [WORDSIZE];
   long auxa;
   long ea;
   char *cp;
   char tc;
   char tl = 0;

/* NB: The below flag values are hard-coded in acdc's dominor.c! */

#define QUIP_FLAG   64
#if defined(DETAIL) || STYLE >= 11
#  define DETAIL_FLAG 32
#endif
#ifdef FULL
#  define FULL_FLAG   16
#else
#  define FULL_FLAG    0
#endif
#define QUAL_FLAG      8
#define VQUAL_FLAG     4
#define VAR_FLAG       2
#define VALUE_FLAG     1

   if (lptr == NULL) lptr = text_buf;
   locate_demands++;
   quip_flag =     key & QUIP_FLAG;
#if defined(DETAIL) || STYLE >= 11
   detail_flag =   key & DETAIL_FLAG;
#endif
#ifdef FULL
   full_flag =     key & FULL_FLAG;
#endif
   qual_flag =     key & QUAL_FLAG;
   var_qual_flag = key & VQUAL_FLAG;
   var_what_flag = key & VAR_FLAG;
   value_flag =    key & VALUE_FLAG;

#ifdef OBSOLETE
#ifdef FULL
   if (bitest (STATUS, TERSE))
      full_flag = 0;
   else if (bitest (STATUS, FULL) ||
      (bitest (STATUS, TERSE) == 0 && bitest (STATUS, BRIEF) == 0))
         full_flag = 1;
   else if (bitest (STATUS, BRIEF))
      full_flag = bitest (value [HERE], BEENHERE) ? 0 : 1;
#endif /* FULL */
#endif /* OBSOLETE */

   if (var_what_flag)
      what = value [what];

   given_qualifier = qualifier;
   if (var_qual_flag &&
      ((qualifier != ARG1 && qualifier != ARG2) || value_flag))
      qualifier = value [qualifier];

   if (what > LPLACE)
      ta = textadr [what];
   else if (what >= FPLACE)
   {
#if defined(TERSE) && defined(FULL) && defined(BEENHERE)
      if (bitest (STATUS, TERSE) || 
         (! bitest (STATUS, FULL) && bitest (what, BEENHERE)))
            ta = brief_desc [what];
      else
#endif
         ta = long_desc [what];
   }
   else if (what >= FOBJECT)
   {
#if defined(DETAIL)
      if (detail_flag || bitest (STATUS, DETAIL))
         ta = detail_desc [what];
      else
#endif
      if (location [what] == INHAND)
      {
         brief_flag = 1;
         ta = brief_desc [what];
      }
      else
         ta = long_desc [what];
   }

   if ((tc = get_char (ta)) == '\0') goto shutup;

#define RANDOM_TEXT      1
#define INCREMENTAL_TEXT 2
#define CYCLIC_TEXT      3
#define ASSIGNED_TEXT    4
#define TIED_TEXT        5

   if (what >= FTEXT)
   {
      int twat = 2 * (what - FTEXT);
      textqual = qualifier;
      if (text_info [twat] == RANDOM_TEXT)
      {
         textqual = text_info [twat + 1];
         if (textqual <= 1)
         {
            textqual = 0;
         }
         else
         {
            textqual = irand (textqual);
         }
      }
      else if (text_info [twat] == INCREMENTAL_TEXT)
      {
         textqual = value [what];
         if (value [what] < text_info [twat + 1] - 1)
            value[what]++;
      }
      else if (text_info [twat] == CYCLIC_TEXT)
      {
         textqual = value [what];
         if (value [what] < text_info [twat + 1] - 1)
            value[what]++;
         else
            value [what] = 0;
      }
      else if (text_info [twat] == ASSIGNED_TEXT)
      {
         textqual = value [what];
      }
      else if (text_info [twat] == TIED_TEXT)
      {
         textqual = value [value [what]];
      }
   }

   if (!qual_flag)
   {
      if (what <= LPLACE)
         qualifier = value [what];
      else
         qualifier = what;
   }
   
   while (tc != '\0')
   {
      tl = tc;
#ifdef NEST_TEXT
      if (tc == NEST_TEXT || tc == NEST_VAR)
      {
         nested_say (ta + 1, given_key, tc, qualifier);
         tc = get_char (++ta);
         continue;
      }
#endif /* NEST_TEXT */
#ifdef DWARVEN
      if (tc == DWARVISH)
      {
         extra_dwarvish ^= 1;
         goto next_char;
      }
#endif /* DWARVEN */
      if (tc == SW_START)
      {
         switch_size = get_char (++ta);
         ea = ta + 2 * switch_size -1;
         swqual = (what >= FTEXT) ? textqual : qualifier;
#if STYLE == 1
         if (brief_flag)
            swqual = (swqual == 1 || switch_size == 1) ? 0 : 1;
         if (swqual <= 0 || (swqual == 1 && what >= FTEXT))
#else /* STYLE > 1 */
         if (swqual <= 0)
#endif /* STYLE */
            ta = ea + 1;
         else
         {
            ta = ta - 1 + 2 *
#if STYLE == 1
               ((swqual > switch_size) ? switch_size - 1 : swqual - 1);
            if (what < FTEXT) ta += 2;
#else /* STYLE > 1 */
               ((swqual >= switch_size) ? switch_size - 1 : swqual);
#endif /* STYLE */
            offset = get_char (ta + 1);
            if (offset < 0)
               offset  += 256;
            ta = ea + 256 * get_char (ta) + offset + 1;
         }
         offset = get_char (ea + 1);
         if (offset < 0)
            offset += 256;
         ea = ea + 256 * get_char (ea) + offset + 1;
         tc = get_char (ta);
      }
      else if (tc == SW_BREAK)
      {
         tc = get_char (ta = ea++);
         if (tc == SW_BREAK)
            goto next_char;
      }
      else if (tc == HOLDER)
      {
#if STYLE >= 11
         if (upcase) upcase = 2;
#endif
         if (value_flag)
         {
            (void) sprintf (auxbuf, "%d", qualifier);
            cp = auxbuf - 1;
            while (*(++cp) != '\0')
               outchar (*cp);
            goto next_char;
         }
         else if (qualifier == ARG1 || qualifier == ARG2)
         {
            cp = ((qualifier == ARG1) ? arg1_word : arg2_word) - 1;
            while (*(++cp) != '\0')
               outchar (*cp);
            goto next_char;
         }
#if STYLE >= 11
         else if (qualifier == ORG1 || qualifier == ORG2)
         {
            cp = ((qualifier == ORG1) ? orig1 : orig2) - 1;
            while (*(++cp) != '\0')
               outchar (*cp);
            goto next_char;
         }
#endif
         else
         {
            index = (var_qual_flag && given_qualifier <= LPLACE) ?
               given_qualifier : qualifier;
            auxa = ta;
            locate_demands++;
            ta = textadr [index];
            tc = get_char (ta);
            if (tc == '!')
               tc = get_char (++ta);

            while (tc != '\0')
            {
               outchar (tc);
               tc = get_char (++ta);
            }
            ta = auxa;
         }
      }
      else
         outchar (tc);
next_char:
      tc = get_char (++ta);
   }

shutup:
   if (quip_flag) longjmp (loop_back, 1);
   return;
}

#ifdef __STDC__
void outchar (int text_char)
#else
void outchar (text_char)
int text_char;
#endif
{
#ifdef TAG_START
   if (ignore_tag)
   {
      if (text_char == TAG_END)
         ignore_tag = 0;
      return;
   }
   if (text_char == TAG_START)
   {
      ignore_tag = 1;
      return;
   }
#endif /* TAG */
   if (text_char == '\n')
   {
      eol_count++;
      if (eol_count > 2)
      return;
   }
#ifdef BLOCK_END
   else if (text_char && text_char != BLOCK_END && eol_count)
#else
   else if (text_char && eol_count)
#endif /* BLOCK_END */
      eol_count = 0;

#ifdef NBSP
   if (text_char == NBSP)
      text_char = ' ';
#endif /* NBSP */
      
#if STYLE >= 11
   if (isalpha (text_char))
   {
      if (upcase == 2)
         text_char = toupper (text_char);
      upcase = 0;
   }
   else if (isdigit (text_char))
      upcase = 0;
   else if (strchr (".!?", text_char))
      upcase = 1;
#endif /* STYLE >= 11 */

   if (text_len == text_buf_len - 3)
   {
      text_buf_len += 1024;
      if ((text_buf = (char *) realloc (text_buf, text_buf_len)) == NULL)
      {
         puts ("*** Unable to extend text buffer! ***");
         exit (0);
      }
      lptr = text_buf + text_len;
   }
#ifdef CONTEXT
   if (cgi && (text_char == '<' || text_char == '>'))
   {
      *lptr++ = '&';
      *lptr++ = (text_char == '<') ? 'l' : 'g';
      *lptr++ = 't';
      *lptr = ';';
      text_len += 4;
   }
   else
   {
      text_len++;
      *lptr = text_char;
   }
#else
   text_len++;
   *lptr = text_char;
#endif /* CONTEXT */
#ifdef DWARVEN
   if (value [DWARVEN] || extra_dwarvish)
      shift_up (lptr);
#endif /* DWARVEN */
   lptr++;
   return;
}

#ifdef __STDC__
void getinput (char *inbuf, int insize)
#else
void getinput (inbuf, insize)
char *inbuf;
int insize;
#endif
{
#ifdef READLINE
   char *rdl;
#endif
   char *cptr;
   char mybuf [170];
   *inbuf = '\0';
#ifdef DWARVEN
   extra_dwarvish = 0;
#endif 
   if (text_len)
      outbuf (0);
#if STYLE >= 11
   upcase = 1;
#endif /* STYLE >= 11 */

#ifdef CONTEXT
   if (cgi == 'x' || cgi == 'z')
   {
      special (998, &value [0]);
      if (word_buf) free (word_buf);
      exit (value [CONTEXT]);
   }
   if (cgi == 'y')
   {
      strncpy (inbuf, cgicom, insize);
      cgi = 'z';
   }
   else
#endif /* CONTEXT */
        if (com_file)
   {
      while (1)
      {
         if (fgets (mybuf, insize, com_file) == NULL || 
             strncmp (mybuf, "INTERACT", 8) == 0)
         {
            fclose (com_file);
            com_file = NULL;
#ifdef READLINE
            rdl = readline (NULL);
            memcpy (inbuf, rdl, insize);
            free (rdl);
            *(inbuf + insize - 1) = 0;
#else /* not READLINE */
#  ifdef GLK
            glkgets (inbuf, insize);
#  else
            fgets (inbuf, insize, stdin);
#  endif
#endif /* READLINE */
            break;
         }
         if (strncmp (mybuf, "REPLY: ", 7) == 0)
         {
            strncpy (inbuf, mybuf + 7, insize);
            printf (inbuf);
            break;
         }
      }
   }
   else if (com_file == NULL)
#ifdef READLINE
   {
      rdl = readline (NULL);
      memcpy (inbuf, rdl, insize);
      free (rdl);
      *(inbuf + insize - 1) = 0;
   }
#else /* not READLINE */
#  ifdef GLK
      glkgets (inbuf, insize - 1);
#  else
      fgets (inbuf, insize, stdin);
#  endif
#endif /* READLINE */
#ifdef CONTEXT
   if (cgi == 'x') cgi = 'z';
#endif
   *(inbuf + insize - 1) = '\0';
   *(inbuf + insize - 2) = '\n';
   cptr = inbuf;
   while (*cptr)
   {
      if (strchr ("\"\'_", *cptr))
         *cptr = ' ';
      cptr++;
   }
   if (log_file)
      fprintf (log_file,"\nREPLY: %s\n", inbuf);
}

#ifdef __STDC__
char *outline (char *aptr, int char_count, int break_count, int fill)
#else
char *outline (aptr, char_count, break_count, fill)
char *aptr;
int break_count;
int char_count;
int fill;
#endif
{
   int index;
   int adjust;
   int base;
   int need;
   int break_point;
   char lastchar;
   static int flip_flop = 1;

   if (scrchk (0) != 0)
      return lptr;
/* printf ("+++ OUTLINE =%c=%c=%c=...=%c=%c=%c: %d, %d, %d\n", 
*aptr, *(aptr+1), *(aptr+2),
*(aptr+char_count-3), *(aptr+char_count-2), *(aptr+char_count-1), 
fill, break_count, char_count); */
   if (need = Margin)
      while (need--)
         PUTCHAR (' ');
   if (break_count <= 0 || fill == 0 || char_count == Maxlen)
      while (char_count-- > 0)
      {
         PUTCHARA (aptr);
      }
   else
   {
      need = Maxlen - char_count;
      base = (need - flip_flop) / break_count + flip_flop;
      adjust = 1 - 2 * flip_flop;
      break_point = need % break_count;
      if (!flip_flop)
         break_point = break_count - break_point;
      flip_flop = 1 - flip_flop;
      lastchar = '\0';

      while (char_count-- > 0)
      {
         if (justify && lastchar == ' ' && *aptr != ' ')
         {
            index = base;
            while (index-- > 0)
            {
               (void) PUTCHAR (' ');
            }
            if (--break_point ==0)
               base = base + adjust;
         }
         lastchar = *aptr;

         PUTCHARA (aptr);
      }
   }
   fflush (stdout);
   return (aptr);
}

#ifdef __STDC__
void advcpy (char *word_buff, long word_addr)
#else
void advcpy (word_buff, word_addr)
char *word_buff;
long word_addr;
#endif
{
   int wlen;

   if (get_char (word_addr) == '!')
      word_addr++;
   for (wlen = 1; wlen <= 20; wlen++)
      if ((*word_buff++ = get_char (word_addr++)) == '\0')
         return;
}

#ifdef __STDC__
void fake (int which_arg, int refno)
#else
void fake (which_arg, refno)
int which_arg;
int refno;
#endif
{
   int word;
   
   for (word = 0; word < VOCAB_SIZE; word++)
   {
      if (voc_refno [word] == refno)
      {
         (void) advcpy (which_arg == 1 ? arg1_word : arg2_word, 
            voc_word [word]);
         return;
      }
   }
}

#ifdef __STDC__
void default_to (int key, int place, int type)
#else
void default_to (key, place, type)
int key;
int place;
int type;
#endif
{
   int index;
   int fits;
   int first;

   if (key == 0 && value [STATUS] != 1) return;
   fits = -1;
#ifdef ALL
   first = (key == 2) ? value_all + 1 : FOBJECT;
   if (first > LOBJECT)
      goto failed;
   for (index = first; index <= LOBJECT; index++)
#else /* not ALL */
   for (index = FOBJECT; index <= LOBJECT; index++)
#endif /* ALL */
   {
#ifdef SCHIZOID
      if ((location [index] == place || (place != INHAND &&
         bitest (index, SCHIZOID) && location [index] + 1 == place)) &&
#else
      if (location [index] == place &&
#endif
            (type < 0 || bitest (index, type)))
      {
         if (fits >= 0) return;   /* Can't happen if key > 0 */
         fits = index;
         if (key) break;
      }
   }
   if (fits >= 0)
   {
      value [ARG2] = fits;
      (void) advcpy (arg2_word, textadr [fits]);
#ifdef DWARVEN
      if (value [DWARVEN] || extra_dwarvish)
      {
         char *wp = arg2_word;
         while (*wp)
            shift_up (wp++);
      }
#endif /* DWARVEN */
      arg2_word [19] = '\0';
      value [STATUS] = 2;

#ifdef IT
      value [IT] = fits;
#endif

#ifdef ALL
      if (key > 0)
         value_all = fits;

      if (key == 1)
      {
         location_all = place;
         type_all = type;
      }
#endif /* ALL */
      return;
   }

#ifdef ALL
failed:
/*   if (key == 1 && value [STATUS] == 2)
      value [STATUS] = 1; */      /* Force the please clarify response */
   if (key > 0)
      value_all = 0;
#endif /* ALL */
   return;
}

#if STYLE >= 11
#ifdef __STDC__
int find_word 
   (int *type, int *refno, long *tadr, int *olen, long *ovoc, int which_arg)
#else
int find_word (type, refno, tadr, olen, ovoc, which_arg)
int *type;
int *refno;
long *tadr;
int *olen = 0;
long *ovoc;
#endif
#else
#ifdef __STDC__
int find_word (int *type, int *refno, long *tadr)
#else
int find_word (type, refno, tadr)
int *type;
int *refno;
long *tadr;
#endif
#endif
{
   int bottom, middle, top;
   int old_refno;
#if STYLE > 1
   int old_type;
   long old_tadr;
#endif /* STYLE */
   int exact;
   long va;
   char *wp;
   long ra;
   char myword [WORDSIZE];
  
#if STYLE >= 11
   if (amatch == -1)
   {
      *refno = BADWORD;
      return (0);
   }
#endif /* STYLE >= 11 */
   strcpy (myword, tp [tindex]);
#ifdef DWARVEN
   if (value [DWARVEN]) shift_down (myword, WORDSIZE);
#endif /* DWARVEN */
   if (*myword == '\0')
   {
      *type = NOISE;
      return (0);
   }
   bottom = -1;
   top = VOCAB_SIZE + 1;
   while (top > bottom + 1)
   {
      locate_demands++;
      middle = (bottom + top) / 2;
      if (get_char (va = voc_addr [middle]) == '!')
         va++;
      wp = myword;
      while (get_char (va) == *wp)
         if (*wp != '\0')
         {
            wp++;
            va++;
         }
         else
            break;

      if (get_char (va) < *wp && *wp != '\0')
         bottom = middle;
      else
         top = middle;
   }
   *refno = BADWORD;
   bottom++;
   top = VOCAB_SIZE;
   old_refno = BADWORD;

   while (bottom < top)
   {
      wp = myword;

      if (get_char (va = voc_addr [bottom]) == '!')
      {
         va++;
         exact = 1;
      }
      else
         exact = 0;
      ra = va;
      while (*wp == get_char (ra))
      {
         if (*wp == '\0')
            break;
         else
         {
            ra++;
            wp++;
         }
      }
      if (*wp != '\0') break;
#if STYLE > 1
      if (!exact || (exact && get_char (ra) == '\0'))
#else
      if (get_char (ra) == '\0' || ra - va >= 5)
#endif
      {
         *type = voc_type [bottom];
         *refno = voc_refno [bottom];
         *tadr = voc_word [bottom];
         if (get_char (ra) == '\0')
#if STYLE == 1
         {
            if (ra - va <= 2)
            {
               wp = myword;
               while (++bottom < top)
                  if (*refno == voc_refno [bottom] &&
                     *wp == get_char (voc_addr [bottom]))
                        *tadr = voc_word [bottom];
            }
            return (0);
         }
#else /* STYLE > 1 */
            return (0);
         if (old_refno != BADWORD && *refno != old_refno)
#if STYLE >= 11
         {
#define REF(X) (which_arg == 1 ? X > LOBJECT : (X <= LOBJECT && \
                   (location [X] == INHAND || location [X] == value [HERE])))
            int oref = REF (old_refno);
            int nref = REF (*refno);
            
            if ((nref && oref) || (!nref && !oref))
               { *refno = AMBIGWORD; return (0); }
            if (!nref && oref)
            { 
               *refno = old_refno; 
               *tadr = old_tadr;
               *type = old_type;
               bottom++; 
               continue;
            }
            if (nref && !oref)
               { old_refno = *refno; if (get_char (va) == '\0') break; }
         }
#endif /* STYLE >= 11 */
         old_tadr = *tadr;
         old_type = *type;
#endif /* STYLE */
         old_refno = *refno;
         if (get_char (va) == '\0') break;
      }
      bottom++;
   }

#if STYLE >= 11
   if (*refno == BADWORD && amatch)
   {
      char *bp = NULL;
      long ba = 0;
      old_refno = -1;
      for (bottom = 0; bottom < VOCAB_SIZE; bottom++)
      {
         if (get_char (va = voc_addr [bottom]) == '!')
            continue;
         wp = myword;
         while (*wp == get_char (va))
            { wp++; va++; }
         if (*wp == '\0' && get_char (va + 1) == 0 &&
               voc_type [bottom] != NOISE)
         {
            if (old_refno >= 0 && 
               voc_refno [old_refno] != voc_refno [bottom])
                  {old_refno = AMBIGTYPO; break;}
            old_refno = bottom; 
            *ovoc = voc_addr [bottom];
            *olen = va - *ovoc;
            continue;
         }
         bp = wp;
         ba = va;
         if (*wp == get_char (va + 1) && *(wp + 1) == get_char (va))
         {
            va += 2;
            wp += 2;
            while (*wp && *wp == get_char (va))
               {wp++; va++;}
            if (*wp == '\0' && get_char (va) == '\0' && 
               voc_type [bottom] != NOISE)
            {
               if (old_refno >= 0 && 
                  voc_refno [old_refno] != voc_refno [bottom])
                     {old_refno = AMBIGTYPO; break;}
               old_refno = bottom; 
               *ovoc = voc_addr [bottom];
               *olen = va - *ovoc;
               continue;
            }
           wp = bp; 
           va = ba;
         }
         if (*(wp + 1) == get_char (va + 1))
         {
            wp++;
            va++;
            while (*wp && *wp == get_char (va))
               {wp++; va++;}
            if (*wp == '\0' && get_char (va) == '\0' && 
               voc_type [bottom] != NOISE)
            {
               if (old_refno >= 0 && 
                  voc_refno [old_refno] != voc_refno [bottom])
                     {old_refno = AMBIGTYPO; break;}
               old_refno = bottom; 
               *ovoc = voc_addr [bottom];
               *olen = va - *ovoc;
               continue;
            }
            wp = bp;
            va = ba;
         }
         if (*wp == get_char (va + 1))
         {
            va++;
            while (*wp && *wp == get_char (va))
               {wp++; va++;}
            if (*wp == '\0' && get_char (va) == '\0' && 
               voc_type [bottom] != NOISE)
            {
               if (old_refno >= 0 && 
                  voc_refno [old_refno] != voc_refno [bottom])
                     {old_refno = AMBIGTYPO; break;}
               old_refno = bottom; 
               *ovoc = voc_addr [bottom];
               *olen = va - *ovoc;
               continue;
            }
            wp = bp;
            va = ba;
         }
         if (*(wp + 1) == get_char (va) || *(wp + 1) == '\0')
         {
            wp++;
            while (*wp && *wp == get_char (va))
               {wp++; va++;}
            if (*wp == '\0' && get_char (va) == '\0' && 
               voc_type [bottom] != NOISE)
            {
               if (old_refno >= 0 && 
                  voc_refno [old_refno] != voc_refno [bottom])
                     {old_refno = AMBIGTYPO; break;}
               old_refno = bottom; 
               *ovoc = voc_addr [bottom];
               *olen = va - *ovoc;
               continue;
            }
         }
      }
      if (old_refno == AMBIGTYPO)
         *refno = AMBIGTYPO;
      else if (old_refno >= 0)
      {
         *type = voc_type [old_refno];
         *refno = voc_refno [old_refno];
         *tadr = voc_word [old_refno];
         return (1);
      }
   }
#endif /* STYLE >= 11 */
   return (0);
}

#ifdef __STDC__
void parse (void)
#else
void parse ()
#endif
{
   char *lp = comline;
   char *ew = NULL;
   int tindex = 0;
   int sep;
   int token;
   int first;
   
   first = (orphan == 0);
   while (*lp)
   {
      tp [tindex] = NULL;
      sep = 0;
      while (1)
      {
         token = 0;
         switch (*lp)
         {
            case  ' ': if (sep == 0)               sep = ' ';  break;
            case  ',': if (sep == 0 || sep == ' ') sep = ',';  break;
            case  ';': 
            case  '.': if (sep != ';')             sep = ';';  break;
            case '\n': 
            case 0:    token = -1;                 sep = '\n'; break;
            default:   token = 1;                              break;
         }
         if (token)
         {
            if (ew) *ew = '\0';
            break;
         }
         lp++;
      }
      if (tindex) 
      {
         if (first && sep == ',') sep = ';';
         first = (sep == ';');
         separator [tindex] = sep;
      }
      if (separator [tindex] == ' ' && separator [tindex - 1] == ',')
         separator [tindex - 1] = ';';
      if (token < 0) break;
      tp [tindex] = lp;
      while (*lp && ! strchr (" ,.;\n", *lp))
      {
         *lp = tolower (*lp);
         lp++;
      }
      sep = 0;
      ew = lp;
      tindex++;
   }
   tp [tindex] = NULL;
   return;      
}

#ifdef __STDC__
void input (int textref)
#else
void input (textref)
int textref;
#endif
{
   int type;
   int refno;
   long tadr;
   int continuation;
   char *wp;
   int typo = 0;

   if (value [STATUS] < 90)
      amatch = 1;
   else if (value [STATUS] == 99)
      amatch = 0;
   else
      amatch = -1;
      
#if STYLE >= 11
   *orig1 = '\0';
   *orig2 = '\0';
#endif
   *bitword (ARG1) = -1;        /* Just in case! */
   *bitword (ARG2) = -1; 

#ifdef ALL
   if (value_all)
   {
      default_to (2, location_all, type_all);
      if (value_all)
         return;
   }
   else
   {
      arg1 = value [ARG1];
      arg2 = value [ARG2];
   }
#else /* not ALL */
   arg1 = value [ARG1];
   arg2 = value [ARG2];
#endif /* ALL */

#ifdef PLSCLARIFY
   if (bitest ((STATUS), (PLSCLARIFY)))
   {
      orphan = arg1;
      (void) strncpy (orphan_word, arg1_word, 20);
   }
   else
      orphan = 0;
   bitmod ('c', (STATUS), (PLSCLARIFY));
#endif /* PLSCLARIFY */
      
   continuation = (tindex != 0 && tp [tindex] && separator [tindex] == ',');
   if (separator [tindex] == ';')
   {
      value [ARG1] = -1;
      value [ARG2] = -1;
      outchar ('\n');
   }

restart:
   if (tp [tindex] == NULL)
   {
      if (raw_comline [0] != '\0' && raw_comline [0] != '\n')
         (void) strncpy (old_comline, raw_comline, 160);
      comline [0] = '\0';
      while (comline [0] == '\0' || comline [0] == '\n')
      {
#ifdef AGAIN
         fresh_line = 1;
#endif /* AGAIN */
#ifdef LOC_STATS
         (void) printf ("\n(Locates: demanded %ld (+%ld), faults %ld (+%ld))",
            locate_demands, locate_demands - old_demands, 
            locate_faults, locate_faults - old_faults);
         old_demands = locate_demands;
         old_faults = locate_faults;
#endif /* LOC_STATS */
         (void) scrchk (1);
         if (textref)
            (void) say (0, textref, 0);
         if (! lptr) lptr = text_buf;
         getinput (comline, 160);
#ifdef vms
         (void) putchar ('\n');        /* VMS... sigh... */
#endif /* vms */
         (void) strncpy (raw_comline, comline, 160);
#ifdef CONTEXT
         if (value [CONTEXT] && (*comline == '\n' || *comline == '\0'))
         {
            value [STATUS] = 0;
            value [ARG1] = -1;
            value [ARG2] = -1;
            return;
         }
#endif /* CONTEXT */
      }
      (void) scrchk (1);

retry:
      parse ();
      tindex = 0;
      value [ARG1] = -1;
      value [ARG2] = -1;
      value [STATUS] = 0;
   }

if (tp[tindex] == NULL)
   goto restart;
   
get_arg1:

#if STYLE >= 11
   *orig1 = '\0';
   typo = find_word (&type, &refno, &tadr, &olen1, &ovoc1, 
      separator [tindex] == ',' ? 2 : 1);
#else
   typo = find_word (&type, &refno, &tadr);
#endif
   tindex++;
   if (type == NOISE)
   {
      if (tp [tindex] == NULL) goto restart;
      if (separator [tindex] == ' ' || separator [tindex] == ',')
         goto get_arg1;
   }

#ifdef AGAIN
#if STYLE == 11
   if (refno == AGAIN &&
      ! ((separator [tindex] == ' ' || separator [tindex] == ',') && 
         tp[tindex-1][0] == 'r' && tp[tindex-1][1] == '\0'))
   {
      if (separator [tindex] == ' ' || separator [tindex] == ',')
      {
         value [ARG1] = -AGAIN;
         goto get_arg2;
      }
      else
#else
   if (refno == AGAIN)
   {
#endif /* STYLE == 11 */
      if (fresh_line)
      {
         if (*old_comline == '\n')
            goto restart;

         (void) strncpy (comline, old_comline, 160);
         (void) strncpy (raw_comline, old_comline, 160);
         goto retry;
      }
      else
      {
         tindex--;
         while (separator [++tindex] == ' ');
         value [ARG1] = arg1;     /* arg1/2_word still valid!  */
         value [ARG2] = arg2;     /* as are value [STATUS] and */
         return;                  /* varbits of STATUS         */
      }
   }

#endif /* AGIAN */
#ifdef PLSCLARIFY
   if ((bitest (STATUS, PLSCLARIFY) && refno <= LPLACE) || continuation)
   {
      value [ARG1] = arg1;
      value [ARG2] = refno;
#if STYLE >= 11
      if (refno == BADWORD || refno == AMBIGWORD || refno == AMBIGTYPO)
#else
#  if STYLE == 1
      if (refno == BADWORD)
#  else
      if (refno == BADWORD || refno == AMBIGWORD)
#  endif
#endif
         (void) strncpy (arg2_word, tp [tindex - 1], WORDSIZE);
      else
      {
#if STYLE >= 11
         if (typo)
         {
            typo = 0;
            (void) strncpy (orig2, tp [tindex - 1], WORDSIZE);
            ovoc2 = ovoc1;
            olen2 = olen1;
         }
         else
            *orig2 = '\0';
#endif /* STYLE >= 11 */
         (void) advcpy (arg2_word, tadr);
#ifdef DWARVEN
         if (value [DWARVEN] || extra_dwarvish)
         {
            char *wp = arg2_word;
            while (*wp)
               shift_up (wp++);
         }
#endif /* DWARVEN */
      }
      value [STATUS] = 2;
      goto got_command;
   }
#endif /* PLSCLARIFY */
   value [ARG1] = refno;
#if STYLE >= 11
   if (refno == BADWORD || refno == AMBIGWORD || refno == AMBIGTYPO)
#else
#  if STYLE == 1
   if (refno == BADWORD)
#  else
   if (refno == BADWORD || refno == AMBIGWORD)
#  endif
#endif
      (void) strncpy (arg1_word, tp [tindex - 1], 20);
   else
   {
#if STYLE >= 11
      if (typo)
      {
         typo = 0;
         (void) strncpy (orig1, tp [tindex - 1], WORDSIZE);
#ifdef DWARVEN
         if (value [DWARVEN]) shift_down (orig1, WORDSIZE);
#endif
      }
      else
         *orig1 = '\0';
#endif
      (void) advcpy (arg1_word, tadr);
#ifdef DWARVEN
      if (value [DWARVEN] || extra_dwarvish)
      {
         char *wp = arg1_word;
         while (*wp)
            shift_up (wp++);
      }
#endif /* DWARVEN */
   }
   value [STATUS] = 1;

get_arg2:
   if (separator [tindex] == ' ' && tp [tindex])
   {
#if defined(FIRST_SPECIAL) && defined(LAST_SPECIAL)
      int bmatch = amatch;
      if (amatch == 1)
         amatch = (value [ARG1] < FIRST_SPECIAL || value [ARG1] > LAST_SPECIAL);
#endif
#if STYLE >= 11
      *orig2 = '\0';
      typo = find_word (&type, &refno, &tadr, &olen2, &ovoc2, 2);
#else
      typo = find_word (&type, &refno, &tadr);
#endif
#if defined(FIRST_SPECIAL) && defined(LAST_SPECIAL)
      amatch = bmatch;
#endif
      tindex++;
      if (type == NOISE)
         goto get_arg2;

      value [ARG2] = refno;
#if STYLE >= 11
      wp = (refno == BADWORD || refno == AMBIGWORD || refno == AMBIGTYPO) ?
#else
#  if STYLE == 1
      wp = (refno == BADWORD) ?
#  else
      wp = (refno == BADWORD || refno == AMBIGWORD) ?
#  endif
#endif
         tp [tindex - 1] : &text [tadr];

#if STYLE >= 11
      if (refno == BADWORD || refno == AMBIGWORD || refno == AMBIGTYPO)
#else
#  if STYLE == 1
      if (refno == BADWORD)
#  else
      if (refno == BADWORD || refno == AMBIGWORD)
#  endif
#endif
         (void) strncpy (arg2_word, tp [tindex - 1], 20);
      else 
      {
#if STYLE >= 11
         if (typo)
         {
            typo = 0;
            (void) strncpy (orig2, tp [tindex - 1], WORDSIZE);
#ifdef DWARVEN
            if (value [DWARVEN]) shift_down (orig2, WORDSIZE);
#endif
         }
         else
            *orig2 = '\0';
#endif
         (void) advcpy (arg2_word, tadr);
#ifdef DWARVEN
         if (value [DWARVEN] || extra_dwarvish)
         {
            char *wp = arg2_word;
            while (*wp)
               shift_up (wp++);
         }
#endif /* DWARVEN */
      }
      value [STATUS] = 2;

#if STYLE >= 11
      if ((refno == BADWORD || refno == AMBIGTYPO) && 
         btfind (word_buf, tp [tindex - 1]))
            value [ARG2] = SCENEWORD;
#endif /* STYLE >= 11 */
   }

got_command:
#ifdef AGAIN
   fresh_line = 0;
#endif /* AGAIN */
   if (value [STATUS] == 1 && orphan)
   {
      value [STATUS] = 2;
      value [ARG2] = orphan;
      (void) strncpy (arg2_word, orphan_word, 20);
   }

   if (   value [ARG1] == BADWORD   || value [ARG2] == BADWORD
#if STYLE > 1
       || value [ARG1] == AMBIGWORD || value [ARG2] == AMBIGWORD
#endif
#if STYLE >= 11
       || value [ARG1] == AMBIGTYPO || value [ARG2] == AMBIGTYPO
#endif
                                                                 )
         tp [tindex] = NULL;    /* Forget rest of command */
#if STYLE < 11
   else if (value [STATUS] == 2 && (bitest (value [ARG2], VERB)) &&
      !(bitest (value [ARG1], VERB)))
#else /* STYLE >= 11 */
   else if (value [STATUS] == 2 && value [ARG2] != SCENEWORD && 
      (bitest (value [ARG2], VERB)) && !(bitest (value [ARG1], VERB)))
#endif /* STYLE */
   {
      int temp_val;
      temp_val = value [ARG1];
      value [ARG1] = value [ARG2];
      value [ARG2] = temp_val;
      (void) strncpy (temp_word, arg1_word, 20);
      (void) strncpy (arg1_word, arg2_word, 20);
      (void) strncpy (arg2_word, temp_word, 20);
#if STYLE > 11
      temp_val = ovoc1;
      ovoc1 = ovoc2;
      ovoc2 = temp_val;
      temp_val = olen1;
      olen1 = olen2;
      olen2 = temp_val;
#endif
   }
   arg1_word [19] = '\0';
   arg2_word [19] = '\0';
#ifdef DWARVISH
   if (value[DWARVEN])
   {
      shift_down (arg1_word, WORDSIZE);
      shift_down (arg2_word, WORDSIZE);
   }
#endif
   if (separator [tindex] == ' ')
   {
      if (tp [tindex] && strcmp (tp [tindex], "and") == 0 && 
         separator [++tindex] == ' ')
            separator [tindex] = ',';
      else
      {
         while (separator [++tindex] == ' ');
#if STYLE >= 11
         if (value [STATUS] == 2)
            value [STATUS] = BADSYNTAX;
      }
   }
#ifdef AGAIN
   if (value [ARG1] == -AGAIN && value [STATUS] > 1)
   {
      value [ARG1] = AGAIN;
      value [STATUS] = BADSYNTAX;
   }
#endif /* AGAIN */
   if (value [STATUS] == BADSYNTAX || value [ARG1] > STATUS || 
       value [ARG2] > STATUS)       /* Bad command! Ignore rest of line */
          while (tp [tindex]) tindex++;
#else
      }
   }
#endif
   return;
}

#ifdef __STDC__
int query (int textref)
#else
int query (textref)
int textref;
#endif
{
   char reply [10];
   char *rp;
   int which = 0;

   if (textref >= 0)
      say (0, textref, 0);
   else
      (void) scrchk (1);

try_again:
   getinput (reply, 10);
   (void) scrchk (1);
#ifdef DWARVEN
   if (value [DWARVEN])  shift_down (reply, 10);
#endif /* DWARVEN */
   rp = reply;
   if (*rp == '\0' || *rp == '\n') return (1);
   while (*rp == ' ') rp++;
   if (*rp == 'y' || *rp == 'Y') return (1);
   if (*rp == 'n' || *rp == 'N') return (0);
   if (*rp == 'q' || *rp == 'Q') return (0);
   if (which)
   {
      PRINTF ("(OK, smartass... I'll assume you mean YES - so there!)\n \n");
      return (1);
   }
   PRINTF ("Eh? Do me a favour and answer yes or no!\nWhich will it be? ");
   which = 1;
   goto try_again;
}

#ifdef __STDC__
void make_name (char *file_name, char *save_name)
#else
void make_name (file_name, save_name)
char *file_name;
char *save_name;
#endif
{
   char *cptr;                 /* Discardable pointer to file_name */

   (void) strncpy (save_name, file_name, 32);
   cptr = save_name;
   while (*cptr)
   {
      if (*cptr == '\n')
      {
         *cptr = '\0';            /* Strip off trailing \n, if any */
         break;
      }
#if defined (MSDOS) || defined (vms) || defined (_WIN32)
      if (*cptr == '.')
         *cptr = '-';     /* DOMESTOS doesn't like double suffixes */
#endif /* MSDOS or VMS or Windows */
      cptr++;
   }
   
#ifdef MSDOS
   *(save_name + 8) = '\0';
#else /* !MSDOS */
   *(save_name + 16) = '\0';
#endif /* MSDOS */
   if (strcmp (save_name + strlen (save_name) - 4, ".adv") != 0)
      (void) strcat (save_name, ".adv");
   return;
}

#ifdef __STDC__
void close_files (void)
#else
void close_files ()
#endif
{
   if (com_file)
      fclose (com_file);
      
   if (log_file)
   {
      int cnt;
      fprintf (log_file, "\nINTERACT\n");
      for (cnt = 0; cnt < 39; cnt++)
         fprintf (log_file, "*-");
      fprintf (log_file, "*\n");
      fclose (log_file);
   }
#if STYLE >= 11
   if (word_buf) free (word_buf);
#endif
}
#ifdef __STDC__
int special (int key, int *var)
#else
int special (key, var)
int key;
int *var;
#endif
{
   static char save_name [32];
   static char *image_base = NULL;
   char *image_ptr;
   char file_name [20];
   char save_title [32];
   FILE *game_file;
   int val, val1;
   long lval;
   char tval [sizeof (time_t)];
   long chksum;
   long chksav;
   char *cptr;
   int cnt;
   static int saved_value;
   static long game_time;
   struct stat statbuf;
   void adv_hours ();
   void adv_news ();

   switch (key)
   {
      case 1:          /* Dump game to disc */
      case 2:          /* Restore game from disc */
         val = value [ARG2];
try_again:
         if (val >= 0)
            (void) strncpy (file_name, arg2_word, 16);
         else
#ifdef CONTEXT
         {
            printf ("*** Glitch! No save/restore name specified!\n");
            *var = 3;
            return (0);
         }
      case 999:        /* Restore context */
      case 997:        /* Restore from context comline */
         if (key > 2)
            (void) make_name (cgi_name, save_name);
         else
            (void) make_name (file_name, save_name);
#else
         {
            if (key == 1)
            {
               PRINTF ("\nName to save game under: ");
            }
            else
            {
               PRINTF ("\nName of saved game to restore: ");
            }
            getinput (file_name, 16);
            scrchk(1);
#ifdef DWARVEN
            if (value [DWARVEN]) shift_down (file_name, 16);
#endif /* DWARVEN */
            if (file_name [0] == '\0' || file_name [0] == '\n')
            {
               PRINTF ("\nChanged your mind, eh?  Fine by me...\n");
               *var = 3;
               return (0);
            }
         }
         (void) make_name (file_name, save_name);
#endif /* CONTEXT */
      case 996:
         if (key == 996)
         {
            sprintf (raw_comline, "\nRestoring game '%s'...\n \n", dump_name);
            PRINTF (raw_comline);
            (void) make_name (dump_name, save_name);   
         }
         if ((game_file = fopen (save_name, RMODE)) != NULL)
         {
            if (key == 2 || key == 999 || key == 997 || key == 996) 
               goto restore_it;
            (void) fclose (game_file);
            PRINTF ("\nThere's already a game dumped under that name.\n");
#ifdef CONTEXT
            *var = 2;
            return (0);
#else
            PRINTF ("Do you really mean to overwrite it? ");
            if (!query (-1))
            {
               val = -1;
               goto try_again;
            }
            PRINTF ("\nAs you wish...\n");
#endif /* CONTEXT */
         }
         if (key == 2 || key == 996)
         {
            if (key == 996)
            {
               PRINTF ("Failed to open save file!\n \n");
            }
            *var = 1;
            return (0);
         }
#ifdef CONTEXT
      case 998:
         if (key == 998) 
         {
            make_name (cgi_name, save_name);
            if (value [CONTEXT] == 0) value [CONTEXT] = 1;
            *qcon = value [CONTEXT];
         }
         else
         {
            if (key != 1) return (0);
         }
#endif /* CONTEXT */
         if ((game_file = fopen (save_name, WMODE)) == NULL)
         {
#ifdef CONTEXT
            if (key != 998) *var = 1;
#endif /* CONTEXT */
            return (1);
         }
         (void) time ((time_t *) &tval[0]);
         (void) fprintf (game_file, "%s\n", DBNAME);
         val = FOBJECT;
         (void) fwrite (&val, sizeof (int), 1, game_file);
         val = LOBJECT;
         (void) fwrite (&val, sizeof (int), 1, game_file);
         val = LPLACE;
         (void) fwrite (&val, sizeof (int), 1, game_file);
         val = LVERB;
         (void) fwrite (&val, sizeof (int), 1, game_file);
         val = LVARIABLE;
         (void) fwrite (&val, sizeof (int), 1, game_file);
         val = LTEXT;
         (void) fwrite (&val, sizeof (int), 1, game_file);
         chksum = 0;
         CHKSUM(tval, sizeof(tval))
         CHKSUM(value, sizeof(value))
         CHKSUM(location, sizeof(location))
         CHKSUM(objbits, sizeof(objbits))
         CHKSUM(placebits, sizeof(placebits))
         CHKSUM(varbits, sizeof(varbits))
#ifdef CONTEXT
         if (cgi && key == 998)
         {
            CHKSUM(qwords, sizeof(qwords));
            CHKSUM(qvals, sizeof(qvals));
         }
#endif /* CONTEXT */
         (void) fwrite (&chksum, sizeof (long), 1, game_file);
         (void) fwrite (tval, 1, sizeof(tval), game_file);
         (void) fwrite (value, sizeof (int), 
            sizeof (value) / sizeof(int), game_file);
         (void) fwrite (location, sizeof (int), 
            sizeof (location) / sizeof (int), game_file);
         (void) fwrite (objbits, sizeof (short), 
            sizeof (objbits) / sizeof (short), game_file);
         (void) fwrite (placebits, sizeof (short), 
            sizeof (placebits) / sizeof (short), game_file);
         (void) fwrite (varbits, sizeof (short), 
            sizeof (varbits) / sizeof (short), game_file);
#ifdef CONTEXT
         if (cgi && key == 998)
         {
            (void) fwrite (qwords, sizeof (char), sizeof (qwords), game_file);
            (void) fwrite (qvals, sizeof (char), sizeof (qvals), game_file);
            (void) fwrite (&mainseed, sizeof (long), 1, game_file);
            (void) fwrite (word_buf, sizeof (short), *word_buf - 1, game_file);
            (void) fwrite (old_comline, sizeof (char), sizeof (old_comline),
               game_file);
         }
#endif /* CONTEXT */
         (void) fclose (game_file);
         if (ferror (game_file))
         {
            *var = 1;
            return (1);
         }
         *var = 0;
         return (0);

restore_it:
#ifdef CONTEXT
         if (cgi == 'x')
         {
            fprintf (log_file, "\nREPLY: restore %s\n", save_name);
            *qstat = 2;
            *qarg2 = value [ARG2];
            strncpy (qargw2, arg2_word, 20);
         }
#endif
         val1 = 0;
         (void) fscanf (game_file, "%s", save_title);
         (void) fgetc (game_file);         /* Skip \n */
         if (strcmp (save_title, DBNAME) == 0)
         {
            (void) fread (&val, sizeof (int), 1, game_file);
#ifdef DEBUG
            printf ("FOBJECT: image %3d, expected %3d\n", val, FOBJECT);
#endif /* DEBUG */
            if (val != FOBJECT) val1++;
            (void) fread (&val, sizeof (int), 1, game_file);
#ifdef DEBUG
            printf ("LOBJECT: image %3d, expected %3d\n", val, LOBJECT);
#endif /* DEBUG */
            if (val != LOBJECT) val1++;
            (void) fread (&val, sizeof (int), 1, game_file);
#ifdef DEBUG
            printf ("LPLACE: image %3d, expected %3d\n", val, LPLACE);
#endif /* DEBUG */
            if (val != LPLACE) val1++;
            (void) fread (&val, sizeof (int), 1, game_file);
#ifdef DEBUG
            printf ("LVERB: image %3d, expected %3d\n", val, LVERB);
#endif /* DEBUG */
            if (val != LVERB) val1++;
            (void) fread (&val, sizeof (int), 1, game_file);
#ifdef DEBUG
            printf ("LVARIABLE: image %3d, expected %3d\n", val, LVARIABLE);
#endif /* DEBUG */
            if (val != LVARIABLE) val1++;
            (void) fread (&val, sizeof (int), 1, game_file);
#ifdef DEBUG
            printf ("LTEXT: image %3d, expected %3d\n", val, LTEXT);
#endif /* DEBUG */
            if (val > LTEXT) val1++;
         }
         if (val1)
         {
            *var = 2;
            (void) fclose (game_file);
            return (0);
         }
         chksav = 0;
#ifdef DEBUG
         puts ("Reading image...");
#endif
         (void) fread (&chksav, sizeof (long), 1, game_file);
         (void) fread (tval, 1, sizeof (tval), game_file);
         (void) fread (value, sizeof (int), val, game_file);
         (void) fread (location, sizeof (int), 
            sizeof (location) / sizeof (int), game_file);
         (void) fread (objbits, sizeof (short), 
            sizeof (objbits) / sizeof (short), game_file);
         (void) fread (placebits, sizeof (short), 
            sizeof (placebits) / sizeof (short), game_file);
         (void) fread (varbits, sizeof (short), 
            sizeof (varbits) / sizeof (short), game_file);
#ifdef CONTEXT
         if (cgi && key == 999)
         {
            (void) fread (qwords, sizeof (char), sizeof (qwords), game_file);
            (void) fread (qvals, sizeof (char), sizeof (qvals), game_file);
            (void) fread (&mainseed, sizeof (long), 1, game_file);
            if (! ferror (game_file))
            {
               (void) fread (word_buf, sizeof (short), 2, game_file);
               if (ferror (game_file))
               {
                  *word_buf = 3;
                  *(word_buf + 1) = 0;
               }
               else
                  (void) fread (word_buf + 2, sizeof (short),
                     *word_buf - 3, game_file);
            }
            if (! ferror (game_file))
            {
               (void) fread (old_comline, sizeof (char), sizeof (old_comline),
                   game_file);
            }
            clearerr (game_file);
         }
#endif /* CONTEXT */
         if (ferror (game_file))
         {
            *var = 2;
            return (0);
         }
#ifdef DEBUG
         puts ("Checking image...");
#endif
         (void) fclose (game_file);
         chksum = 0;
         CHKSUM(tval, sizeof(tval))
         CHKSUM(value, (val) * sizeof(value[0]))
         CHKSUM(location, sizeof(location))
         CHKSUM(objbits, sizeof(objbits))
         CHKSUM(placebits, sizeof(placebits))
         CHKSUM(varbits, sizeof(varbits))
#ifdef CONTEXT
         if (cgi && key == 999)
         {
            CHKSUM(qwords, sizeof(qwords));
            CHKSUM(qvals, sizeof(qvals));
         }
#endif /* CONTEXT */
         if (chksav != chksum)
         {
            *var = 2;
            return (0);
         }
         memcpy (&game_time, tval, sizeof (long));
#ifdef CONTEXT
         if (key == 997) value [CONTEXT] = 2;
#endif
#ifdef MOVED
         if (key == 996)
            bitmod ('s', STATUS, MOVED);
#endif /* MOVED */
         *var = 0;
         return (0);
      case 3:          /* Delete saved game */
#ifdef CONTEXT
         (void) make_name (arg2_word, save_name);
#endif         
         *var = unlink (save_name);
         return (0);
      case 4:          /* Spare */
      case 5:          /* Spare */
         *var = 0;
         return (0);
      case 6:          /* Save value of a variable (only one can be saved!) */
         saved_value = *var;
         return (0);
      case 7:          /* Restore saved variable value */
         *var = saved_value;
         return (0);
      case 8:          /* Get minutes since restored game dumped */
         (void) time ((time_t *) &lval);
         *var = 1 + (lval - game_time) / 60;      /* Be generous! */
         return (0);
      case 9:         /* Fudge a value into ARG1 */
      case 10:        /* Fudge a value into ARG2 */
         value [(key == 9) ? ARG1 : ARG2] = *var;
         return (0);
      case 11:         /* Pretend player said "X X" instead of "X" */
         value [ARG2] = value [ARG1];
         strncpy (arg2_word, arg1_word, 20);
         value [STATUS] = 2;
         return (0);
      case 12:         /* Spare */
         *var = 0;
         return (0);
      case 13:         /* Spare */
         *var = 0;
         return (0);
      case 14:         /* Check for virgin data file */
#ifdef CONTEXT
         if (cgi)
            *var = stat ("adv.vrg", &statbuf) ? 1 : 0;
         else
#endif
            *var = virgin == 'v' ? 1 : 0;
         return (0);
      case 15:         /* Note that he meditated, as he should */
#ifdef CONTEXT
         if (cgi)
            rape_file = fopen ("adv.vrg", "wb");
         else 
#endif
            if (virgin == 'v' && 
            (rape_file = fopen (data_file, "r+")) != NULL)
               (void) fputc ('w', rape_file);
         if (rape_file) fclose (rape_file);
         return (0);
      case 16:        /* Initial restore */
         *var = 0;
         if (dump_name)
         {
            strncpy (file_name, dump_name, 16);
            strcat (file_name, "\n");
            if (log_file)
               fprintf (log_file, "REPLY: %s\n", file_name);
            dump_name = NULL;
         }
         else
         {
            PRINTF (
               "\n \nGame to restore (or press ENTER for a brand new game): ");
            getinput (file_name, 16);
         }
         (void) scrchk (1);
         if (*file_name == '\n' || *file_name == '\0')
            return (0);
         value [ARG2] = 0;
         (void) strcpy (arg2_word, file_name);
         *(arg2_word + strlen (arg2_word) - 1) = '\0';
         value [STATUS] = 2;
         *var = 1;
         return (0);
      case 17:    /* Memory save */
         *var = 1;
         val = sizeof (value) + sizeof (location) +
               sizeof (objbits) + sizeof (placebits) + sizeof (varbits);
         if (image_base == NULL)
         {
            image_base = (char *) malloc (val);
            if (image_base == NULL)
               return (0);
         }
         image_ptr = image_base;
#define STASH(X,Y,Z) memcpy (X,Y,Z); X += Z
         STASH (image_ptr, value, sizeof (value));
         STASH (image_ptr, location, sizeof (location));
         STASH (image_ptr, objbits, sizeof (objbits));
         STASH (image_ptr, placebits, sizeof (placebits));
         STASH (image_ptr, varbits, sizeof (varbits));
#ifdef CONTEXT
         if (cgi)
         {
            FILE *memory_file;
            if ((memory_file = fopen (".M.adv", WMODE)) == NULL)
               return (0);
            if (fwrite (image_base, sizeof (char), val, memory_file) == val)
               *var = 0;
            fclose (memory_file);
         }
         else
            *var= 0;
#else
         *var = 0;
#endif
         return (0);
      case 18:    /* Memory restore */
         *var = 1;
         val = sizeof (value) + sizeof (location) +
               sizeof (objbits) + sizeof (placebits) + sizeof (varbits);
#ifdef CONTEXT
         if (cgi)
         {
            FILE *memory_file;
            if ((image_base = (char *) malloc (val)) == NULL ||
                (memory_file = fopen (".M.adv", RMODE)) == NULL ||
                (fread (image_base, sizeof (char), val, memory_file)) != val)
                   return (0);
         }
         else if (image_base  == NULL)
            return (0);
#else
         if (image_base  == NULL)
            return (0);
#endif /* CONTEXT */

         image_ptr = image_base;
#define UNSTASH(X,Y,Z) memcpy (Y,X,Z); X += Z
         UNSTASH (image_ptr, value, sizeof (value));
         UNSTASH (image_ptr, location, sizeof (location));
         UNSTASH (image_ptr, objbits, sizeof (objbits));
         UNSTASH (image_ptr, placebits, sizeof (placebits));
         UNSTASH (image_ptr, varbits, sizeof (varbits));
         *var = 0;
         return (0);
         
      case 19:    /* Fiddle justification */
         val = *var;
         justify = val < 2 ? val : 1 - justify;
         *var = justify;
         return (0);
         
      case 20:    /* Set screen line length */
         val = atoi (arg2_word);
         *var = 0;
         if (val == 0) return (0);
         if (val < 16) val = 16;
         if (val > 1024) val = 1024;
         *var = val;
         Linlen = val;
         if (Linlen - 2 * Margin < 16)
            Margin = (Linlen - 16) / 2;
         if (Margin < 0) Margin = 0;
         Maxlen = Linlen - 2 * Margin;
         return (0);

      case 21:    /* Set page offset */
         val = atoi (arg2_word);
         *var = 0;
         if (val <0) val = 0;
         if (val > 9) val = 9;
         if (Linlen - val - val < 16)
            val = (Linlen - 16) / 2;
         if (val < 0) val = 0;
         *var = val;
         Margin = val;
         Maxlen = Linlen - val - val;
         return (0);

      case 22:    /* Set screen depth */
         val = atoi (arg2_word);
         if (val < 4)
         {
            *var = 0;
            return (0);
	 }
         if (val > 1024) val = 1024;
         *var = val;
         Screen = val;
         return (0);

      case 23:    /* Preserve player input */
         *qtext = *var;
         *qstat = value [STATUS];
         *qarg1 = value [ARG1];
         strncpy (qargw1, arg1_word, 20);
         if (*qstat == 2)
         {
            *qarg2 = value [ARG2];
            strncpy (qargw2, arg2_word, 20);
         }
         else
         {
            *qarg2 = -1;
            *qargw2 = '\0';
         }
         return (0);

      case 24:    /* Restore player input */
         *var = *qtext;
         value [STATUS] = *qstat;
         value [ARG1] = *qarg1;
         value [ARG2] = *qarg2;
         strncpy (arg1_word, qargw1, 20);
         strncpy (arg2_word, qargw2, 20);
         return (0);

      case 25:    /* Check for running as CGI */
#ifdef CONTEXT
         *var = cgi ? 1 : 0;
#else
         *var = 0;
#endif
         return (0);

      case 26:    /* Check for being in a "do all" loop */
         *var = value_all;
         return (0);

      case 27:    /* Report ARG1 typo, if any */
         *var = 0;
#if STYLE >= 11         
         if (*orig1)
         {
            char save_char;
            say (QUAL_FLAG, *var, ORG1);
            advcpy (orig1, ovoc1);
            save_char = *(orig1 + olen1);
            *(orig1 + olen1) = '\0';
            say (QUAL_FLAG, *var, ORG1);
            *(orig1 + olen1) = save_char;
            if (olen1 >= strlen (orig1)) 
               value [*var]++;
            else
               say (QUAL_FLAG, *var, ORG1);
            say (0, *var, 0);
            *orig1 = '\0';
            *var = 1;
         }
#endif
         return (0);
         
      case 28:    /* Report ARG2 typo, if any */
         *var = 0;
#if STYLE >= 11
         if (*orig2)
         {
            char save_char;
            say (QUAL_FLAG, *var, ORG2);
            advcpy (orig2, ovoc2);
            save_char = *(orig2 + olen2);
            *(orig2 + olen2) = '\0';
            say (QUAL_FLAG, *var, ORG2);
            *(orig2 + olen2) = save_char;
            if (olen2 >= strlen (orig2)) 
               value [*var]++;
            else
               say (QUAL_FLAG, *var, ORG2);
            say (0, *var, 0);
            *orig2 = '\0';
            *var = 1;
         }
#endif
         return (0);
         
      case 29:    /* Swap ARG1 and ARG2 */
         *var = 0;
         if (value [STATUS] > 1)
         {
            val = value [ARG1];
            value [ARG1] = value [ARG2];
            value [ARG2] = val;
            for (cnt = 0; cnt < VARSIZE; cnt++)
            {
               val = varbits [ARG1 + cnt];
               varbits [ARG1 + cnt] = varbits [ARG2 + cnt];
               varbits [ARG2 + cnt] = val;
            }
            strcpy (temp_word, arg1_word);
            strcpy (arg1_word, arg2_word);
            strcpy (arg2_word, temp_word);
         }
         return (0);

      case 30:   /* Return 1 for ARG1 typo, 2 for ARG2 typo, 0 for none */
         *var = 0;
#if STYLE >= 11         
         if (*orig1)
            *var = 1;
         else if (*orig2)
            *var = 2;
#endif
         return (0);
         
      default:
         PRINTF2 ("\n \nGLITCH! Bad special code: %d\n", key);
         return (1);
   }
}

#ifdef __STDC__
int initialise (void)
#else
int initialise ()
#endif
{
#ifdef MEMORY
   long text_bytes;
#endif
   int index;
   int len;

   if ((text_buf = (char *) malloc (text_buf_len)) == NULL)
   {
      (void) printf ("Can't allocate text buffer!\n");
      return (1);
   }   
   lptr = text_buf;
   *lptr++ = '\n';
   text_len = 1;
#if STYLE >= 11
   word_buf = btinit (NULL);
#endif /* STYLE */

#ifdef CONTEXT
   if (cgi != 'y')
#else
   if (dump_name == NULL || *dump_name == '\0')
#endif
   {
      PRINTF ("\n[A-code kernel version 11.44; MLA, 30 Dec 2002]\n");
   }
   *data_file = '\0';
   if (SEP != '?')
   {
      char *ptr;
      ptr = strrchr (exec, SEP);
      if (ptr)
      {
         ptr++;
         len = ptr - exec;
      }
      else
      {
         ptr = exec;
         len = 0;
      }
      if (*log_name == '\0' && log_wanted)
      {
         strncat (log_name, ptr, sizeof (log_name));
         *(log_name + sizeof (log_name) - 1) = '\0';
         if (strlen (log_name) > 15)
            *(log_name + 15) = '\0';
         strcat (log_name, ".log");
      }
      
      if (dbs_dir)
      {
         strncpy (data_file, dbs_dir, sizeof (data_file) - 14);
         ptr = data_file + strlen (data_file);
         *ptr++ = SEP;
         *ptr = '\0';
      }
      else if (ptr)
      { 
         if (len > sizeof (data_file) - 13) len = sizeof (data_file) - 13;
         strncpy (data_file, exec, len);
      }
   }

   
   (void) strncat (data_file, DBNAME, 8);
   (void) strcat (data_file, ".dat");

   if ((text_file = fopen (data_file, RMODE)) == NULL)
   {
      (void) printf ("Sorry, can't find the %s data file.\n", DBNAME);
      close_files ();
      exit (0);
   }
#ifdef MEMORY
/*   (void) printf ("\nInitialising the universe - please wait...\n"); */
   text_bytes = fread (text, sizeof (char), TEXT_BYTES+1, text_file);
   (void) clearerr (text_file);
   (void) fclose (text_file);
   if (text_bytes != TEXT_BYTES)
   {
      (void) printf ("Wrong data file length!\n");
      return (1);
   }
#else /* not MEMORY */
/*   (void) setbuf (text_file, NULL);  */
#ifdef BUFFERS
   chunk_end [0] = fread (text, sizeof (char), TEXT_CHUNK, text_file) - 1;
   chunk_start [0] = 0;
#else /* not BUFFERS */
   chunk_end = fread (text, sizeof (char), TEXT_CHUNK, text_file) - 1;
   chunk_start = 0;
#endif /* BUFFERS */
#endif /* MEMORY */

   virgin = *text;
   title [0] = text [1] ^ 'x';
   titlen = 0;
   while (++titlen < 16)
      if ((title [titlen] = title [titlen - 1] ^ text [titlen + 1]) == '\0')
         break;
   
   if (strcmp (title, DBNAME) != 0)
   {
      (void) printf ("Data file does not belong to this program!\n");
      return (1);
   }
   tp [0] = NULL;

   for (index = 0; index < sizeof (location) / sizeof (location [0]); index++)
      location [index] = 0;
   
   for (index = 0; index < sizeof (objbits) / sizeof (objbits [0]); index++)
      objbits [index] = 0;
   
   for (index = 0; index < sizeof (placebits) / sizeof (placebits [0]); index++)
      placebits [index] = 0;
   
   for (index = 0; index < sizeof (varbits) / sizeof (varbits [0]); index++)
      varbits [index] = 0;   
   
   for (index = 0; index < sizeof (value) / sizeof (value [0]); index++)
      value [index] = 0;
       
   for (index = FOBJECT; index <= LOBJECT; index++)
      bitmod ('s', index, OBJECT);

   for (index = FPLACE; index <= LPLACE; index++)
      bitmod ('s', index, PLACE);

#if STYLE == 1 && defined(BRIEF)
   bitmod ('s', STATUS, BRIEF);
#endif

   if (com_name && *com_name && (com_file = fopen (com_name, "r")) == NULL)
   {
      (void) printf ("Sorry, unable to open command file '%s'!\n", com_name);
      exit (0);
   }
   if (com_file)
   {
      fgets (comline, sizeof (comline), com_file);
      if (strncmp (comline, DBNAME, strlen (DBNAME)) != 0)
      {
         printf ("%s: wrong adventure version!", com_name);
         exit (0);
      }
      mainseed = atol (comline + strlen (DBNAME) + 1);
   }

   if (*log_name)
   {
      if ((log_file = fopen (log_name, "a+")) == NULL)
         (void) printf ("(Sorry, unable to open log file...)\n");
#ifdef CONTEXT
      else if (cgi == 0 || cgi == 'x')
         (void) fprintf (log_file, "%s: %lu\n", DBNAME, mainseed);
#endif
   }

   return (0);
}

#ifdef GLK
int argc = 0;
char **argv = NULL;

#ifdef _WIN32
#include "WinGlk.h"
char* arglist[1] = { "" };

int winglk_startup_code(const char* cmdline)
{
#ifdef DBNAME

/* Hardwire some obvious names... */

   if (strncmp (DBNAME, "adv350", 6) == 0)
   {
      winglk_app_set_name("Adv350");
      winglk_window_set_title("Adventure 350");
   }
   else if (strncmp (DBNAME, "adv440", 6) == 0)
   {
      winglk_app_set_name("Adv440");
      winglk_window_set_title("Adventure 440");
   }
   else if (strncmp (DBNAME, "adv550", 6) == 0)
   {
      winglk_app_set_name("Adv550");
      winglk_window_set_title("Adventure 550");
   }
   else if (strncmp (DBNAME, "adv660", 6) == 0)
   {
      winglk_app_set_name("Adv660");
      winglk_window_set_title("Adventure 660");
   }
   else if (strncmp (DBNAME, "adv770", 6) == 0)
   {
      winglk_app_set_name("Adv770");
      winglk_window_set_title("Adventure 770");
   }
#endif /* DBNAME */
   argc = 1;
   argv = arglist;
   return 1;
}
#endif
#if defined(unix) || defined(linux)
#define glkunix_arg_End (0)
#define glkunix_arg_ValueFollows (1)
#define glkunix_arg_NoValue (2)
#define glkunix_arg_ValueCanFollow (3)
#define glkunix_arg_NumberValue (4)

typedef struct glkunix_argumentlist_struct {
    char *name;
    int argtype;
    char *desc;
} glkunix_argumentlist_t;

typedef struct glkunix_startup_struct {
    int argc;
    char **argv;
} glkunix_startup_t;

#ifdef __STDC__
int glkunix_startup_code(glkunix_startup_t *data)
#else
int glkunix_startup_code(data)
glkunix_startup_t *data;
#endif
{
   argc = data->argc;
   argv = data->argv;
   return 1;
}

glkunix_argumentlist_t glkunix_arguments[] = 
   {
      {"",   glkunix_arg_ValueFollows, "[<dumpfile]: game to restore"},
      {"-b", glkunix_arg_NoValue, "-b: toggle blank lines around prompt"},
      {"-d", glkunix_arg_ValueFollows, "-d <dirname>: dbs directory"},
      {"-r", glkunix_arg_ValueFollows, "[-r] <savefile>: restore game"},
      {"-c", glkunix_arg_ValueFollows, "-c <comfile>: replay game from log"},
      {"-l", glkunix_arg_ValueCanFollow, "-l [<logfile>]: log the game"},
      {"-h", glkunix_arg_NoValue, "-h: print help text"},
      {NULL, glkunix_arg_End, NULL }
   };
#endif /* unix || linux */
void glk_main (void)
#else
#  ifdef __STDC__
int main (int argc, char **argv)
#  else
int main (argc, argv)
int argc;
char **argv;
#  endif
#endif
{
   char *kwrd;
   int val;
   char *cptr;
   char *prog = *argv;
   char *opt;
   
   if (Linlen == 0) Linlen = 32767;
   if (Screen == 0) Screen = 32767;
   Maxlen = Linlen - 2 * Margin;
#ifdef GLK
   mainwin = glk_window_open(0, 0, 0, wintype_TextBuffer, 1);
   if (!mainwin)
   {
      fprintf (stderr, "Failed to open main window!\n");
      exit (0);
   }
    
   /* Set the current output stream to print to it. */
   glk_set_window (mainwin);
   
#endif
   strncpy (exec, *argv, sizeof (exec) - 1);
   if (argc > 1)
      while (--argc)
      {
         argv++;
         if (**argv != '-') 
         {
            if (! dump_name)
            {
               if (*argv) dump_name = *argv; 
               continue;
            }
            if (! log_name)
            {
               strncpy (log_name, *argv, sizeof (log_name)); 
               *(log_name + sizeof (log_name) - 1) = '\0';
               log_wanted = 1;
               continue;
            }
            if (! com_name)
            {
               com_name = *argv; 
               continue;
            }
         }
         kwrd = *argv + 1;
         if (*kwrd == 'j')
         {
            justify = 1 - justify;
            continue;
         }
         else if (*kwrd == 'b')
         {
            compress = 1 - compress;
            continue;
         }
         else if (*kwrd == 'p')
         {
            end_pause = 1 - end_pause;
            continue;
         }
         else if (*kwrd == 'l')
            log_wanted = 1;
         else if (*kwrd == 'h')
         {
            printf ("\nUsage: %s [options]\n\nOptions:\n", prog);
#ifndef GLK
            printf ("    -w                invert default wrap/justify setting\n");
            printf ("    -b                invert default setting for blank lines around prompt\n");
            printf ("    -s <W>x<H>[-<M>]  set screen size and margin\n");
#endif
            printf ("    -d <dbsdir>       specify dbs directory\n");
            printf ("   [-r] <dumpfile>    restore game from dump\n");
            printf ("    -c <cominfile>    replay game from log\n");
            printf ("    -l <logfile>      log the game\n");
            printf ("    -p                invert defaul setting for pause before exiting\n");
            printf ("    -h                print this usage summary\n");
            exit (0);
         }
         if (--argc == 0) break;
         argv++;
         opt = *argv;
         switch (*kwrd)
         {
            case 's':
               val = strtol (opt, &cptr, 10);
               if (val == 0) val = 32767;
               if (val >= 16 && val <= 32767)  Linlen = val;
               if (*cptr++)
               {
                  val = strtol (cptr, &cptr, 10);
                  if (val == 0) val = 32767;
                  if (val >= 16 && val <= 32767) Screen = val;
                  if (*cptr++)
                  {
                     val = strtol (cptr, (char **)NULL, 10);
                     if (val >= 0 && val < (Linlen - 16 )/ 2) Margin = val;
                  }
               }
               Maxlen = Linlen - 2 * Margin;
               break;
               
            case 'd':
               dbs_dir = opt;
               break;
               
            case 'l':
               strncpy (log_name, opt, sizeof (log_name));
               *(log_name + sizeof (log_name) - 1) = '\0';
               break;
               
            case 'c':
               com_name = opt;
               break;
               
            case 'r':
               if (*opt) dump_name = opt;
               break;
#ifdef CONTEXT
            case 'x':
            case 'y':
               cgi = *kwrd;
               strncpy (cgicom, opt, sizeof (cgicom));
               break;
#endif /* CONTEXT */               
            default:
               puts ("Bad args!");
               exit (0);
         }         
      }

#ifdef CGI
   if (cgi) compress = 1;
#endif
   if (mainseed == 0)
      (void) time ((time_t *) &mainseed);
   mainseed %= 32768L;
   
   if (initialise () != 0)
   {
      (void) printf ("Sorry, unable to set up the world.\n");
#ifdef GLK
      glk_exit ();
#else
      return (0);
#endif
   }

   value [THERE] = value [HERE] = FPLACE;

#ifdef CONTEXT
   if (cgi == 'x' && dump_name && *dump_name)
   {
      cgi_name = dump_name;
      special (997, &value [0]);
      cgi_name = ".C.adv";
   }
   else if (cgi == 'y')
      special (999, &value [0]);
   else
   {
      if (dump_name && *dump_name)
      {
         value [STATUS] = -1;
         strncpy (arg2_word, dump_name, WORDSIZE);
         *(arg2_word + WORDSIZE - 1) = '\0';
/*         special (996, &value [STATUS]);
 *         if (value [STATUS])
 *            exit (0);
 */
      }
      else     
      {
         (void) setjmp (loop_back);
         p1 ();
      }
   }
#else
   if (dump_name && *dump_name)
   {
      value [STATUS] = -1;
      strncpy (arg2_word, dump_name, WORDSIZE);
      *(arg2_word + WORDSIZE - 1) = '\0';
/*      special (996, &value [STATUS]);
 *      if (value [STATUS])
 *         exit (0);
 */
   }
   else
   {
      (void) setjmp (loop_back);
      p1 ();
   }
#endif /* CONTEXT */

   (void) setjmp (loop_back);
   if (quitting) 
   {
      if (end_pause)
      {
         PRINTF ("(To exit, press ENTER)");
         getinput (comline, 160);
         putchar ('\n');
      }
      else
      {
         if (text_len > 0)
            outbuf (1);
         putchar ('\n');
         putchar ('\n');
      }
      close_files ();
#ifdef GLK
      glk_exit ();
#else
      return (255);
#endif
   }

   while (1)
   {
      rseed = mainseed;
      (void) irand (1);
      mainseed = rseed;
      rseed = mainseed ^ 255;
      p2 ();
   }
}

#ifdef __STDC__
int have (int l1,int l2,int l3)
#else
int have (l1,l2,l3)
int l1;
int l2;
int l3;
#endif
{
   if (l1 > LOBJECT) return (0);
   if (location [l1] != INHAND) return (0);
   if (l2 < 0) return (1);
   if (l2 == 0)
   {
      if (value [l1] == l3) return (1);
   }
   else
      if (bitest (l1, l3)) return (1);
   return (0);
}

#ifdef __STDC__
int isat (int l1,int l2,int l3, int l4)
#else
int ishere (l1,l2,l3,l4)
int l1;
int l2;
int l3;
int l4;
#endif
{
   if (l1 > LOBJECT) return (0);
   if (l2 != -1)
   {
      if (l2 == 0)
      {
         if (value [l1] != l3) return (0);
      }
      else
         if (!(bitest (l1, l3))) return (0);
   }
   if (location [l1] == l4) return (1);
#ifdef SCHIZOID
   if (!(bitest (l1, SCHIZOID))) return (0);
   if (location [l1] + 1 == l4) return (1);
#endif
   return (0);
}

#ifdef __STDC__
int ishere (int l1,int l2,int l3)
#else
int ishere (l1,l2,l3)
int l1;
int l2;
int l3;
#endif
{
   return (isat (l1, l2, l3, value [HERE]));
}

#ifdef __STDC__
int isnear (int l1,int l2,int l3)
#else
int isnear (l1,l2,l3)
int l1;
int l2;
int l3;
#endif
{
   if (have (l1,l2,l3)) return (1);
   if (ishere (l1,l2,l3)) return (1);
   return (0);
}

#if !defined(NOVARARGS) && defined(__STDC__)
void move (int a1, int a2, ...)
{
   va_list ap;
   int arg_end;
   int kwrd;

   va_start (ap, a2);
   if (a2 < 0) goto gothere;
   arg_end = 0;
   while (!arg_end)
   {
      if ((kwrd = va_arg (ap, int)) < 0)
      {
         kwrd = -kwrd;
         arg_end = 1;
      }
      if (KEY (kwrd))
         goto gothere;
   }
   va_end (ap);
   return;
gothere:
   va_end (ap);
#else /* not (NOVARARGS && __STDC__)*/
#ifdef __STDC__
void move (int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8,
           int a9,int a10,int a11,int a12,int a13,int a14,int a15,int a16)
#else
void move (a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16)
int a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16;
#endif
{
   int kwrd;

   if (a2 < 0) goto gothere;
   if ((kwrd = a3) < 0) kwrd = -kwrd;
   if (KEY (kwrd)) goto gothere; else if (a3 < 0) return;
   if ((kwrd = a4) < 0) kwrd = -kwrd;
   if (KEY (kwrd)) goto gothere; else if (a4 < 0) return;
   if ((kwrd = a5) < 0) kwrd = -kwrd;
   if (KEY (kwrd)) goto gothere; else if (a5 < 0) return;
   if ((kwrd = a6) < 0) kwrd = -kwrd;
   if (KEY (kwrd)) goto gothere; else if (a6 < 0) return;
   if ((kwrd = a7) < 0) kwrd = -kwrd;
   if (KEY (kwrd)) goto gothere; else if (a7 < 0) return;
   if ((kwrd = a8) < 0) kwrd = -kwrd;
   if (KEY (kwrd)) goto gothere; else if (a8 < 0) return;
   if ((kwrd = a9) < 0) kwrd = -kwrd;
   if (KEY (kwrd)) goto gothere; else if (a9 < 0) return;
   if ((kwrd = a10) < 0) kwrd = -kwrd;
   if (KEY (kwrd)) goto gothere; else if (a10 < 0) return;
   if ((kwrd = a11) < 0) kwrd = -kwrd;
   if (KEY (kwrd)) goto gothere; else if (a11 < 0) return;
   if ((kwrd = a12) < 0) kwrd = -kwrd;
   if (KEY (kwrd)) goto gothere; else if (a12 < 0) return;
   if ((kwrd = a13) < 0) kwrd = -kwrd;
   if (KEY (kwrd)) goto gothere; else if (a13 < 0) return;
   if ((kwrd = a14) < 0) kwrd = -kwrd;
   if (KEY (kwrd)) goto gothere; else if (a14 < 0) return;
   if ((kwrd = a15) < 0) kwrd = -kwrd;
   if (KEY (kwrd)) goto gothere; else if (a15 < 0) return;
   if ((kwrd = a16) < 0) kwrd = -kwrd;
   if (KEY (kwrd)) goto gothere; return;
gothere:
#endif /* NOVARARGS && __STDC__ */

#if STYLE >= 11
   if (value [THERE] != value [HERE])
   {
      *word_buf = 3;
      *(word_buf + 1) = 0;
   }
#endif /* STYLE */
   value [THERE] = value [HERE];
   *bitword (THERE) = -1;
   value [HERE] = a1;
   *bitword (HERE) = -1;
#if defined (MOVED) && defined (STATUS)
   bitmod ('s', STATUS, MOVED);
#endif /* MOVED and STATUS */
   if (a2 < -2)
      a2 = -a2;
   if (a2 > 0)
      say (0, a2, 0);
   if (a2 != -1) longjmp (loop_back, 1);
   return;
}

#ifdef __STDC__
void apport (int l1,int l2)
#else
void apport (l1,l2)
int l1,l2;
#endif
{
#if defined (JUGGLED) && defined (STATUS)
   if (location [l1] == INHAND || l2 == INHAND)
      bitmod ('s', STATUS, JUGGLED);
#endif
   location [l1] =  (l2 <= LPLACE || l2 == INHAND) ? l2 : value [l2];
   return;
}

#ifdef __STDC__
void set (char t1, int v1, char t2, int v2, int *lv, short *lb)
#else
void set (t1, v1, t2, v2, lv, lb)
int t1, v1, t2, v2;
int *lv;
short *lb;
#endif
{
   int val, bts, cur = 0;
  
   if      (t2 == 'e') { val = value [v2]; bts = 0; } /* OBJECT, PLACE, TEXT */
   else if (t2 == 'c') { val = v2; bts = 0; }                    /* CONSTANT */
   else if (t2 == 'v') { val = value [v2];                       /* VARIABLE */
                       if (v2 == ARG1 || v2 == ARG2) bts = -1;
                       else bts = varbits [VARSIZE * v2]; }
   else  /* t2 == 'l'*/ { val = lv [v2];                            /* LOCAL */
                       bts = lb [VARSIZE * v2]; }
   if      (t1 == 'V') { value [v1] = val;                       /* VARIABLE */
                       cur = varbits [VARSIZE * v1]; }
   else if (t1 == 'L') { lv [v1] = val;                             /* LOCAL */
                       cur = lb [VARSIZE * v1]; }
   else  /* t1 == 'E'*/ value [v1] = val;             /* OBJECT, PLACE, TEXT */
   
   if      (t1 == 'V') {                                         /* VARIABLE */
      if      (bts == -1 && cur != -1) varbits [VARSIZE * v1] = -1;
      else if (bts != -1 && cur == -1) varbits [VARSIZE * v1] = 0; }
   else if (t1 == 'L') {                                            /* LOCAL */
      if      (bts == -1 && cur != -1) lb [VARSIZE * v1] = -1;
      else if (bts != -1 && cur == -1) lb [VARSIZE * v1] = 0; }
   else if (t1 == 'T')                                               /* TEXT */
   {
      val = text_info [2 * (v1 - FTEXT) + 1];
      if (val <= value [v1]) value [v1] = val - 1;
   }
}

#ifdef __STDC__
void lset (int l1, int l2, int l3)
#else
void lset (l1, l2, l3)
int l1,l2,l3;
#endif
{
   
}

#ifdef __STDC__
void lda (int l1, int l2)
#else
void lda (l1, l2)
int l1,l2;
#endif
{
   value [l1] = l2;
   *bitword (l1) = -1;
   textadr [l1] = textadr [l2];
   return;
}

#ifdef __STDC__
void eval (int l1, int l2)
#else
void eval (l1, l2)
int l1,l2;
#endif
{
   value [l1] = value [value [l2]];
   return;
}

#ifdef __STDC__
void deposit (int l1, int l2)
#else
void deposit (l1, l2)
int l1,l2;
#endif
{
    value [value [l1]] = (l2 > LVARIABLE || l2 < FVARIABLE) ? l2 :
       value [l2];
    return;
}

#ifdef __STDC__
void locate (int l1, int l2)
#else
void locate (l1, l2)
int l1,l2;
#endif
{
   value [l1] = location [(l2 < FVARIABLE || l2 > LVARIABLE) ? l2 :
      value [l2]];
   *bitword (l1) = -1;
   return;
}

#ifdef __STDC__
int evar (int l1)
#else
int evar (l1)
int l1;
#endif
{
   if (*bitword (l1) == -1)
      return value [l1];
   else
      return l1;
}

#ifdef __STDC__
int levar (int l1, int *l2, short *l3)
#else
int levar (l1, l2, l3)
int l1;
int *l2;
short *l3;
#endif
{
   if (*(l3 + VARSIZE * l1) == -1)
      return (*(l2 + l1));
   else
      return l1;
}

#ifdef __STDC__
void finita (void)
#else
void finita ()
#endif
{
#ifndef MEMORY
   (void) fclose (text_file);
#endif /* MEMORY */
#ifdef LOC_STATS
   (void) printf ("\n(Locates: demanded %ld (+%ld), faults %ld (+%ld))\n",
      locate_demands, locate_demands - old_demands, 
      locate_faults, locate_faults - old_faults);
   (void) printf ("(Locate ratio %ld%%)\n", 
      (((1000 * locate_faults) / locate_demands) + 5) / 10);
#endif /* LOC_STATS */
   quitting = 1;
   longjmp (loop_back, 1);
}

#ifdef __STDC__
short *bitword (int a1)
#else
short *bitword (a1)
int a1;
#endif
{
   short *adr;
   
   adr = NULL;
   if (a1 <= LOBJECT)
       adr = &objbits [OBJSIZE * (a1 - FOBJECT)];
   else if (a1 <= LPLACE)
      adr = &placebits [PLACESIZE * (a1 - FPLACE)];
   else if (a1 <= LVARIABLE)
      adr = &varbits [VARSIZE * (a1 - FVERB)];
   return (adr);
}

#ifdef __STDC__
void bitmod (char a1, int a2, int a3)
#else
void bitmod (a1, a2, a3)
char a1;
int a2;
int a3;
#endif
{
   short *bitadr;
   
   if (a2 > LVARIABLE || (a2 < FVARIABLE && a2 > LPLACE)) 
   {
      printf (
         "*** Run-time glitch! Setting flag on a flagless entity %d! ***\n", a2);
      return;
   }
   if (a2 <= LOBJECT && a3 >= OBJSIZE * 16)
      printf (
         "*** GLITCH: object %d flag %d out of range!\n", a2, a3);
   if (a2 >= FPLACE && a2 <= LPLACE && a3 >= PLACESIZE * 16)
      printf (
         "*** GLITCH: place %d flag %d out of range!\n", a2, a3);
   if (a2 >= FVARIABLE && a2 <= LVARIABLE && a3 >= VARSIZE * 16)
      printf (
         "*** GLITCH: variable %d flag %d out of range!\n", a2, a3);
   bitadr = bitword (a2);
   while (a3 > 15)
   {
      bitadr++;
      a3 -= 16;
   }
   if (a1 == 's')
      *bitadr |= 1 << a3;
   else
      *bitadr &= ~(1 << a3);
   return;
}
      
#ifdef __STDC__
void lbitmod (int a0, char a1, int a2, int a3, int *a4, short *a5)
#else
void lbitmod (a0, a1, a2, a3, a4, a5)
int a0;
char a1;
int a2;
int a3;
int *a4;
short *a5
#endif
{
/* a0 locals
 * a1 type ('c', 's')
 * a2 entity
 * a3 flag
 * a4 *lval
 * a5 *lbts
 */
   short *bitadr;

   if (a2 < 0 || a2 >= a0)
      printf (
         "*** Run-time glitch! Local entity %d >= locals %d! ***\n", a2, a0);

   if (a2 <= LOBJECT && a3 >= OBJSIZE * 16)
      printf (
         "*** GLITCH: local object %d flag %d out of range!\n", a2, a3);
   if (a2 >= FPLACE && a2 <= LPLACE && a3 >= PLACESIZE * 16)
      printf (
         "*** GLITCH: local %d place flag %d out of range!\n", a2, a3);
   if (a2 >= FVARIABLE && a2 <= LVARIABLE && a3 >= VARSIZE * 16)
      printf (
         "*** GLITCH: local %d variable %d flag %d out of range!\n", a2, a3);

   if (*(a5 + VARSIZE * a2) == -1)
      bitadr = bitword (*(a4 + a2));
   else
      bitadr = a5 + VARSIZE * a2;

   while (a3 > 15)
   {
      bitadr++;
      a3 -= 16;
   }
   if (a1 == 's')
      *bitadr |= 1 << a3;
   else
      *bitadr &= ~(1 << a3);
   return;
}
      
#ifdef __STDC__
int bitest (int a1, int a2)
#else
int bitest (a1, a2)
int a1;
int a2;
#endif
{
   short *bitadr;
   
   if (a1 > LVARIABLE)
      return (0);
   if (a1 < FVARIABLE && a1 > LPLACE)
      return (a2 == VERB);
   bitadr = bitword (a1);
   if (bitadr == NULL)
      return (0);
   while (a2 > 15)
   {
      bitadr++;
      a2 -= 16;
   }
   return (*bitadr & 1 << a2);
}

#ifdef __STDC__
int lbitest (int a1, int a2, int *a3, short *a4)
#else
int lbitest (a1, a2, a3, a4)
int a1;
int a2;
int *a3;
short *a4
#endif
{
   short *bitadr;
   if (*(a4 + VARSIZE * a1) == -1)
      bitadr = bitword (*(a3 + a1));
   else
      bitadr = a4 + VARSIZE * a1;
   if (bitadr == NULL)
      return (0);
   while (a2 > 15)
   {
      bitadr++;
      a2 -= 16;
   }
   return (*bitadr & 1 << a2);
}

#ifdef __STDC__
void flush_command (void)
#else
void flush_command ()
#endif
{
   value_all = 0;
   tp [tindex] = NULL;
   return;
}

#ifdef __STDC__
void shift_up (char *aptr)
#else
void shift_up (aptr)
char *aptr;
#endif
{
   if ((*aptr >= 'a' && *aptr < 'z') || (*aptr >= 'A' && *aptr < 'Z'))
      (*aptr)++;
   else if (*aptr == 'z' || *aptr == 'Z')
      *aptr -= 25;
}
#ifdef __STDC__
void shift_down (char *aptr, int maxlen)
#else
void shift_down (aptr, maxlen)
char *aptr;
int maxlen;
#endif
{
   char *sptr = aptr;
   while (maxlen-- && *aptr)
   {
      if ((*aptr > 'a' && *aptr <= 'z') || (*aptr > 'A' && *aptr <= 'Z'))
         (*aptr)--;
      else if (*aptr == 'a' || *aptr == 'A')
         *aptr += 25;
      aptr++;
   }
   if (log_file) fprintf (log_file, "TRANSLATION: %s\n", sptr);
}

#ifdef __STDC__
void tie (int text, int holder)
#else
void tie (text, holder)
int text;
int holder;
#endif
{
   text_info [2 * (text - FTEXT)] = TIED_TEXT;
   value [text] = holder;
}

#ifdef __STDC__
void svar (int type, int *var)
#else
void svar (type, var)
int type;
int *var;
#endif
{
   time_t now;
   struct tm *tp;
   switch (type)
   {
      case 4:
      case 5:
         now = time (NULL);
         tp = localtime (&now);         
         *var = (type == 4 ? tp -> tm_hour : tp -> tm_min);
         break;
        
      default:
         (void)  PRINTF2 ("GLITCH! Bad svar code: %d\n", type);
   }
   return;
}

