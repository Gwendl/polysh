/*
 * alias.h	-- Gestion des alias
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date:  6-Jun-2012 11:47 (eg)
 * Last file update:  7-Jun-2012 19:12 (eg)
 */

#ifndef ALIAS_H
#  define ALIAS_H
#  include <stdio.h>

#define DEFAULT_ALLOC_INCR 50 	/* voir notes en fin de fichier*/
/* Chercher la valeur d'un alias (NULL si l'alias n'exsite pas) */
char *get_alias(const char *str);

/* Ajouter un alias */
void set_alias(const char *key, char *value);

/* Impression des alias dans le fichier f */
void print_aliases(FILE *f);


/* Notes:
 *    - La table des alias est initialisée avec DEFAULT_ALLOC_INCR cases. Si
 *      le nombre d'aliases augmente, la taille de cette table est augmentée
 *      dynamiquement
 */
#endif
