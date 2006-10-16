/* adv00.c: A-code kernel - copyleft Mike Arnautov 1990-2006.
 */
#define KERNEL_VERSION "11.88, MLA - 16 Oct 2006"
/*
 * 15 Oct 06   MLA        Reinstated HTML tag handling. 
 *                        Also added PROMPTED symbol processing.
 * 30 Jul 05   MLA        Cleaned up compiler warnings.
 * 25 May 05   MLA        BUG: Don't gripe for flags in excess of 15!
 * 17 Apr 05   MLA        BUG: Dump readline buffer on new line.
 * 09 Apr 05   MLA        BUG: allow for voc growth in restoring varbits.
 * 26 Mar 05   MLA        BUG: Fixed UNDO/REDO for the CGI mode.
 * 13 Mar 05   MLA        BUG: Restore computed image length, not real one!
 * 12 Mar 05   MLA        Bug: time_t is long, not int!
 * 20 Feb 05   MLA        Bug: Don't strip off dots if no matching!
 * 18 Jan 05   MLA        Allowed for nested vars and others.
 * 09 Jan 05   MLA        Command line and symbol handling of UNDO status.
 * 03 Jan 05   MLA        Added undo history keeping.
 * 31 Dec 04   MLA        Bug: cgi only defined if CONTEXT is defined!
 * 28 Dec 04   MLA        Assembled state arrays into one array.
 * 22 Dec 04   MLA        bug: PRINTF2 has to be braced -- it's compound!
 * 05 Dec 04   MLA        Bug: Verbatim glitch.
 * 19 Aug 04   MLA        Replaced special(31) with verbatim().
 * 08 Aug 04   MLA        bug: Force logfile in CGI mode.
 * 07 Aug 04   MLA        Bug: Remember game name on initial restore in
 *                        the cgi mode.
 * 31 Jul 04   MLA        bug: Don't abort compound commands after "except".
 * 09 Apr 04   MLA        bug: Don't print kernel version twice if GLK.
 * 14 Mar 04   MLA        BUG: Or for (internal) "-z" ones. And don't leave
 *                        debug statements lying around!!!
 * 28 Feb 04   MLA        BUG: Don't use memstore for CGI -y restores!
 * 16 Feb 04   MLA        G++ didn't like initialisation of fname in memstore().
 *                        Bug: Initialise rseed before calling p1()!
 * 12 Feb 04   MLA        Reused exec 12.
 * 06 Feb 04   MLA        Flag pseudo-objects on entry.
 * 07 Jan 04   MLA        Split memstore() off special(). Reused exec 28.
 *                        Added exec 33.
 * 06 Jan 04   MLA        Exec 30 reused to strip off trailing LF.
 * 02 Jan 04   MLA        Exec 9/10 now also fake the arg word.
 * 30 Dec 03   MLA        Bug: Fixed termination of ALL loops.
 * 09 Dec 03   MLA        Bug: Fixed BLOCK_END handling in outbuf().
 * 16 Nov 03   MLA        Bug: check for bad syntax before skipping rest
 *                        of command!
 * 11 Oct 03   MLA        Allow for TYPO not being declared in style >= 11.
 * 23 Sep 03   MLA        BUG: don't zap tokens in find_word, if no matching!
 *                        bug: don't convert _ into blank on input.
 * 20 Sep 03   MLA        BUG: readline does not append '\n'!!
 * 18 Sep 03   MLA        Bug: don't call ferror() on a closed file handle!
 * 29 Jun 03   MLA        Eliminated redundant restore mode 966.
 * 27 Jun 03   MLA        BUG: Use separate memory for checking restore!
 * 22 Jun 03   MLA        BUG: Make sure command is lowercased!!!
 * 16 Jun 03   MLA        Bug: Fixed variant bit testing in voc().
 * 31 May 03   MLA        More tolerance for shorter (older) save-files.
 * 26 May 03   MLA        Parser re-write: THEN is now equivalent to semicolon.
 *                        Also, let the game do pre-saying.
 * 10 May 03   MLA        BUG: Fixed "drop treasure and <something>".
 * 30 Apr 03   MLA        Bug: Strip off '\r' from MS line terminator.
 * 08 Apr 03   MLA        bug: Initialise to zero values beyond end of
 *                        values array in a restored game.
 * 01 Apr 03   MLA        BUG: fixed restore of incompatible versions.
 *                        Also, improved version checking.
 *                        Also changed -l to -log iff GLK.
 * 24 Mar 03   MLA        BUG: no SCHIZOID behaviour for INHAND in isat().
 * 22 Mar 03   MLA        BUG: run p1() when restoring from command line!
 * 20 Mar 03   MLA        Intelligent version checks on restore,
 * 09 Mar 03   S. Munro   bug: Remove some redundant declarations.
 *                        Work around an MS oddity in using CHKSUM.
 *             MLA        Default to SWAP.
 * 08 Mar 03   S. Munro   Bug: Fix several non-ANSI declaration.
 * 04 Mar 03   MLA        Trap bad command-line restores.
 *                        Re-do the handling of VERSION as GAMEID and DBNAME.
 * 24 Feb 03   MLA        Bug: Fixed create_db sign handling.
 *                        bug: Suppressed unnecessary "More?" prompts.
 * 23 Feb 03   MLA        Bug: Fixed CGI version handling.
 * 21 Feb 03   MLA        Rationalised use of database use or non-use.
 * 20 Feb 03   MLA        Merged database into executable.
 * 16 Feb 03   MLA        bug: several small command handling bugs.
 * 14 Feb 03   MLA        Bug: Fixed '-l -c name' handling in command args.
 * 09 Feb 03   MLA        Use F/LFULL and F/LDIR. Also use SAY.
 * 04 Feb 03   MLA        Bug: fix qualifying by ARG2. 
 *                        Also hacked in EXCEPT code.
 * 31 Jan 03   MLA        Virgin mode entirely file based -- no rapes! :-)
 * 26 Jan 03   MLA        bug: avoid looping in INITs even if code QUITs there.
 * 24 Jan 03   MLA        BUG: BADWORD etc do *not* suppress amatch!
 * 06 Jan 03   MLA        BUG: Fixed varbits[] handling!
 * 04 Jan 03   MLA        Bug: fixed the typo reporting code.
 *                        Also added case 31 of special().
 * 02 Jan 03   MLA        bug: removed redundant fprintf arg.
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
 * 12 May 01   MLA        Bug: conditionally switch off amatching for ARG2.
 * 06 May 01   MLA        bug: Fixed approximate matching.
 * 02 May 01   MLA        Bug: Fixed yet another "null command" bug. :-(
 * 16 Apr 01   MLA        Fixed zapping save file on initial restore.
 * 30 Mar 01   MLA        Added typo reporting
 * 25 Mar 01   MLA        Added scenery word matching.
 * 15 Mar 01   MLA        Added readline.
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

#include "adv1.h"

#ifdef USEDB
#  undef USEDB
#endif /* USEDB */

#ifdef PRELOADED
#  undef PRELOADED
#endif /* PRELOADED */

#ifdef MEMORY
#  ifdef DBSTATUS
#     undef DBSTATUS
#  endif
#endif /* MEMORY */

#ifdef FILE
#  undef FILE
#  define READFILE
#  ifdef SWAP
#     undef SWAP
#  endif
#  ifdef MEMORY
#     undef MEMORY
#  endif
#  ifdef DBSTATUS
#     undef DBSTATUS
#  endif
#endif /* FILE */

#ifdef SWAP
#  ifdef MEMORY
#     undef MEMORY
#  endif
#  ifdef DBSTATUS
#     undef DBSTATUS
#  endif
#endif /* SWAP */

#ifdef DBSTATUS
#  if DBSTATUS == 0
#     define PRELOADED
#  endif
#  if DBSTATUS == 1
#     define MEMORY
#  endif
#  if DBSTATUS == 2
#     define SWAP 32
#  endif
#  if DBSTATUS == 3
#     define READFILE
#  endif
#endif /* DBSTATUS */

#ifdef SWAP
#  if SWAP < 16
#     undef SWAP
#     define SWAP 16
#  endif /* SWAP < 16 */
#  if SWAP > 128
#     undef SWAP
#     define SWAP 128
#  endif /* SWAP > 128 */
#endif /* SWAP */

#ifndef PRELOADED
#  define USEDB
#endif

#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifdef NEED_UNISTD
#include <unistd.h>
#else
int unlink(char *);
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
#include <readline/readline.h>
#include <readline/history.h>
char *lbp;
char *lbuf;
#endif

FILE *text_file;
FILE *gv_file;
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

#include "adv0.h"
#ifndef USEDB
#  include "adv6.h"
#endif /* ! USEDB */

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
#  if STYLE >= 11
#     define VHOLDER      '\361'
#  endif
#endif /* STYLE */

#ifdef GLK
#  define putchar(X) glk_put_char(X)
#else
#  ifdef READLINE
#     define putchar(X) *lbp++=X;if (*(lbp-1)=='\n')\
              {*lbp='\0';printf(lbuf);lbp=lbuf;}

#  endif
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
                     putchar(*X++);} else X++
#else
#define PUTCHARA(X)  if (*X != IGNORE_EOL) { \
                     if (log_file) (void)fputc(*X,log_file); \
                     putchar(*X++);} else X++
#endif /* BLOCK_END */

void outbuf (int);
int value_all;
jmp_buf loop_back;
char data_file [128];
#ifdef USEDB
   char *dbs_dir = NULL;
#endif /* USEDB */
char exec [128];
char virgin;
#define VAL_SIZE (LTEXT * sizeof (int))
#define OFFSET_LOCS VAL_SIZE
#define LOCS_SIZE ((LOBJECT + 1) * sizeof (int))
#define OFFSET_OBJBIT (OFFSET_LOCS + LOCS_SIZE)
#define OBJBIT_SIZE (OBJSIZE * (LOBJECT - FOBJECT + 1) * sizeof (short))
#define OFFSET_PLACEBIT (OFFSET_OBJBIT + OBJBIT_SIZE)
#define PLACEBIT_SIZE (PLACESIZE * (LPLACE - FPLACE + 1) * sizeof (short))
#define OFFSET_VARBIT (OFFSET_PLACEBIT + PLACEBIT_SIZE)
#define VARBIT_SIZE (VARSIZE * (LVARIABLE - FVERB + 1) * sizeof (short))
#define VRBBIT_SIZE (VARSIZE * (LVERB - FVERB + 1) * sizeof (short))
#define IMAGE_SIZE (OFFSET_VARBIT + VARBIT_SIZE)
char IMAGE [IMAGE_SIZE];
int *value = (int *)IMAGE;
int *location = (int *)(IMAGE + OFFSET_LOCS);
short *objbits = (short *)(IMAGE + OFFSET_OBJBIT);
short *placebits = (short *)(IMAGE + OFFSET_PLACEBIT);
short *varbits = (short *)(IMAGE + OFFSET_VARBIT);
#ifdef UNDO
   char image [sizeof (IMAGE)];
   int inhand [LOCS_SIZE];
   unsigned char *diffs = NULL;
   unsigned char *dptr = NULL;
   unsigned char *edptr;
   int diffsz = 0;
#ifdef NO_UNDO
   int undo_def = -2;
#else
   int undo_def = 0;
#endif /* NO_UNDO */
#endif
char comline [161] = "\n";
char old_comline [161] = "\n";
char raw_comline [161];
char long_word [161];
int arg1, arg2;
int orphan;
int qvals [5];
int *qtext = &qvals[0];
int *qstat = &qvals [1];
int *qarg1 = &qvals [2];
int *qarg2 = &qvals [3];
int *qcon = &qvals [4];
char say_buf[160];
#define WORDSIZE 20
char qwords [5 * WORDSIZE];
char *arg1_word = qwords;
char *arg2_word = qwords + WORDSIZE;
char arg3_word [WORDSIZE];
char *orphan_word = qwords + 2 * WORDSIZE;
char *qargw1 = qwords + 3 * WORDSIZE;
char *qargw2 = qwords + 4 * WORDSIZE;
char temp_word [WORDSIZE];
#if STYLE >= 11
#  define ORIG -1
   char orig [WORDSIZE];
#  if defined(ALL) && defined(EXCEPT)
      int except_count;
      int except [100];
#  endif /* ALL and EXCEPT */
#endif /* STYLE == 11 */
int rseed;
int mainseed = 0;
int amatch = 1;
#ifdef DWARVEN
   int extra_dwarvish = 0;
#endif
#if defined(JUSTIFY) || STYLE == 10
   int justify = 1;
#else
   int justify = 0;
#endif
#if defined(TIGHT_PROMPT) || STYLE == 1
   int compress = 1;
#else
   int compress = 0;
#endif
#if defined(PAUSE) || defined(MSDOS) || defined(_WIN32) || defined (GLK)
   int end_pause = 1;
#else
   int end_pause = 0;
#endif
#ifdef CONTEXT
   int cgi = 0;
   char cgicom [160];
   char *cgi_name = ".C.adv";
#endif

#include "adv3.h"
#include "adv4.h"
#include "adv2.h"
#include "adv5.h"

#ifdef AGAIN
   int fresh_line = 1;
#endif /* AGAIN */

#ifdef MEMORY
   char text [TEXT_BYTES];
#endif /* MEMORY */

#ifdef SWAP
#  define TEXT_CHUNK 1024
   char text [SWAP * TEXT_CHUNK];
   int chunk_start [SWAP];
   int chunk_end [SWAP];
   int chunk_age [SWAP];
#endif /* SWAP */

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
int ta;
int locate_faults;
int locate_demands;
#ifdef LOC_STATS
   int old_faults;
   int old_demands;
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
char title [80];
int titlen;
int quitting;
int eol_count = 0;
#ifdef TAG_START
   int html_tag = 0;
#endif /* TAG_START */
char *lp;

#define PRINTF(X)    { char *ptr = X; while (*ptr) outchar(*ptr++); }
#define PRINTF1(X)   printf(X); if (log_file) (void)fprintf(log_file,X);
#define PRINTF2(X,Y) printf(X,Y); if (log_file) (void)fprintf(log_file,X,Y);
#define CHKSUM(X,Y)  for (cptr=(char *)X,cnt=1; \
                     (unsigned int)cnt<=(unsigned int)Y;cnt++,cptr++) \
                     {chksum+=(*cptr+cnt)*(((int)(*cptr)+cnt)<<4)+Y; \
                     chksum&=07777777777L;} 

/******************************************************************/

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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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
   int dir;
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

/*===========================================================*/

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

/* PRIVATE */
#if defined(PLAIN) && (defined(MEMORY) || defined(PRELOADED))
#  define get_char(X) text[X]
#else /* !PLAIN || (!MEMORY && !PRELOADED)*/

/*===========================================================*/

#ifdef __STDC__
char get_char (int char_addr)
#else
char get_char (char_addr)
int char_addr;
#endif
{
#ifndef PLAIN
   int mask;
#endif /* not PLAIN */
#if defined(MEMORY) || defined (PRELOADED)
   mask = (char_addr >> 4) & 127;
   if (mask == 0)
      mask = char_addr & 127;
   if (mask == 0)
      mask = 'X';
   mask = (17 * mask + 13) & 127;
   return (mask ^ text [char_addr] ^ title [char_addr % titlen]);
#endif /* MEMORY || PRELOADED */
#ifdef SWAP
   int index;
   char *buf_ptr;
   int oldest_chunk;
   int new_addr;
   void file_oops ();
   
   oldest_chunk = 0;
   buf_ptr = text;
   for (index = 0; index < SWAP; index++)
   {
      if (char_addr >= chunk_start [index] && char_addr < chunk_end [index])
         goto gotit;
      buf_ptr += TEXT_CHUNK;
   }

   for (index = 0; index < SWAP; index++)
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
   mask = (17 * mask + 13) & 127;
   return 
      (*(buf_ptr + char_addr - chunk_start [index]) ^ mask ^ 
         title [char_addr % titlen]);
#endif /* PLAIN */
#endif /* SWAP */
#ifdef READFILE
   void file_oops ();
   static int file_addr = -1;
   char this_char;   

   if (file_addr != char_addr)
   {
      locate_faults++;
      if (fseek (text_file, char_addr, 0))
         file_oops ();
      file_addr = char_addr;
   }
   this_char = fgetc (text_file);
   file_addr++;
#ifdef PLAIN
   return (this_char);
#else /* not PLAIN */
   mask = (char_addr >> 4) & 127;
   if (mask == 0)
      mask = char_addr & 127;
   if (mask == 0)
      mask = 'X';
   mask = (17 * mask + 13) & 127;
   return (this_char ^ mask ^ title [char_addr % titlen]);
#endif /* PLAIN */
#endif /* READFILE */
}

#if defined(SWAP) || defined(READFILE)

/*===========================================================*/

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
}
#endif /* SWAP || READFILE */
#endif /* PLAIN && MEMORY */
/* ENDPRIVATE */

/*===========================================================*/

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
   if (test >0 && bitest (what, test) == 0)
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

/*===========================================================*/

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
      PRINTF1 ("[More?] ");
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

/*===========================================================*/

#ifdef __STDC__
void outstr(char *str)
#else
void outstr(str)
char *str;
#endif
{
   while (*str)
      putchar(*str++);
   return;
}
   

/*===========================================================*/

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
   hlead = 2;   /* Was 5! */
#endif
   while (*tptr && *tptr != BLOCK_END)
   {
      scrchk (0);
#ifdef GLK
      tptr += lead;
#endif
      if (cgi)
         tptr += lead;
      else if (hlead < 0)
         tptr -= hlead;
      else if (hlead > 0 && ! cgi)
      {
         for (len = 0; len < hlead; len++)
         {
            PUTCHAR (' ');
         }
      }
      while (*tptr && *tptr != '\n' && *tptr != BLOCK_END)
      {
         if (cgi && type == BLOCK_START && *tptr == ' ')
         {
            if (log_file) (void)fputc(*tptr++, log_file);
            outstr("&nbsp;");
            if (*tptr == ' ')
               outstr("&nbsp;&nbsp;");
         }
         else
         {
            PUTCHARA (tptr);
         }
      }
      if (*tptr == '\n')
      {
#ifdef CONTEXT
         if (cgi && *tptr != BLOCK_END) 
               printf ("<br />");
#endif
         PUTCHARA (tptr);
      }
   }
#ifdef CONTEXT
   if (cgi)
   {
      if (type == BLOCK_START)
         printf ("</td></tr></table>");
      printf ("</center>");
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

/*===========================================================*/

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
   int frag;
#ifdef BLOCK_START
   int line_break = 1;
#endif

   eol_count = 0;
   frag = 1;
 
   lptr--;  
   while (*lptr == ' ' || *lptr == '\n')
   {
      if (*lptr == '\n')
         frag = 0;
      lptr--;
      text_len--;
   }
#ifdef BLOCK_END
   if (*lptr == BLOCK_END && *(lptr - 1) == '\n')
      frag = -1;
#endif /* BLOCK_END */
   lptr++;
   
   if (frag <= 0)
   {
      if (! terminate)
      {      
#if STYLE > 1
         if (!compress && frag == 0)
         {
            PRINTF ("\n ");
         }
#endif /* STYLE */
            PRINTF ("\n? ")
      }
   }
   else
   {
      *lptr++ = ' ';
      text_len++;
   }
   *lptr = '\0';

   if (*tptr == '\n')
   {
      while (*tptr == '\n')
         tptr++;
      if (!compress)
         tptr--;
   }
      
   lptr = tptr;
   break_point = 0;
   break_count = -1;

#if STYLE >= 11
   if (value [ARG1] < BADWORD && value [ARG2] < BADWORD)
      word_update ();
#endif /* STYLE */

   while ((text_char = *tptr++))
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
           line_break = 0;
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
            line_len = 0;
            tptr = lptr;
         }
         else if (!wrapped)
         {
            PUTCHAR ('\n');
            lptr = tptr;
         }
         break_point = 0;
         break_count = -1;
         lastchar = ' ';
         line_len = 0;
         wrapped = 0;
#ifdef BLOCK_START
         if (cgi && line_break)
            printf ("<br />");
         line_break = 1;
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
            PUTCHAR ('\n');
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
            PUTCHAR ('\n');
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

#define VOC_FLAG     128
#define QUIP_FLAG     64
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

#ifdef NEST_TEXT

/*===========================================================*/

#ifdef __STDC__
void nested_say (int addr, int key, int qualifier)
#else
void nested_say (addr, key, qualifier)
int addr;
int key;
int qualifier;
#endif
{
   int refno;
   int type;
   
   if (key &= 14)
      key = 8;
   type = get_char (addr++);
   refno = get_char (addr++) << 8;
   refno |= (get_char (addr) & 255);
   if (type == 0)
   {
      refno += FOBJECT;
      key = VOC_FLAG;
   }
   else if (type == 1)
   {
      refno += FPLACE;
      key = VOC_FLAG;
   }
   else if (type == 2)
      refno += FVERB;
   else if (type == 3)
   {
      refno += FVARIABLE;
      key = VAR_FLAG | VOC_FLAG;
      qualifier = 0;
   }
   else
      refno += FTEXT;
   if (type < 2)
      qualifier = 0;
   say (key, refno, qualifier);
   ta = addr;
}
#endif /* NEST_TEXT */

/*===========================================================*/

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
   int voc_flag;
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
   int auxa;
   int ea;
   char *cp;
   char tc;
   char tl = 0;

/* NB: The below flag values are hard-coded in acdc's dominor.c! */

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
   voc_flag =      key & VOC_FLAG;
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
      ((qualifier != ARG1 && qualifier != ARG2 && qualifier != ARG3) || 
         value_flag))
            qualifier = value [qualifier];

   if (what > LPLACE || voc_flag)
   {
      if (voc_flag && (what == ARG1 || what == ARG2))
      {
         if (what == ARG1)
            cp = arg1_word;
         else if (what == ARG2)
            cp = arg2_word;
         else
            cp = arg3_word;
         while (*cp != '\0')
            outchar (*cp++);
         return;
      }
      ta = textadr [what];
   }
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
            textqual = 0;
         else
            textqual = irand (textqual);
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
         textqual = value [what];
      else if (text_info [twat] == TIED_TEXT)
         textqual = value [value [what]];
      else if (qualifier == ARG2 && value [ARG2] < BADWORD)
         textqual = value [value [qualifier]];
   }

   if (!qual_flag)
      qualifier = (what <= LPLACE) ? value [what] : what;
   
   while (tc != '\0')
   {
      tl = tc;
#ifdef NEST_TEXT
      if (tc == NEST_TEXT)
      {
         nested_say (ta + 1, given_key, qualifier);
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
#if STYLE >= 11
      else if (tc == HOLDER || tc == VHOLDER)
      {
         if (upcase) upcase = 2;
         if (value_flag || tc == VHOLDER)
#else
      else if (tc == HOLDER)
      {
         if (value_flag)
#endif
         {
            (void) sprintf (auxbuf, "%d", qualifier);
            cp = auxbuf - 1;
            while (*(++cp) != '\0')
               outchar (*cp);
            goto next_char;
         }
#if STYLE >= 11
         else if (qualifier == ARG1 || qualifier == ARG2 || qualifier == ARG3)
         {
            if (qualifier == ARG1)
               cp = arg1_word;
            else if (qualifier == ARG2)
               cp = arg2_word;
            else
               cp = arg3_word;
            while (*cp != '\0')
               outchar (*cp++);
            goto next_char;
         }
         else if (qualifier == ORIG)
         {
            cp = orig;
            while (*cp != '\0')
               outchar (*cp++);
            goto next_char;
         }
#else /* STYLE < 11 */
         else if (qualifier == ARG1 || qualifier == ARG2)
         {
            cp = (qualifier == ARG1 ? arg1_word : arg2_word);
            while (*cp != '\0')
               outchar (*cp++);
            goto next_char;
         }
#endif /* STYLE */
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

/*===========================================================*/

#ifdef __STDC__
void outchar (int text_char)
#else
void outchar (text_char)
int text_char;
#endif
{
   if (text_len == text_buf_len - 8)
   {
      text_buf_len += 1024;
      if ((text_buf = (char *) realloc (text_buf, text_buf_len)) == NULL)
      {
         puts ("*** Unable to extend text buffer! ***");
         exit (0);
      }
      lptr = text_buf + text_len;
   }

#ifdef TAG_START
   if (text_char == TAG_START)
   {
      html_tag = 1;
      if (cgi)
         *lptr++ = '<';
      return;
   }
   else if (html_tag)
   {
      if (text_char == TAG_END)
      {
         html_tag = 0;
         if (cgi)
            *lptr++ = '>';
         return;
      }
   }
   if (html_tag && cgi == 0)
      return;
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
   {
      if (cgi)
      {
         strcpy(lptr, "&nbsp;");
         lptr += 6;
         return;
      }
      else
         text_char = ' ';
   }
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

#ifdef UNDO

/*===========================================================*/

#ifdef __STDC__
void save_changes (void)
#else
void save_changes ();
#endif
{
   char *iptr;
   char *optr;
   unsigned int cnt;
   int some = 0;

   if (value [ARG1] >= BADWORD || value [ARG2] >= BADWORD ||
#ifdef CONTEXT
       value [CONTEXT] > 1 ||  cgi == 'y' ||
#endif
       value [ARG1] == UNDO || value [ARG1] == REDO)
          return;
   if (dptr > edptr)
      dptr = edptr;
   if (diffs == NULL)
   {
      if ((diffs = (unsigned char *)malloc(8192)) == NULL)
      {
         printf ("GLITCH: Unable to allocate diffs array!\n");
         return;
      }
      else
      {
         diffsz = 8192;
         memset (diffs, '\0', 4);
         edptr = dptr = diffs + 4;
      }
   }
   else
   {
      for (cnt = 0, optr = image, iptr = IMAGE; cnt < sizeof (IMAGE); 
         cnt++, optr++, iptr++)
      {
         if (*optr != *iptr && 
          ! ((cnt >= ARG1*sizeof(int) && cnt < (ARG1 + 1)*sizeof(int)) ||
             (cnt >= ARG2*sizeof(int) && cnt < (ARG2 + 1)*sizeof(int)) ||
             (cnt >= STATUS*sizeof(int) && cnt < (STATUS + 1)*sizeof(int))))
         {
            if (dptr - diffs + 8 >= diffsz)
            {
               int doffset = dptr - diffs;
               if ((diffs = (unsigned char *)realloc(diffs, diffsz + 8192)) == NULL)
               {
                  printf ("GLITCH: Unable to re-allocate diffs array!\n");
                  return;
               }
               diffsz += 8192;
               dptr = diffs + doffset;
            }
            if (cnt || cgi == 0)
            {
               *dptr++ = cnt / 256;
               *dptr++ = cnt % 256;
               *dptr++ = *optr;
               *dptr++ = *iptr;
               some = 1;
            }
         }
      }
      if (some)
      {
         for (cnt = 0; cnt < 4; cnt++)
            *dptr++ = '\0';
         edptr = dptr;
      }
   }
   memcpy (image, IMAGE, sizeof (IMAGE));
}
#endif /* UNDO */

/*===========================================================*/

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
   scrchk (1);
#if STYLE >= 11
   upcase = 1;
#endif /* STYLE >= 11 */

#ifdef UNDO
   if (value [UNDO_STAT] >= 0)
      save_changes ();
   else if (diffs && dptr > diffs)
      edptr = dptr = diffs;
#endif /* UNDO */

#ifdef CONTEXT
#  ifdef PROMPTED
   bitmod ('s', CONTEXT, PROMPTED);
#  endif
   if (cgi == 'x' || cgi == 'z')
   {
      special (998, &value [0]);
      if (word_buf) free (word_buf);
      exit (value [CONTEXT]);
   }
   if (cgi == 'y')
   {
      strncpy (inbuf, cgicom, insize - 1);
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
            rdl = readline (lbuf);
            memcpy (inbuf, rdl, insize);
            add_history (rdl);
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
            cptr = inbuf + strlen (inbuf) - 2;
            if (*inbuf != '\n' && *cptr == '\r')
            {
               *cptr++ = '\n';
               *cptr = '\0';
            }
            break;
         }
      }
   }
   else if (com_file == NULL)
#ifdef READLINE
   {
      rdl = readline (lbuf);
      memcpy (inbuf, rdl, insize);
      add_history (rdl);
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
      if (strchr ("\"\'", *cptr))
         *cptr = ' ';
      cptr++;
   }
   if (log_file)
      fprintf (log_file,"\nREPLY: %s\n", inbuf);
}

/*===========================================================*/

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

   if (text_len - (lptr - text_buf) >= Maxlen && scrchk (0) != 0)
      return lptr;
   if ((need = Margin))
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
               PUTCHAR (' ');
            }
            if (--break_point ==0)
               base = base + adjust;
         }
         lastchar = *aptr;

         PUTCHARA (aptr);
      }
   }
#ifdef READLINE
   *lbp = '\0';
   if (*aptr)
      printf (lbuf);
   lbp = lbuf;      
#endif
   fflush (stdout);
   return (aptr);
}

/*===========================================================*/

#ifdef __STDC__
void advcpy (char *word_buff, int word_addr)
#else
void advcpy (word_buff, word_addr)
char *word_buff;
int word_addr;
#endif
{
   int wlen;

   if (get_char (word_addr) == '!')
      word_addr++;
   for (wlen = 1; wlen <= 20; wlen++)
      if ((*word_buff++ = get_char (word_addr++)) == '\0')
         return;
}

/*===========================================================*/

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
   strcpy (which_arg == 1 ? arg1_word : arg2_word, "*GLITCH*");
   return;
}

/*===========================================================*/

#ifdef __STDC__
void default_to (int key, int place, int type)
#else
void default_to (key, place, type)
int key;   /* 0 is "default", 1 is initial "doall", 2 is continued "doall" */
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
   {
#if STYLE >= 11
      if (except_count > 0)
      {
         int i, j;
         j = 0;
         for (i = 0; i < except_count; i++)
            if (index == except [i])
            { 
               except [i] = except [except_count - 1];
               except_count--;
               j = 1;
               break;
            }
         if (j)
            continue;
      }
#endif /* STYLE == 11 */
#else /* not ALL */
   for (index = FOBJECT; index <= LOBJECT; index++)
   {
#endif /* ALL */
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
#ifdef TYPO

/*===========================================================*/

#ifdef __STDC__
void report_typo (int ovoc, int olen)
#else
void report_typo (ovoc, olen)
int ovoc;
int olen;
#endif
{
   char save_char;

   (void) strncpy (orig, tp [tindex], WORDSIZE);
#ifdef DWARVEN
   if (value [DWARVEN]) shift_down (orig, WORDSIZE);
#endif
   say (QUAL_FLAG, TYPO, ORIG);
   advcpy (orig, ovoc);
   save_char = *(orig + olen);
   *(orig + olen) = '\0';
   say (QUAL_FLAG, TYPO, ORIG);
   *(orig + olen) = save_char;
   if ((unsigned int)olen >= strlen (orig)) 
      value [TYPO]++;
   else
      say (QUAL_FLAG, TYPO, ORIG);
   say (0, TYPO, 0);
   *orig = '\0';
   PRINTF("\n\n");
}
#endif

/*===========================================================*/

#ifdef __STDC__
void find_word (int *type, int *refno, int *tadr, int which_arg, int gripe)
#else
void find_word (type, refno, tadr, which_arg, gripe)
int *type;
int *refno;
int *tadr;
int which_arg;
int gripe;
#endif
#else
/*===========================================================*/

#ifdef __STDC__
void find_word (int *type, int *refno, int *tadr, int which_arg)
#else
void find_word (type, refno, tadr, which_arg)
int *type;
int *refno;
int *tadr;
int which_arg;
#endif
#endif
{
   int bottom, middle, top;
   int old_refno;
#if STYLE > 1
   int old_type;
   int old_tadr;
#endif /* STYLE */
#if STYLE >= 11
   int ovoc;
   int olen;
#endif
   int exact;
   int va;
   char *wp;
   int ra;
   char myword [WORDSIZE];
  
   strcpy (myword, tp [tindex]);
#ifdef DWARVEN
   if (value [DWARVEN]) shift_down (myword, WORDSIZE);
#endif /* DWARVEN */
   if (*myword == '\0')
   {
      *type = NOISE;
      goto done;
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
            goto done;
         }
#else /* STYLE > 1 */
            goto done;
         if (old_refno != BADWORD && *refno != old_refno)
#if STYLE >= 11
         {
#define REF(X) (which_arg == 1 ? X > LOBJECT : (X <= LOBJECT && \
                   (location [X] == INHAND || location [X] == value [HERE])))
            int oref = REF (old_refno);
            int nref = REF (*refno);
            
            if ((nref && oref) || (!nref && !oref))
               { *refno = AMBIGWORD; goto done; }
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

   if (*refno == BADWORD && amatch > 0)
   {
      char *bp = NULL;
      int ba = 0;
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
            ovoc = voc_addr [bottom];
            olen = va - ovoc;
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
               ovoc = voc_addr [bottom];
               olen = va - ovoc;
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
               ovoc = voc_addr [bottom];
               olen = va - ovoc;
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
               ovoc = voc_addr [bottom];
               olen = va - ovoc;
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
               ovoc = voc_addr [bottom];
               olen = va - ovoc;
               continue;
            }
         }
      }
      if (old_refno == AMBIGTYPO)
         *refno = AMBIGTYPO;
      else if (old_refno >= 0)
      {
#ifdef TYPO
         *type = voc_type [old_refno];
         *refno = voc_refno [old_refno];
         *tadr = voc_word [old_refno];
         if (gripe)
            report_typo (ovoc, olen);
#else
         *refno = BADWORD;
#endif
      }
   }
#endif /* STYLE >= 11 */
done:
#if STYLE >= 11
      if (which_arg > 1 && (*refno == BADWORD || *refno == AMBIGTYPO) && 
         btfind (word_buf, tp [tindex]))
            value [ARG2] = SCENEWORD;
#endif /* STYLE >= 11 */

   if (which_arg == 1)
      wp = arg1_word;
   else if (which_arg == 2)
      wp = arg2_word; 
   else
      wp = arg3_word;
   
   if (*refno >= BADWORD)
   {
      (void) strncpy (wp, tp [tindex], WORDSIZE);
      if (which_arg <= 2 && strlen (tp [tindex]) > 16)
         (void) strcpy (long_word, tp[tindex]);
   }
   else
   {
      (void) advcpy (wp, *tadr);
#ifdef DWARVEN
      if (value [DWARVEN] || extra_dwarvish)
      {
         char *cp = wp;
         while (*cp)
            shift_up (cp++);
      }
#endif /* DWARVEN */
   }
   if (*refno >= BADWORD && amatch != -1)
      tp [tindex + 1] = NULL; /* Discard rest of command */

#if defined(FDIR) && defined(LDIR) 
   else if ((*refno > FDIR && *refno < LDIR) && 
            separator [tindex + 1] == ' ')
      separator [tindex + 1] = ';';
#endif
   return;
}

/*===========================================================*/

#ifdef __STDC__
void parse (void)
#else
void parse ()
#endif
{
#ifndef OLDPARSER
   char *cptr, *lptr;
   char sep;
   
   for (cptr = comline; *cptr; cptr++)
      *cptr = tolower (*cptr);
   cptr = lptr = comline;
   while (*cptr == ' ' || *cptr == ',' || *cptr == ';' || 
         (*cptr == '.' && *(cptr + 1) != '.' && *(cptr + 1) != '/' &&
                          *(cptr + 1) != '\\'))
      cptr++;
   while (*cptr)
   {
      if (*cptr == '.' && (*(cptr + 1) == '.' || *(cptr + 1) == '/' ||
                           *(cptr + 1) == '\\'))
      {
         *lptr++ = *cptr++;
         continue;
      }
      
      while (*cptr && *cptr != ' ' && *cptr != ',' && *cptr != ';' && 
             *cptr != '.' && *cptr != '\n')
         *lptr++ = *cptr++;
      sep = ' ';
      while (*cptr == ' ' || *cptr == ',' || *cptr == ';' || 
            *cptr == '\n' || 
            (*cptr == '.' && *(cptr + 1) != '.' && *(cptr + 1) != '/' &&
                             *(cptr + 1) != '\\'))
      {
         if (*cptr == '.')
            *cptr = ';';
         if (sep == ' ' || *cptr == '\n')
            sep = *cptr;
         else if ((sep == ' ' || sep == ',') &&
                  (*cptr == ';' || *cptr == '\n'))
            sep = *cptr;
         cptr++;
      }
      if (*cptr)
         *lptr++ = sep;
   }
   if (sep != '\n')
      *lptr++ = '\n';
   *lptr++ = '\0';
   *lptr = '\0';
#ifdef NEWPARSER
 printf ("+++ Comline: %s", comline);
#endif
   tindex = 0;
   cptr = comline;
   while (*cptr)
   {
      if (*cptr == '\n')
         break;
      tp [tindex] = cptr;
      while (*cptr && *cptr != ' ' && *cptr != ',' && 
         *cptr != ';' && *cptr != '\n')
            cptr++;
      separator [tindex + 1] = *cptr;
      *cptr++ = '\0';
      if (strcmp (tp [tindex], AND) == 0)
         separator [tindex] = ',';
      else if (strcmp (tp [tindex], THEN) == 0)
         separator [tindex] = ';';
      else
         tindex++;
   }
   tp [tindex] = NULL;
   separator [tindex] = '\n';
#else
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
      if (tindex > 0)
      {
         if (strcmp (tp [tindex - 1], AND) == 0)
         {
            tindex--;
            if (sep == ' ') sep = ',';
         }
         else if (strcmp(tp [tindex - 1], THEN) == 0)
         {
            tindex--;
            if (sep == ' ' || sep == ',') sep = ';';
         }
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
         lp++;
      sep = 0;
      ew = lp;
      if (strcmp (tp [tindex], AND) == 0)
      {
         if (tindex >= 0 && separator [tindex - 1] == ' ')
            separator [tindex - 1] = ',';
      }
      else if (strcmp (tp [tindex], THEN) == 0)
      {
         if (tindex >= 0 && separator [tindex - 1] == ' ')
            separator [tindex - 1] = ';';
      }
      else
         tindex++;
   }
   tp [tindex] = NULL;
#endif
#if defined(OLDPARSER) || defined(NEWPARSER)
 {
  int n = 0;
  while (1)
  {
   printf ("+++ %d: %s (%c)\n", n, tp [n], separator [n]);
   if (tp [n] == NULL) break;
   n++;
  }
 }
#endif
   return;      
}


/*===========================================================*/

#ifdef __STDC__
void input (int textref)
#else
void input (textref)
int textref;
#endif
{
   int type;
   int refno;
   int tadr;
   int continuation;

   if (value[STATUS] == -1 && value [ARG3] == -1)
   {
      printf ("\nSorry... This game does not support command line restore.\n\n");
      exit (1);
   }
   if (value [STATUS] < 90 || value [STATUS] >= LTEXT)
      amatch = 1;
   else if (value [STATUS] == 99)
      amatch = 0;
   else
      amatch = -1;
      
#if STYLE >= 11
#ifdef ALL
   if (value_all == 0)
      except_count = 0;
#endif
   *orig = '\0';
#endif
   *bitword (ARG1) = -1;        /* Just in case! */
   *bitword (ARG2) = -1; 

#ifdef ALL
   if (value_all)
   {
      default_to (2, location_all, type_all);
      if (separator [tindex] == ',')
         arg1 = value [ARG1];
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
#  ifdef PROMPTED
   bitmod ('c', CONTEXT, PROMPTED);
#  endif

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
   *orig = '\0';
   find_word (&type, &refno, &tadr, separator [tindex] == ',' ? 2 : 1, 1);
#else
   find_word (&type, &refno, &tadr, separator [tindex] == ',' ? 2 : 1);
#endif
   tindex++;
   if (type == NOISE)
   {
      if (tp [tindex] == NULL) goto restart;
      if (separator [tindex] == ' ' || separator [tindex] == ',')
         goto get_arg1;
   }

#ifdef AGAIN
#if STYLE >= 11
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
#endif /* STYLE >= 11 */
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
      value [STATUS] = 2;
      goto got_command;
   }
#endif /* PLSCLARIFY */
   value [ARG1] = refno;
   value [STATUS] = 1;

get_arg2:
   if (separator [tindex] == ' ' && tp [tindex])
   {
#if defined(FSPECIAL) && defined(LSPECIAL)
      int bmatch = amatch;
      if (amatch == 1)
         amatch = (value [ARG1] < FSPECIAL || value [ARG1] > LSPECIAL);
#endif
#if defined(FACT) && defined (LACT)
      if (value [ARG1] > FACT && value [ARG1] < LACT)
      {
         separator [tindex] = ';';
         goto got_command;
      }
#endif
#if STYLE >= 11
#ifdef SAY
      if (value [ARG1] == SAY)
      {
         int i = tindex;
         strcpy (say_buf, tp [i]);
         while (tp [i] && (separator[i + 1] == ' ' || separator[i + 1] == ','))
         {
            strcat (say_buf, " ");
            strcat (say_buf, tp [i + 1]);
            if (separator [i + 1] == ' ')
               separator [i + 1] = ',';
            i++;
         }
      }
#endif /* SAY */
      *orig = '\0';
      find_word (&type, &refno, &tadr, 2, 1);
#else
      find_word (&type, &refno, &tadr, 2);
#endif
#if defined(FSPECIAL) && defined(LSPECIAL)
      amatch = bmatch;
#endif
      tindex++;
      if (type == NOISE)
         goto get_arg2;

      value [ARG2] = refno;
      value [STATUS] = 2;
   }

got_command:
#ifdef AGAIN
   fresh_line = 0;
#endif /* AGAIN */
   if (value [STATUS] == 1 && orphan)
   {
      if ((orphan > LOBJECT && value [ARG1] < LOBJECT) ||
          (orphan < LOBJECT && value [ARG1] > LOBJECT))
      {
         value [STATUS] = 2;
         value [ARG2] = orphan;
         (void) strncpy (arg2_word, orphan_word, 20);
      }
      orphan = 0;         
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
#if STYLE >= 11 && defined(ALL) && defined (EXCEPT)
      if (tp [tindex])
      {
         find_word (&type, &refno, &tadr, 3, 0);
         if (refno == EXCEPT)
         {
            tindex++;
            while (refno < BADWORD && 
               (separator [tindex] == ' ' || separator [tindex] == ','))
            {
               if (strcmp (tp [tindex], AND) != 0)
               {
                  find_word (&type, &refno, &tadr, 3, 1);
                  if (refno >= BADWORD)
                     break;
                  else if (refno > LOBJECT)
                  {
                     refno = BADSYNTAX;
                     break;
                  }
                  else
                  {
                     (void) advcpy (arg3_word, tadr);
                     except [except_count++] = refno;
                  }
 	       }
               tindex++;
            }
            value [ARG3] = -1;
            if (refno >= BADWORD)
               return;
         }
      }
#endif /* ALL and EXCEPT */
      if (tp [tindex] && strcmp (tp [tindex], AND) == 0 && 
         separator [tindex] == ' ')
            separator [++tindex] = ',';
      else if (separator[tindex] != ';')
      {
#if STYLE >= 11
         if (value [STATUS] > 1 && 
            (separator [tindex] == ' ' || separator [tindex] == ','))
               value [STATUS] = BADSYNTAX;
         if (tp [tindex])
            while (separator [++tindex] == ' ');
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
          tp [tindex + 1] = NULL;
#else /* STYLE < 11 */
         while (separator [++tindex] == ' ');
      }
   }
#endif /* STYLE */
   if (value [STATUS] == 1)
      value [ARG2] = -1;
#if STYLE >= 11
   else if (value [STATUS] == BADSYNTAX)
   {
/*      value [ARG1] = -1; */
      value [ARG2] = -1;
   }
#endif
   return;
}

/*===========================================================*/

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

/*===========================================================*/

#ifdef __STDC__
void make_name (char *file_name, char *save_name)
#else
void make_name (file_name, save_name)
char *file_name;
char *save_name;
#endif
{
   char *cptr;                 /* Discardable pointer to file_name */

   (void) strcpy (save_name, file_name);
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
#if !defined(unix) && ! defined(__CYGWIN__)
   *(save_name + 16) = '\0';
#endif
#endif /* MSDOS */
   if (strcmp (save_name + strlen (save_name) - 4, ".adv") != 0)
      (void) strcat (save_name, ".adv");
   return;
}

/*===========================================================*/

#ifdef __STDC__
int check_version (FILE *infile)
#else
int check_version (infile)
FILE *infile;
#endif
{
   int majvalg = 0;
   int minvalg = 0;
   int majvalt = 0;
   int minvalt = 0;
   char *gptr = GAMEID;
   char tchr = fgetc (infile);
   
   while (1)
   {
      if (*gptr == '\0' && tchr == '\n') return (0);
      if (! isalnum (tchr) && ! isalnum(*gptr)) break;
      if (tchr != *gptr) return (1);
      gptr++;
      tchr = fgetc (infile);
   }
   while (*gptr && ! isdigit (*gptr)) gptr++;
   while (tchr != '\n' && ! isdigit (tchr)) tchr = fgetc (infile);
   if (tchr == '\n' && *gptr == '\0') return (0);
   while (isdigit (*gptr) || *gptr == '.')
   {
      if (*gptr == '.') { majvalg = minvalg; minvalg = 0; }
      else              minvalg = 10 * minvalg + *gptr - '0';
      gptr++;
   }
   while (isdigit (tchr) || tchr == '.')
   {
      if (tchr == '.') { majvalt = minvalt; minvalt = 0; }
      else              minvalt = 10 * minvalt + tchr - '0';
      tchr = fgetc (infile);
   }
   if (majvalg != majvalt) return (1);
   if (minvalg < minvalt) return (1);
   while (tchr != '\n') tchr = fgetc (infile);
   return (0);
}

/*===========================================================*/

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

/*===========================================================*/

#ifdef __STDC__
int memstore (int key)
#else
int memstore (key)
int key;
#endif
{
/* Key -1  check for existence of memory image
 * Key 0   true memory save
 * Key 1   true memory restore
 * Key 2   temporary memory save
 * Key 3   temporary memory restore
 */
   FILE *memory_file = NULL;
   static char *image_base = NULL;   /* True memory save area */
   static char *image_temp = NULL;   /* Temp save over restore area */
   char *image_ptr;
#ifdef CONTEXT
   char *fname = (char *)(key < 2 ? ".M.adv" : ".T.adv");
#endif
   int result = 1;

   if (key < 0)
   {
#ifdef CONTEXT
      if (cgi)
      {
         if ((memory_file = fopen (fname, RMODE)) != NULL)
         {
            fclose (memory_file);
            result = 0;
         }
         return (result);
      }
#endif
      return (image_base ? 0 : 1);
   }

   image_ptr = key < 2 ? image_base : image_temp;
   if (key == 0 || key == 2)
   {
      if (image_ptr == NULL)
      {
         image_ptr = (char *) malloc (IMAGE_SIZE);
         if (image_ptr == NULL)
            return (1);
         if (key == 0)
            image_base = image_ptr;
         else
            image_temp = image_ptr;
      }
      memcpy (image_ptr, IMAGE, IMAGE_SIZE);
#ifdef CONTEXT
      if (cgi)
      {
         if ((memory_file = fopen (fname, WMODE)) != NULL &&
            fwrite (image_base, 1, IMAGE_SIZE, memory_file) == IMAGE_SIZE)
               result = 0;
         if (memory_file)
            fclose (memory_file);
         return (result);
      }
#endif
      return (0);
   }
   else
   {
#ifdef CONTEXT
      if (cgi)
      {
         if ((image_ptr = (char *) malloc (IMAGE_SIZE)) != NULL &&
             (memory_file = fopen (fname, RMODE)) != NULL &&
             (fread (image_ptr, 1, IMAGE_SIZE, memory_file)) == IMAGE_SIZE)
                result = 0;
         if (memory_file)
            fclose (memory_file);
         if (result)
            return (1);
      }
      else if (image_ptr  == NULL)
         return (1);
#else
      if (image_ptr  == NULL)
         return (1);
#endif /* CONTEXT */
      memcpy (IMAGE, image_ptr, IMAGE_SIZE);      
      return (0);
   }
}

#if STYLE >= 11

#include <dirent.h>

/*===========================================================*/

#ifdef __STDC__
int list_saved (int action, char *last_name)
#else
int list_saved (action, last_name)
int action;
char *last_name;
#endif
{
   int cnt = 0;
   char buf[16];
   DIR *dp;
   struct dirent *de;
   char *sfx;
#ifdef CONTEXT
   if (cgi) return (-1);
#endif
   *(buf + 15) = '\0';
   if ((dp = opendir(".")))
   {
      while ((de = readdir (dp)))
      {
         if (*(de->d_name) != '.' &&
            strcmp (sfx = de->d_name + strlen(de->d_name) - 4, 
               ".adv") == 0)
         {
            *sfx = '\0';
            if (action)
            {
               if (cnt)         
                  PRINTF (", ")
               PRINTF (de -> d_name);
            }
            else if (last_name)
               strncpy (buf, de -> d_name, 15);
	    cnt++;
         }
      }
      closedir (dp);
      if (action)
         PRINTF (".\n")
      if (last_name && cnt == 1)
      {
         value [ARG2] = 0;
         strcpy (last_name, buf);
      }
   }
   return (cnt);
}
#endif

/*===========================================================*/

#ifdef __STDC__
int special (int key, int *var)
#else
int special (key, var)
int key;
int *var;
#endif
{
   static char save_name [168];
   static char *scratch;
   char *image_ptr;
   char file_name [168];
   FILE *game_file;
   int val, val1;
   int lval;
   char tval [12];
   static int tsiz = sizeof (time_t);
   int chksum;
   int chksav;
   char *cptr;
   int cnt;
   int lobj, lplace, lverb, lvar, ltext;
   static int saved_value;
   static long game_time;
   void adv_hours ();
   void adv_news ();

   switch (key)
   {
      case 1:          /* Dump game to disc */
      case 2:          /* Restore game from disc */
         val = value [ARG2];
#ifndef CONTEXT
try_again:
#endif
         if (val >= 0)
         {
            if (*long_word && 
               strncmp (long_word, arg2_word, 16) == 0)
                  (void) strcpy (file_name, long_word);
            else
               (void) strcpy (file_name, arg2_word);
         }
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
         {
            strncpy (arg2_word, cgi_name, WORDSIZE - 1);
            (void) make_name (cgi_name, save_name);
         }
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
#if STYLE >= 11
               int cnt = list_saved (0, file_name);
               if (cnt == 0)
                  PRINTF (
   "Can't see any saved games here, but you may know of some elsewhere.\n")
               else if (cnt == 1)
               {
                  goto got_name;
               }
               else
               {
                  PRINTF ("You have the following saved games: ")
                  (void) list_saved (1, NULL);
               }
#endif
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
#if STYLE >= 11
got_name:
#endif
         (void) make_name (file_name, save_name);
#endif /* CONTEXT */
         if ((game_file = fopen (save_name, RMODE)) != NULL)
         {
            if (key == 2 || key == 999 || key == 997) 
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
         if (key == 2)
         {
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
         (void) fprintf (game_file, "%s\n", GAMEID);
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
         *value = -1;
         chksum = 0;
         CHKSUM(tval, sizeof(time_t))
         CHKSUM(IMAGE, VAL_SIZE)
         CHKSUM(IMAGE + OFFSET_LOCS, LOCS_SIZE)
         CHKSUM(IMAGE + OFFSET_OBJBIT, OBJBIT_SIZE)
         CHKSUM(IMAGE + OFFSET_PLACEBIT, PLACEBIT_SIZE)
         CHKSUM(IMAGE + OFFSET_VARBIT, VARBIT_SIZE)
#ifdef CONTEXT
         if (cgi && key == 998)
         {
            CHKSUM(qwords, sizeof(qwords));
            CHKSUM(qvals, sizeof(qvals));
         }
#endif /* CONTEXT */
         (void) fwrite (&chksum, sizeof (int), 1, game_file);
         (void) fwrite (tval, 1, sizeof(time_t), game_file);
         (void) fwrite (IMAGE, 1, IMAGE_SIZE, game_file);
#ifdef CONTEXT
         if (cgi && key == 998)
         {
            (void) fwrite (qwords, sizeof (char), sizeof (qwords), game_file);
            (void) fwrite (qvals, sizeof (char), sizeof (qvals), game_file);
            (void) fwrite (&mainseed, sizeof (int), 1, game_file);
            (void) fwrite (word_buf, sizeof (short), *word_buf - 1, game_file);
            (void) fwrite (old_comline, sizeof (char), sizeof (old_comline),
               game_file);
            (void) fwrite (long_word, sizeof (char), sizeof (long_word),
               game_file);
         }
#endif /* CONTEXT */
         *var = (ferror (game_file)) ? 1 : 0;
         (void) fclose (game_file);
#ifdef UNDO
         if (value [UNDO_STAT] >= 0 && diffs && (diffs < dptr || cgi))
         {
            strcpy (save_name + strlen(save_name) - 3, "adh");
            if (((diffs && dptr > diffs + 4) || (cgi && value [CONTEXT] <= 1)) &&
               (game_file = fopen (save_name, WMODE)))
            {
               int len = dptr - diffs;
               fwrite (&len, 1, sizeof (int), game_file);
               fwrite (diffs, 1, dptr - diffs, game_file);
               CHKSUM(diffs, len);
               fwrite (&chksum, 1, sizeof (chksum), game_file);
               len = edptr - diffs;
               fwrite (&len, 1, sizeof (int), game_file);
               fclose (game_file);
            }
         }
#endif /* UNDO */
         return (*var);

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
         if (check_version (game_file) != 0)
         {
            *var = 4;
            return (0);
         }
         val1 = 0;
         (void) fread (&val, sizeof (int), 1, game_file);
#ifdef DEBUG
         printf ("FOBJECT: image %3d, expected %3d\n", val, FOBJECT);
#endif /* DEBUG */
         if (val != FOBJECT) val1++;
         (void) fread (&lobj, sizeof (int), 1, game_file);
#ifdef DEBUG
         printf ("LOBJECT: image %3d, expected %3d\n", lobj, LOBJECT);
#endif /* DEBUG */
         if (lobj > LOBJECT) val1++;
         (void) fread (&lplace, sizeof (int), 1, game_file);
#ifdef DEBUG
         printf ("LPLACE: image %3d, expected %3d\n", lplace, LPLACE);
#endif /* DEBUG */
         if (lplace > LPLACE) val1++;
         (void) fread (&lverb, sizeof (int), 1, game_file);
#ifdef DEBUG
         printf ("LVERB: image %3d, expected %3d\n", lverb, LVERB);
#endif /* DEBUG */
         if (lverb > LVERB) val1++;
         (void) fread (&lvar, sizeof (int), 1, game_file);
#ifdef DEBUG
         printf ("LVARIABLE: image %3d, expected %3d\n", lvar, LVARIABLE);
#endif /* DEBUG */
         if (lvar > LVARIABLE) val1++;
         (void) fread (&ltext, sizeof (int), 1, game_file);
#ifdef DEBUG
         printf ("LTEXT: image %3d, expected %3d\n", ltext, LTEXT);
#endif /* DEBUG */
         if (ltext > LTEXT) val1++;

         if (val1)
         {
            *var = 2;
            (void) fclose (game_file);
            return (0);
         }
         chksav = 0;
#ifdef CONTEXT
         if (cgi != 'z' && cgi != 'y' && cgi != 'x')
         {
            *var = memstore (2);
            if (*var != 0)
               return (0);
         }
#endif
         if (scratch == NULL)
         {
            scratch = (char *) malloc (IMAGE_SIZE);
            if (scratch == NULL)
               return (0);
         }
         image_ptr = scratch;
#ifdef DEBUG
         puts ("Reading image...");
#endif
         (void) fread (&chksav, sizeof (int), 1, game_file);
#ifdef DEBUG
         PRINTF2("CHKSAV %d\n", chksav)
#endif
         (void) fread (tval, 1, sizeof (tval), game_file);
         if (*((int *)(tval + 4)) == -1)
            tsiz = 4;
         else if (*((int *)(tval + 8)) == -1)
            tsiz = 8;
         else
            tsiz = sizeof(time_t);
         fseek (game_file, tsiz - 12L, SEEK_CUR);
         {
            int locso = ltext * sizeof (int);
            int locss = (lobj + 1) * sizeof (int);
            int objbo = locso + locss;
            int objbs = OBJSIZE * (lobj - FOBJECT + 1) * sizeof (short);
            int plabo = objbo + objbs;
            int plabs = PLACESIZE * (lplace - lobj) * sizeof (short);
            int varbo = plabo + plabs;
            int varbs = VARSIZE * (lvar - lplace) * sizeof (short);
            int imgsiz = varbo + varbs;
            (void) fread (scratch, 1, imgsiz, game_file);
         }
#ifdef CONTEXT
         if (cgi && key == 999)
         {
            (void) fread (qwords, sizeof (char), sizeof (qwords), game_file);
            (void) fread (qvals, sizeof (char), sizeof (qvals), game_file);
            (void) fread (&mainseed, sizeof (int), 1, game_file);
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
            *long_word = '\0';
            if (! ferror (game_file))
            {
               (void) fread (long_word, sizeof (char), sizeof (long_word),
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
         {
            int locso = ltext * sizeof (int);
            int locss = (lobj + 1) * sizeof (int);
            int objbo = locso + locss;
            int objbs = OBJSIZE * (lobj - FOBJECT + 1) * sizeof (short);
            int plabo = objbo + objbs;
            int plabs = PLACESIZE * (lplace - lobj) * sizeof (short);
            int varbo = plabo + plabs;
            int varbs = VARSIZE * (lvar - lplace) * sizeof (short);
            int vrbbs = VARSIZE * (lverb - lplace) * sizeof (short);
            CHKSUM(tval, tsiz);
            CHKSUM(scratch, locso)
            CHKSUM(scratch + locso, locss)
            CHKSUM(scratch + objbo, objbs)
            CHKSUM(scratch + plabo, plabs)
            CHKSUM(scratch + varbo, varbs)
            if (val < LTEXT)    /* In case we added some texts since then! */
               while (val < LTEXT)
                  *(value + (val++)) = 0;
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
            if (tsiz == sizeof(game_time))
               memcpy (&game_time, tval, tsiz);
            else 
               game_time = 1;
            memset (IMAGE, '\0', IMAGE_SIZE);
            memcpy (value, scratch, (lobj + 1) * sizeof (int));
            memcpy (value + FPLACE, scratch + (lobj + 1) * sizeof (int), 
               (lplace - lobj) * sizeof (int));
            memcpy (value + FVERB, scratch + (lplace + 1) * sizeof (int), 
               (lverb - lplace) * sizeof (int));
            memcpy (value + FVARIABLE, scratch + (lverb + 1) * sizeof (int),
               (lvar - lverb - 1) * sizeof (int));
            memcpy (value + FTEXT, scratch + lvar * sizeof (int),
               (ltext - lvar) * sizeof (int));
            memcpy (location,  scratch + locso, locss);
            memcpy (objbits,   scratch + objbo, objbs);
            memcpy (placebits, scratch + plabo, plabs);
            memcpy (varbits,   scratch + varbo, vrbbs);
            memcpy ((char *)varbits + VRBBIT_SIZE, scratch + varbo + vrbbs, 
               varbs - vrbbs);
	 }
#ifdef CONTEXT
         if (key == 997) value [CONTEXT] = 2;
#endif

#ifdef UNDO
         if (value [UNDO_STAT] >= 0)
         {
            strcpy (save_name + strlen(save_name) - 3, "adh");
            if ((game_file = fopen (save_name, RMODE)))
            {
               int len;
               int diflen = len;
               unsigned char *d;
               if (diffs)
                  edptr = dptr = diffs + 4;
               fread (&len, 1, sizeof (int), game_file);
               if (len > 0)
               {
                  diflen = 8192 * ((len + 8191) / 8192);
                  d = (unsigned char *)malloc(diflen);
                  (void) fread (d, 1, len, game_file);
                  fread (&chksav, 1, sizeof (chksav), game_file);
                  CHKSUM(d, len);
                  if (chksum == chksav)
                  {
                     if (diffs)
                        free (diffs);
                     diffs = d;
                     diffsz = diflen;
                     dptr = diffs + len;
                     memcpy (image, IMAGE, sizeof(IMAGE));
                     fread (&len, 1, sizeof (int), game_file);
                     edptr = diffs + len;
                  }
               }
               fclose (game_file);
	    }            
         }
#endif /* UNDO */
         *var = 0;
         return (0);
      case 3:          /* Delete saved game */
#ifdef CONTEXT
         (void) make_name (arg2_word, save_name);
#endif         
         *var = unlink (save_name);
 if (*var)
 {
   printf ("Failed: %s - error code: %d<br />\n", save_name, *var);
   system ("pwd");
 }
         strcpy (save_name + strlen(save_name) - 3, "adh");
         (void) unlink (save_name);
         return (0);
      case 4:          /* Adv550 legacy - flush game cache */
      case 5:          /* Adv550 legacy - get prime time flag */
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
#if STYLE < 10
         *var = 0;
#else
         value [ARG1] = *var;
         fake (1, *var);
#endif
         return (0);
      case 10:        /* Fudge a value into ARG2 */
         value [ARG2] = *var;
         fake (2, *var);
         return (0);
      case 11:         /* Pretend player said "X X" instead of "X" */
         value [ARG2] = value [ARG1];
         strncpy (arg2_word, arg1_word, 20);
         value [STATUS] = 2;
         return (0);
      case 12:         /* Check for end of command */
         *var = (tp[tindex] == NULL);
         return (0);
/*    case 13: */         /* Spare */
      case 14:         /* Check for virgin game */
         if ((*var = (gv_file = fopen ("adv.vrg", RMODE)) ? 0 : 1) == 0)
            fclose (gv_file);
         return (0);
      case 15:         /* Note that he meditated, as he should */
         if ((gv_file = fopen ("adv.vrg", WMODE)))
            fclose (gv_file);
         return (0);
/*    case 16: */        /* Spare */
/*    case 17: */        /* Spare */
/*    case 18: */        /* Spare */
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
#ifdef READLINE
         cnt = lbp - lbuf;
         lbuf = (char *)realloc(lbuf, 2 * Maxlen + 1);
         lbp = lbuf + cnt;
#endif
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
#ifdef READLINE
         cnt = lbp - lbuf;
         lbuf = (char *)realloc(lbuf, 2 * Maxlen + 1);
         lbp = lbuf + cnt;
#endif
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

/*    case 25: */   /* Spare */
/*    case 26: */   /* Spare */

      case 27:    /* Pre-say */
         *var = 1;
         if (*say_buf)
         {
            PRINTF("\nOk - \"")
            PRINTF(say_buf)
            PRINTF("\"\n")
            *say_buf = '\0';
         }
         return (0);
         
      case 28:   /* Recover from failed restore */
         *var = memstore (3);
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
               val = varbits [ARG1 - FVERB + cnt];
               varbits [ARG1 - FVERB + cnt] = varbits [ARG2 - FVERB + cnt];
               varbits [ARG2 - FVERB + cnt] = val;
            }
            strcpy (temp_word, arg1_word);
            strcpy (arg1_word, arg2_word);
            strcpy (arg2_word, temp_word);
         }
         return (0);

/*      case 30:   Spare */
         
/*      case 31:   Spare */

      case 32:   /* Is the object on the exception list? */
#if STYLE >= 11 && defined (ALL) && defined (EXCEPT)
         if (except_count == 0)
         {
            *var = 0;
            return (0);
         }
         for (cnt = 0; cnt < except_count; cnt++)
         {
            if (*var == except [cnt])
            {
               *var = 1;
               return (0);
            }
         }
#endif /* ALL and EXCEPT */
         *var = 0;
         return (0);

      case 33:  /* Check for existence of a memory save */
#if STYLE >= 11
         *var = memstore (-1);
#else
         *var = 0;
#endif
         return (0);

      case 34:  /* List available saved games */
#if STYLE >= 11
         *var = list_saved (*var, arg2_word);
#else
         *var = 0;
#endif
         return (0);
         
      default:
         PRINTF2 ("\n \nGLITCH! Bad special code: %d\n", key);
         return (1);
   }
}

#ifdef USEDB

/*===========================================================*/

#ifdef __STDC__
void create_db (char *dbfile)
#else
void create_db (dbfile)
char *dbfile;
#endif
{
   FILE *db_file;
   char ch;
   int val = 0;
   int bytes = 0;
   int sgn = 0;
   
   if ((db_file = fopen (dbfile, WMODE)) == NULL)
      return;
   while (fgetc (text_file) != '{')
      if (feof (text_file))
         return;
   while (1)
   {
      ch = fgetc (text_file);
      if (feof (text_file))
         return;
      if (isdigit (ch))
      {
         if (sgn == 0)
            sgn = 1;
         val = 10 * val + ch - '0';   
      }
      else if (ch == '-' && sgn == 0)
         sgn = -1;
      else if (sgn)
      {
         if (sgn == -1)
            val = - val;
         fputc (val & 255, db_file);
         sgn = 0;
         val = 0;
         bytes++;
      }
      if (ch == '}')
         break;
   }
   fclose (db_file);
   if (bytes != TEXT_BYTES)
      return;
   printf ("\n(Database %s created...)\n", DBNAME);
}
#endif /* USEDB */

/*===========================================================*/

#ifdef __STDC__
int initialise (void)
#else
int initialise ()
#endif
{
#ifdef MEMORY
   int text_bytes;
#endif
#ifdef READFILE
   char text [100];
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

#ifndef GLK
#ifdef CONTEXT
   if (cgi != 'y')
#else
   if (dump_name == NULL || *dump_name == '\0')
#endif
#endif /* ! GLK */
   {
      PRINTF2 ("\n[A-code kernel version %s]\n", KERNEL_VERSION);
#ifdef CONTEXT
      if (cgi)
         PRINTF1 ("<br />\n");
#endif
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
      
#ifdef USEDB
      if (dbs_dir)
      {
         strncpy (data_file, dbs_dir, sizeof (data_file) - 14);
         ptr = data_file + strlen (data_file);
         *ptr++ = SEP;
         *ptr = '\0';
      }
      else if (ptr)
      { 
         if ((unsigned int)len > sizeof (data_file) - 13) 
            len = sizeof (data_file) - 13;
         strncpy (data_file, exec, len);
      }
#endif /* USEDB */
   }

#ifdef USEDB
   (void) strcat (data_file, DBNAME);

   if ((text_file = fopen (data_file, RMODE)) == NULL)
   {
      if ((text_file = fopen ("adv6.h", RMODE)))
         (void) create_db (data_file);
      else
      {
         (void) printf ("Sorry, can't find the %s data file.\n", data_file);
         close_files ();
         return (1);
      }
      if ((text_file = fopen (data_file, RMODE)) == NULL)
      {
         (void) printf ("Unable to find or construct the data file %s.\n",
            data_file);
         return (1);
      }
   }
#ifdef MEMORY
   text_bytes = fread (text, sizeof (char), TEXT_BYTES+1, text_file);
   (void) clearerr (text_file);
   (void) fclose (text_file);
   if (text_bytes != TEXT_BYTES)
   {
      (void) printf ("Wrong data file length: expected %d, got %d.\n",
         TEXT_BYTES, text_bytes);
      return (1);
   }
#endif /* MEMORY */
#ifdef SWAP
   chunk_end [0] = fread (text, sizeof (char), TEXT_CHUNK, text_file) - 1;
   chunk_start [0] = 0;
#endif /* SWAP */
#ifdef READFILE
   (void) fread (text, sizeof (char), sizeof (text), text_file);
#endif /* READFILE */
#endif /* USEDB */

   virgin = *text;
#ifdef PLAIN
   strcpy (title, text + 1);
#else
   title [0] = text [1] ^ KNOT;
   titlen = 0;
   while (++titlen < 80)
      if ((title [titlen] = text [titlen] ^ text [titlen + 1]) == '\0')
         break;
#endif /* PLAIN */
   
   if (strcmp (title, GAMEID) != 0)
   {
      (void) printf ("Version stamp mismatch!\n");
      return (1);
   }
   tp [0] = NULL;

   for (index = FOBJECT; index <= LOBJECT; index++)
      bitmod ('s', index, OBJECT);

   for (index = FPLACE; index <= LPLACE; index++)
      bitmod ('s', index, PLACE);

#if STYLE == 1 && defined(BRIEF)
   bitmod ('s', STATUS, BRIEF);
#endif

   if (com_name && *com_name && (com_file = fopen (com_name, RMODE)) == NULL)
   {
      (void) printf ("Sorry, unable to open command file '%s'!\n", com_name);
      exit (0);
   }
   if (com_file)
   {
      fgets (comline, sizeof (comline), com_file);
      if (strncmp (comline, "Wiz: ", 5) == 0)
         mainseed = atol (comline + 5);
      else if (strncmp (comline, GAMEID, strlen (GAMEID)) != 0)
      {
         printf ("%s: wrong adventure version!\n", com_name);
         exit (0);
      }
      else
         mainseed = atol (comline + strlen (GAMEID) + 1);
   }

   if (*log_name)
   {
      if ((log_file = fopen (log_name, "a+")) == NULL)
         (void) printf ("(Sorry, unable to open log file...)\n");
      else 
#ifdef CONTEXT
      if (cgi == 0 || cgi == 'x')
#endif /* CONTEXT */
         (void) fprintf (log_file, "%s: %u\n", GAMEID, mainseed);
   }

   for (index = 0; (unsigned int)index < 
                             sizeof (voc_refno) / sizeof (voc_refno [0]);
         index++)
      if (voc_refno [index] < 0)
      {
         voc_refno [index] *= -1;
         bitmod ('s', voc_refno [index], VERB + 1);
      }
            
   return (0);
}

#ifdef GLK
int argc = 0;
char **argv = NULL;

#ifdef _WIN32
#include <windows.h>
/* #include "WinGlk.h" */
char* arglist[1] = { "" };

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
#endif
#if defined(unix) || defined(linux) || defined(XGLK)
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

/*===========================================================*/

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
#ifdef USEDB
      {"-d", glkunix_arg_ValueFollows, "-d <dirname>: dbs directory"},
#endif /* USEDB */
      {"-r", glkunix_arg_ValueFollows, "[-r] <savefile>: restore game"},
      {"-c", glkunix_arg_ValueFollows, "-c <comfile>: replay game from log"},
      {"-log", glkunix_arg_ValueCanFollow, "-log [<logfile>]: log the game"},
      {"-h", glkunix_arg_NoValue, "-h: print help text"},
      {NULL, glkunix_arg_End, NULL }
   };
#endif /* unix || linux || XGLK */
void glk_main (void)
#else

/*===========================================================*/

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
            printf ("    -w                  invert default wrap/justify setting\n");
            printf ("    -b                  invert default setting for blank lines around prompt\n");
            printf ("    -s <W>x<H>[-<M>]    set screen size and margin\n");
            printf ("    -p                  invert default setting for pause before exiting\n");
#endif /* GLK */
#ifdef USEDB
            printf ("    -d <dbsdir>         specify dbs directory\n");
#endif /* USEDB */
            printf ("   [-r] <dumpfile>      restore game from dump\n");
            printf ("    -c <cominfile>      replay game from log\n");
            printf ("    -l <logfile>        log the game\n");
#ifdef UNDO
            if (undo_def != -2)
               printf ("    -u {on|off|forbid}  override default UNDO status\n");
#endif /* UNDO */
            printf ("    -h                  print this usage summary\n");
            exit (0);
         }
         if (--argc == 0) break;
         argv++;
         if (**argv == '-')
         {
            argv--;
            argc++;
            continue;
         }
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

#ifdef USEDB
            case 'd':
               dbs_dir = opt;
               break;
#endif /* USEDB */
               
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

#ifdef UNDO
            case 'u':
               if (undo_def == -2)
                  break;
               if (strcmp (opt, "off") == 0)
                  undo_def = -1;
               else if (strcmp (opt, "forbid") == 0)
                  undo_def = -2;
               else if (strcmp (opt, "on") == 0)
                  undo_def = 1;
               break;
#endif /* UNDO */

#ifdef CONTEXT
            case 'x':
            case 'y':
               cgi = *kwrd;
               strncpy (cgicom, opt, sizeof (cgicom));
               if (*log_name == '\0')
                  strcpy (log_name, "adv770.log");
               break;
#endif /* CONTEXT */               
            default:
               puts ("Bad args!");
               exit (0);
         }         
      }

#ifdef READLINE
   lbuf = (char *)malloc(2 * Maxlen + 1);
   lbp = lbuf;
#endif
#ifdef CONTEXT
   if (cgi) compress = 1;
#endif
   if (mainseed == 0)
      (void) time ((time_t *) &mainseed);
   rseed = mainseed %= 32768L;
   (void) irand (1);
   
   if (initialise () != 0)
   {
      (void) printf ("Sorry, unable to set up the world.\n");
#ifdef GLK
      glk_exit ();
#else
      return (0);
#endif
   }

#ifdef GLK
   glk_stylehint_set (wintype_TextBuffer, style_Normal, 
      stylehint_Justification, stylehint_just_LeftFlush);
   glk_set_style (style_Normal);
#endif
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
         p1();
         value [STATUS] = -1;
         value [ARG3] = -1;
         tindex = 1;
         tp[0] = dump_name;
         strncpy (arg2_word, dump_name, WORDSIZE);
         *(arg2_word + WORDSIZE - 1) = '\0';
      }
      else     
      {
         if (setjmp (loop_back) == 0)
            p1 ();
      }
   }
#else
   if (dump_name && *dump_name)
   {
      p1 ();
      value [STATUS] = -1;
      value [ARG3] = -1;
      strncpy (arg2_word, dump_name, WORDSIZE);
      *(arg2_word + WORDSIZE - 1) = '\0';
   }
   else
   {
      tindex = 0;
      tp [0] = NULL;
      if (setjmp (loop_back) == 0)
         p1 ();
   }
#endif /* CONTEXT */

#ifdef UNDO
   if (undo_def == -2)
      bitmod ('s', UNDO_STAT, UNDO_NONE);
   else if (undo_def == 1)
      bitmod ('s', UNDO_STAT, UNDO_INFO);
   else if (undo_def == -1)
   {
      bitmod ('s', UNDO_STAT, UNDO_INFO);
      bitmod ('s', UNDO_STAT, UNDO_OFF);
   }
#endif /* UNDO */

   (void) setjmp (loop_back);

   if (quitting) 
   {
      if (end_pause)
      {
         PRINTF ("(To exit, press ENTER)");
#ifdef GLK
         outbuf (1);
#else         
         getinput (comline, 160);
         putchar ('\n');
#endif
      }
      else
      {
         if (text_len > 0)
            outbuf (1);
         putchar ('\n');
#ifndef READLINE
         putchar ('\n');
#endif /* not READLINE */
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

/*===========================================================*/

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

/*===========================================================*/

#ifdef __STDC__
int isat (int l1,int l2,int l3, int l4)
#else
int isat (l1,l2,l3,l4)
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
   if (l4 == INHAND || !(bitest (l1, SCHIZOID))) return (0);
   if (location [l1] + 1 == l4) return (1);
#endif
   return (0);
}

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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
                       else bts = varbits [VARSIZE * (v2 - FVERB)]; }
   else  /* t2 == 'l'*/ { val = lv [v2];                            /* LOCAL */
                       bts = lb [VARSIZE * v2]; }
   if      (t1 == 'V') { value [v1] = val;                       /* VARIABLE */
                       cur = varbits [VARSIZE * (v1 - FVERB)]; }
   else if (t1 == 'L') { lv [v1] = val;                             /* LOCAL */
                       cur = lb [VARSIZE * v1]; }
   else  /* t1 == 'E'*/ value [v1] = val;             /* OBJECT, PLACE, TEXT */
   
   if      (t1 == 'V') {                                         /* VARIABLE */
      if      (bts == -1 && cur != -1) varbits [VARSIZE * (v1 - FVERB)] = -1;
      else if (bts != -1 && cur == -1) varbits [VARSIZE * (v1 - FVERB)] = 0; }
   else if (t1 == 'L') {                                            /* LOCAL */
      if      (bts == -1 && cur != -1) lb [VARSIZE * v1] = -1;
      else if (bts != -1 && cur == -1) lb [VARSIZE * v1] = 0; }
   else if (t1 == 'T')                                               /* TEXT */
   {
      val = text_info [2 * (v1 - FTEXT) + 1];
      if (val <= value [v1]) value [v1] = val - 1;
   }
}

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

#ifdef __STDC__
void finita (void)
#else
void finita ()
#endif
{
#if !defined(MEMORY) && !defined(PRELOADED)
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

/*===========================================================*/

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

/*===========================================================*/

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
   
   if (a2 > LVARIABLE) 
   {
      printf (
         "*** Run-time glitch! Setting flag on a flagless entity %d! ***\n", a2);
      return;
   }
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
      
/*===========================================================*/

#ifdef __STDC__
void lbitmod (int a0, char a1, int a2, int a3, int *a4, short *a5)
#else
void lbitmod (a0, a1, a2, a3, a4, a5)
int a0;
char a1;
int a2;
int a3;
int *a4;
short *a5;
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
      
/*===========================================================*/

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
   if (a1 < FVARIABLE && a1 > LVERB)
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

/*===========================================================*/

#ifdef __STDC__
int lbitest (int a1, int a2, int *a3, short *a4)
#else
int lbitest (a1, a2, a3, a4)
int a1;
int a2;
int *a3;
short *a4;
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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

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

/*===========================================================*/

#ifdef __STDC__
void glue_text (void)
#else
void glue_text();
#endif
{
/* Convert last message output into a fragment */
   while (*(lptr - 1) == '\n') lptr--;
}

/*===========================================================*/

#ifdef __STDC__
void verbatim (int arg)
#else
void verbatim(arg);
int arg;
#endif
{
   if (arg == ARG1)
      strncpy (arg1_word, tp [tindex - 1], WORDSIZE);
   else if (arg == ARG2 && value [STATUS] == 2)
      strncpy (arg2_word, tp [tindex - 1], WORDSIZE);
   else if (arg != ARG2)
   {
      (void) PRINTF2 ("GLITCH! Bad ARGn indicator: %d\n", arg);
   }
}

/*===========================================================*/

#ifdef __STDC__
int test (char *type)
#else
int test (type);
char *type;
#endif
{
   if (strcmp(type, "cgi") == 0)
#ifdef CONTEXT
      return (cgi);
#else
      return (0);
#endif
   if (strcmp(type, "doall") == 0)
      return (value_all);
      
   (void) PRINTF2 ("GLITCH! Bad test type: %s\n", type);
   return (0);
}
#ifdef UNDO

/*===========================================================*/

#ifdef __STDC__
int checkdo (void)
#else
int checkdo ()
#endif
{
   char *a;
   int val = 0;

   bitmod ('c', UNDO_STAT, UNDO_BAD);
   bitmod ('c', UNDO_STAT, UNDO_TRIM);
   bitmod ('c', UNDO_STAT, UNDO_INV);
#ifdef ALL
   if (value [ARG2] == ALL)
      val = 32767;
   else if (value[STATUS] > 1)
#else
   if (value[STATUS] > 1)
#endif
   {
      a = arg2_word;
      while (*a)
      {
         if (*a < '0' || *a >'9')
         {
            bitmod ('s', UNDO_STAT, UNDO_BAD);
            return (-1);
         }
         val = 10 * val + *a++ - '0';
      }
   }
   else
      val = 1;
   return (val);
}

/*===========================================================*/

#ifdef __STDC__
int inv_check (int mode)
#else
int inv_check (mode)
int mode;
#endif
{
   int i;
   if (mode == 0)
   {
      memcpy (inhand, location, LOCS_SIZE * sizeof(int));
      return (0);
   }
   for (i = 0; i <= LOBJECT; i++)
   {
      if ((inhand[i] == INHAND && location[i] != INHAND) ||
          (inhand[i] != INHAND && location[i] == INHAND))
             return (1);
   }
   return (0);
}

/*===========================================================*/

#ifdef __STDC__
void  undo (void)
#else
void undo ()
#endif
{
   int cnt;
   int acnt;
      
   if ((cnt = checkdo ()) < 0)
      return;
   if (diffsz == 0 || edptr <= diffs + 4)
      acnt = 0;
   else
   {
      (void) inv_check (0);
      for (acnt = 0; acnt < cnt; acnt++)
      {
         if (edptr <= diffs + 4)
            break;
         edptr -= 4;
         while (edptr > diffs)
         {
            int adr;
            edptr -= 4;
            adr = 256 * (*edptr) + *(edptr + 1);
            if (adr)
               *(IMAGE + adr) = *(edptr + 2);
            else
               break;
         }
         edptr += 4;
      }
      bitmod (inv_check (1) ? 's' : 'c', UNDO_STAT, UNDO_INV);
   }

   value [UNDO_STAT] = acnt;
#ifdef ALL
   if (value [ARG2] == ALL)
      cnt = acnt;
#endif
   bitmod (cnt > acnt ? 's' : 'c', UNDO_STAT, UNDO_TRIM);
   return;
}

/*===========================================================*/

#ifdef __STDC__
void redo (void)
#else
void redo ()
#endif
{
   int acnt;
   int cnt;
   
   if ((cnt = checkdo ()) < 0)
      return;

   if (edptr == dptr)
      acnt = 0;
   else
   {
      (void) inv_check (0);
      for (acnt = 0; acnt < cnt; acnt++)
      {
         if (edptr > dptr)
            edptr = dptr;
         while (1)
         {
            int adr = 256 * (*edptr) + *(edptr + 1);
            edptr += 4;
            if (adr)
               *(IMAGE + adr) = *(edptr - 1);
            else
               break;
         }
         if (edptr == dptr)
         {
            acnt++;
            break;
         }
      }
      bitmod (inv_check (1) ? 's' : 'c', UNDO_STAT, UNDO_INV);
   }
   value [UNDO_STAT] = acnt;
#ifdef ALL
   if (value [ARG2] == ALL)
      cnt = acnt;
#endif
   bitmod (cnt > acnt ? 's' : 'c', UNDO_STAT, UNDO_TRIM);
}
#endif /* UNDO */

/*************************************************************/
