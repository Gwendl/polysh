/*						-*- coding: utf-8 -*-
 * test-history.c	-- Test de editline avec historique
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 21-May-2010 00:03 (eg)
 * Last file update:  6-Jun-2012 12:26 (eg)
 */

#include <stdio.h>
#include <stdlib.h>
#include "editline.h"
#include "history.h"

#define MAXBUFF 150	/* taille max d'une ligne */
#define MAXHIST 5

int main()
{
  char buff[MAXBUFF];
  int i;


  init_history(MAXHIST, NULL);
  /* Entrer des lignes dans l'historique. Ca sert à rien, c'est pour tester */
  for (i = 0; i < MAXHIST-2; i++) {
    snprintf(buff, MAXBUFF , "Ligne #%d", i);
    add_history(buff);
  }

  /* Boucle de lecture */
  while (editline(buff, MAXBUFF, "\033[7mTest>\033[0m ")) {
    printf("Ligne lue: '%s'\n", buff);
    if (*buff)
      add_history(buff);
  }

  /* Afficher l'historique */
  printf("\nHistorique: \n");
  print_history(stdout);

  return EXIT_SUCCESS;
}
