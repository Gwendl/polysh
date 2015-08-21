/*						-*- coding: utf-8 -*-
 * editline.h	-- Editeur en mode ligne
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 20-May-2010 23:09 (eg)
 * Last file update: 30-Jun-2015 16:10 (eg)
 */

#include <signal.h>
#include <setjmp.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <stdio.h>

#include "history.h"
#include "editline.h"

#define Ctrl(x)		(x - 64)
#define DELETE 		127
#define ESCAPE		27

static int pos;		/* Position courante dans la commande en cours d'edition */
static int lg;          /* Longueur de la commande en cours d'edition */
static int old_lg;

static char *kill_buff = NULL;     /* Le kill-buffer utilise par ^K           */
static int lg_kill = 0;            /* Taille de la chaine dans le kill buffer */
static sigjmp_buf retour;	   /* Le point ou il faut revenir sur un ^C   */

static char *the_prompt; 	   /* Sauvegarde du prompt courant */


/*======================================================================
 * Utilitaires
 *======================================================================
 */
static void echo(char c)
{
  write(1, &c, 1);
}

static void printstring(char *s)
{
  write(1, s, strlen(s));
}

static void print_prompt(void)
{
  echo('\r'); printstring(the_prompt);
}

static void beep(void)
{
  echo('\a');
}

/*
 * Gestion de la tty
 *
 */
static void set_tty(struct termios *old)
{
  struct termios t;

  /* Recupérer le mode actuel */
  tcgetattr(0, &t);
  *old = t;

  /* Se mettre en mode non canonique et sans echo */
  t.c_lflag &= ~(ICANON | ECHO);
  t.c_cc[VMIN] = 1;
  t.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &t);
}

static void restore_tty(const struct termios *t)
{
  /* Retour au mode canonique */
   tcsetattr(0, TCSANOW, t);
}


/*
 * La fonction redisplay gère le reaffichage de la chaine "s" de facon minimale.
 * Lorsque la fonction termine son execution, le curseur est place en "pos".
 *
 */
static void redisplay(char *s, int newpos)
{
  register int i, j;
  register char *p;

  /**** 1ere phase: positionner le curseur a sa place definitive ****/
  if (pos < newpos)
    for (p=&s[pos]; p < &s[newpos]; p++) echo(*p);
  else
    if (newpos == 0) /* petite optimisation */ print_prompt();
    else
      for(i=pos ; i > newpos; i--) echo('\b');

  /**** 2e phase: si la longueur de la chaine a change, "toucher" la fin ****/
  if (lg !=  old_lg) {
    /* Aller a la fin de la chaine */
    for (i=0, p=&s[newpos]; p < &s[lg]; i++, p++) echo(*p);

    /* Recouvrir la  fin avec des espaces */
    for(j = lg; j < old_lg; j++, i++) echo(' ');

    /* Remettre le curseur a sa place (i.e. reculer de i caracteres) */
    for( ; i; i--) echo('\b');
  }
  fflush(stdout);

  old_lg = lg; pos = newpos;
}

static void ControlC(int sig)
{
  signal(sig, ControlC);  /* Just in case ... */
  echo('\n');
  print_prompt();
  siglongjmp(retour, 1);
}


char *editline(char *s, const int size, const char *prompt)
{
  char c;
  void (*save_signal)();
  struct termios save_term;

  /* Affichage du prompt */
  the_prompt = (char *) prompt;
  print_prompt();

  /* Edition proprement dite */
  set_tty(&save_term);
  save_signal=signal(SIGINT, ControlC);
  sigsetjmp(retour, 1);

  pos = lg = old_lg = 0;

  while (read(0, &c, 1)==1 && c != '\n' && c != '\r') {
  top:
    switch (c) {
      case Ctrl('A'): redisplay(s, 0);	 			break;
      case Ctrl('E'): redisplay(s, lg);	 			break;
      case Ctrl('B'): if (pos > 0) redisplay(s, pos-1);		break;
      case Ctrl('F'): if (pos <lg) redisplay(s, pos+1);     	break;
      case Ctrl('D'): if (pos != lg) {
			memmove(&s[pos], &s[pos+1], lg-pos);
			lg -= 1;
			redisplay(s, pos);
		      }
		      else
			if (pos == 0) {/* ^D sur un debut de ligne <=> exit */
			  s = NULL;
			  goto cleanup;
			}
		      break;
      case Ctrl('H'):
      case DELETE   : if (pos > 0) {
			memmove(&s[pos-1], &s[pos], lg-pos);
			lg -= 1;
			redisplay(s, pos-1);
		      }
		      break;

      case Ctrl('P'):
      case Ctrl('N'): strcpy(s, c == Ctrl('P') ?  previous_history() :
						  next_history());
		      print_prompt();
		      printstring(s);
		      lg = pos = strlen(s);
		      redisplay(s, pos);
		      break;
    default:          if (lg < size-1 && ' ' <= c && c <= '~') {
			memmove(&s[pos+1], &s[pos], lg-pos);
			s[pos] = c;
			lg += 1;
			redisplay(s, pos+1);
		      }
		      else beep();
    }
  }
  s[lg]   = '\0';

  /* Placer le curseur a la ligne et mettre un \n dans le buffer */
  echo('\r');echo('\n');

  /* Remettre les choses qu'on avait touchées en place */
  cleanup:
    signal(SIGINT, save_signal);
    restore_tty(&save_term);

  return s;
}

