/*						-*- coding: utf-8 -*-
 * test-token3.c	-- Test tokenizer
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date:  6-Jun-2012 23:48 (eg)
 * Last file update:  9-Jun-2012 00:12 (eg)
 */
#include <stdio.h>
#include <stdlib.h>
#include "tokenize.h"
#include "alias.h"

#define LIGNE "L > L; echo L; L; L1"


void affichage(struct token* T, int size)
{
  int i;

  /* afficher tous les tokens dus tableau T */
  for (i = 0; i < size; i++) {
    switch (T[i].type) {
    case item:      printf("  item [%s]\n", T[i].content); break;
    case error:     printf("  error [%s]\n", T[i].content); break;
    case less:      printf("  less\n"); break;
    case greater:   printf("  greater\n"); break;
    case append:    printf("  append\n"); break;
    case semicolon: printf("  semicolon\n"); break;
    case pip:       printf("  pip\n"); break;
    case amper:     printf("  amper\n"); break;
    case eol: 	/* pour faire plaisir à  GCC */;
    }
  }
}



int main()
{
  struct token tokens[100], *tok;
  int i, after;

  /* On définit 3 aliases:
          L => ls -l
	  L1 => L2
	  L2 => L
  */
  set_alias("L", "ls -l");
  set_alias("L1", "L2");
  set_alias("L2", "L");

  /* Construire un tableau de tokens à partir de LIGNE */
  i = 0;
  for (tok = get_token(LIGNE); tok->type != eol; tok = get_token(NULL)) {
    tokens[i++] = *tok;
  }

  /* Affichage avant expansion */
  printf("Les tokens avant expansion \n");
  affichage(tokens, i);

  /* On expanse */
  after = expand_tokens(tokens, i);

  /* Affichage après expansion */
  printf("Les tokens après expansion \n");
  affichage(tokens, after);

  return EXIT_SUCCESS;
}
