/* adv0.h: A-code kernel - copyleft Mike Arnautov 1990-2007.
 *
 * 01 May 07   S. Munro       Bug: Added STDC definition of procs[]().
 */

#ifdef FILE
#  undef FILE
#endif
#include <stdio.h>
#include <setjmp.h>
#ifdef __STDC__
extern void say (int key, int what, int qualifier);
extern int query (int textref);
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
extern void outchar (int text_char);
extern char *outline (char *addr, int char_count, int break_count, int fill);
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
extern void verbatim (int);
extern int memstore (int);
extern int test (char *);
extern void undo (void);
extern void redo (void);
extern void (*procs[])(void);
#else
extern void say ();
extern int query ();
extern int special ();
extern int ishere ();
extern int isat ();
extern int isnear ();
extern void apport ();
extern void set ();
extern void lda ();
extern void eval ();
extern void deposit ();
extern void locate ();
extern int evar ();
extern short *bitword ();
extern void bitmod ();
extern int bitest ();
extern void outchar ();
extern char *outline ();
extern void finita ();
extern int irand ();
extern int have ();
extern void flush_command ();
extern void input ();
extern void default_to ();
extern void voc ();
extern int anyof ();
extern int keyword ();
extern void move ();
extern void tie ();
extern int jrand ();
extern void glue_text ();
extern void verbatim ();
extern int memstore ();
extern int test();
extern void undo();
extern void redo();
extern void (*procs[])();
#endif
extern jmp_buf loop_back;
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
#endif
