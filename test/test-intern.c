/*						-*- coding: utf-8 -*-
  * test-intern.c	-- test des fonctions internes du shell
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 22-May-2010 15:18 (eg)
 * Last file update:  8-Jun-2012 23:55 (eg)
 */

#include <stdio.h>
#include <stdlib.h>
#include "intern.h"
#include "environ.h"

int main()
{
  internal_cmd cmd;

  /* Trouver pwd et l'appeler */
  printf("Test pwd\n");
  cmd = find_internal("pwd");
  cmd(0, NULL);

  /* Appeler echo */
  printf("Test echo\n");
  {
    char *argv[] = { "echo", "A", "B", "C", NULL};

    cmd = find_internal("echo");
    cmd(4, argv);
  }

  /* Test de la fonction read */
  {
    char *argv[] = { "read", "foo", NULL};

    printf("Entrer une valeur pour la variable foo? "); fflush(stdout);
    cmd = find_internal("read");
    cmd(2, argv);
    printf("foo = %s\n", get_environ("foo"));
  }

  /* Test d'un fonction inexistante */
  cmd = find_internal("blabla");
  if (cmd)
    printf("Allo Huston, nous avons un problème\n");
  else
    printf("OK\n");

  /* Test de la fonction exit */
  {
    char *argv[] = { "exit", "42", NULL};

    cmd = find_internal("exit");
    cmd(2, argv);
    printf("Ce message ne doit pas apparaitre\n");
  }
  return EXIT_FAILURE;
}


