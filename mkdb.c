#include <stdio.h>
#include <ctype.h>

int main ()
{
   FILE *infile;
   FILE *outfile;
   char *ptr;
   char *bptr;
   int val;
   int count = 0;
   char ch;
   int sign;
   char line [80];
   char dbname [80];
   int bytes = 0;
   
   if ((infile = fopen ("adv1.h", "r")) == NULL)
   {
      puts ("Can't open adv1.h!\n");
      exit (1);
   }
   fgets (line, sizeof (line) - 1, infile);
   while (*line != '#')
      fgets (line, sizeof (line) - 1, infile);
   fgets (line, sizeof (line) - 1, infile);
   fgets (line, sizeof (line) - 1, infile);
   ptr = line;
   while (*ptr != '"') ptr++;
   ptr++;
   bptr = dbname;
   while (*ptr != '"')
      *bptr++ = *ptr++;
   *bptr = '\0';
   fgets (line, sizeof (line) - 1, infile);
   fgets (line, sizeof (line) - 1, infile);
   ptr = line;
   while (*ptr == ' ') ptr++;
   while (*ptr != ' ') ptr++;
   while (*ptr == ' ') ptr++;
   while (*ptr != ' ') ptr++;
   while (*ptr == ' ') ptr++;
   while (isdigit (*ptr)) 
      bytes = 10 * bytes + *ptr++ - '0';
   if ((infile = fopen ("adv6.h", "r")) == NULL)
   {
      puts ("Can't open adv6.h!\n");
      exit (1);
   }
   if ((outfile = fopen (dbname, "w")) == NULL)
   {
      printf ("Can't open %s!\n", dbname);
      exit (1);
   }
   while (fgetc (infile) != '{') ;
   while (fgetc (infile) != '0') ;
   ch = '0';
   sign = 0;
   val = 0;
   while (1)
   {
      while (isdigit (ch = fgetc (infile)))
         val = 10 * val + ch - '0';
      if (sign)
         val = -val;
      fputc (val & 255, outfile);
      count++;
      if (ch == '}') break;
      while (! isdigit (ch = fgetc (infile)) && ch != '-' && ch != '}') ;
      if (ch == '}') break;
      if (ch == '-')
      {
         val = 0;
         sign = 1;
      }
      else if (isdigit (ch))
      {
         val = ch - '0';
         sign = 0;
      }
      else
      {
         puts ("Bad syntax!");
         break;
      }
   }
   fclose (infile);
   fclose (outfile);
   if (count != bytes)
   {
      puts ("Wrong amount of text data!");
      unlink (dbname);
      exit (1);
   }
   printf ("Dbs %s created.\n", dbname);
   exit (0);
}
