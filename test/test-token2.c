/*						-*- coding: utf-8 -*-
 * test-token2.c	-- Test tokenizer
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 22-May-2010 10:53 (eg)
 * Last file update:  6-Jun-2012 23:48 (eg)
 */
#include <stdio.h>
#include <stdlib.h>
#include "tokenize.h"

#define MAXBUFF 500
#define INPUT   "data/input"


int main()
{
  char line[MAXBUFF];
  struct token *tok;
  FILE *f;

  if (!(f = fopen(INPUT, "r"))) {
    fprintf(stderr, "cannot open file %s\n", INPUT);
    return EXIT_FAILURE;
  }

  while (fgets(line, MAXBUFF, f)) {
    printf("======== %s", line);
    /* afficher tous les tokens de la ligne */
    for (tok = get_token(line); tok->type != eol; tok = get_token(NULL)) {
      switch (tok->type) {
	case item:      printf("  item [%s]\n", tok->content);
			free(tok->content);
			break;
        case error:     printf("  error [%s]\n", tok->content);
			free(tok->content);
			break;
	case less:      printf("  less\n"); break;
	case greater:   printf("  greater\n"); break;
	case append:    printf("  append\n"); break;
	case semicolon: printf("  semicolon\n"); break;
	case pip:       printf("  pip\n"); break;
	case amper:     printf("  amper\n"); break;
        case eol: 	/* pour faire plaisir Ã  GCC */;
      }
    }
    printf("  eol\n");
  }
  printf("END\n");
  fclose(f);
  return EXIT_SUCCESS;
}
