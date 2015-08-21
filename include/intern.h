/*						-*- coding: utf-8 -*-
 * intern.h	-- Shell internal commands
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 22-May-2010 12:54 (eg)
 * Last file update: 22-May-2010 15:01 (eg)
 */

#ifndef INTERN_H
#  define INTERN_H

typedef void (*internal_cmd)(int argc, char*arg[]);

/* Cette fonction renvoie un pointeur sur la fonction de nom "name", 
 * si elle existe. Dans le cas contraire, la fonction renvoie NULL */
internal_cmd find_internal(char *name);

/* Note: 
 *    Les fonction internes que l'on a: 
 *      - cd (ou chdir) avec ou sans paramètre
 *	- echo
 *	- exit avec ou sans parametre (sans paramètre => 0)
 *	- pwd
 *	- read avec un parametre (nom de la variable contenat la ligne lue)
 *	- set: 2 formes
 *	     . sans paramètre affiche l'environnement
 *	     . avec 2 paramètres: set VAR valeur 
 *	- history affiche l'historique
 */
#endif
