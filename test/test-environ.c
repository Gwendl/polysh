/*						-*- coding: utf-8 -*-
 * test-environ.c	-- test de l'environnement
 * 
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 22-May-2010 01:21 (eg)
 * Last file update: 22-May-2010 01:39 (eg)
 */

#include <stdio.h>
#include <stdlib.h>

#include "environ.h"

int main()
{
  /* Afficher l'environnement intial */
  print_environ(stdout);
  
  printf("Valeur de HOME = '%s'\n", get_environ("HOME"));
  printf("Valeur de absent = '%s'\n", get_environ("absent"));
  set_environ("present", "OK");
  printf("Valeur de present = '%s'\n", get_environ("present"));
  set_environ("HOME", "/foo/bar");
  printf("Valeur de HOME = '%s'\n", get_environ("HOME"));
  print_environ(stdout);

  return EXIT_SUCCESS;
}
