/*						-*- coding: utf-8 -*-
 * history.h	-- historique de lignes de commandes
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 20-May-2010 23:09 (eg)
 * Last file update:  8-Jun-2012 21:52 (eg)
 */

#ifndef HISTORY_H
#  define HISTORY_H
#  include <stdio.h>

#define HISTORY_DEFAULT_SIZE	100 	/* taille par défaut de l'historique */

/* init. de  l'historique. size est le nombre de lignes a conserver en mémoire
 * et histfile est le fichier qui contient l'historique des commandes.
 * Si histfile est NULL, il n'y aura pas de fichier de sauvegarde.
 *
 * La sauvegarde de l'historique est assurée grace au mécanisme atexit(3)  
 *
 */
void init_history(int size, const char *histfile);

/* afficher l'historique dans le fichier f */
void print_history(FILE *f);

/* ajouter une ligne dans l'historique */
void add_history(const char *s);

/* avance/reculer dans l'historique */
char *next_history(void);
char *previous_history(void);

/* Notes:
 *   - si la fonction init_history n'est pas appelée par l'utilisateur, on se
 *     débrouille pour que le programme ne se plante pas.
 */
#endif
