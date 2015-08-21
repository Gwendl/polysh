/*
 * test-alias.c	-- test des alias
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date:  6-Jun-2012 12:39 (eg)
 * Last file update:  6-Jun-2012 12:44 (eg)
 */

#include <stdio.h>
#include <stdlib.h>
#include "alias.h"

#define MAXBUFF   50	/* taille max d'une alias ou d'une clé */
#define MAX       200

int main(void)
{
  int i;
  char key[MAXBUFF], val[MAXBUFF];

  for (i = 0; i < MAX; i++) {
    sprintf(key, "key%d", i);
    sprintf(val, "Value de l'alias key%d", i);
    set_alias(key, val);
  }

  printf("Table des alias\n");
  print_aliases(stdout);
  printf("------\n");
  printf("Alias pour key0: [%s]\n", get_alias("key0"));
  printf("Alias pour foo (doit être null): %p\n", get_alias("foo"));
  printf("On ajoute l'alias pour foo\n");
  set_alias("foo", "bar bien-sur");
  printf("Alias pour foo: [%s]\n", get_alias("foo"));
  printf("On le change\n");
  set_alias("foo", "GEE!!!!");
  printf("Alias pour foo: [%s]\n", get_alias("foo"));
}
