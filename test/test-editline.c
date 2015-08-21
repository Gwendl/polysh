/*						-*- coding: utf-8 -*-
 * test-editline.c	-- Test de editline
 * 
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 21-May-2010 00:03 (eg)
 * Last file update: 22-May-2010 22:55 (eg)
 */

#include <stdio.h>
#include <stdlib.h>
#include "editline.h"

#define MAXBUFF 150	/* taille max d'une ligne */

int main()
{
  char buff[MAXBUFF];
  
  while (editline(buff, MAXBUFF, "Test> ")) {
    printf("Ligne lue: '%s'\n", buff);
  }
  return EXIT_SUCCESS;
}
