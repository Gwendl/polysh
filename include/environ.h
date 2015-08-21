/*						-*- coding: utf-8 -*-
 * environ.h	-- Gestion des variables d'environnement
 * 
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 21-May-2010 17:59 (eg)
 * Last file update: 25-May-2010 12:11 (eg)
 */

#ifndef ENVIRON_H
#  define ENVIRON_H
#  include <stdio.h>

#define DEFAULT_ALLOC_INCR 50 	/* voir notes en fin de fichier*/

extern char **Environ;		/* l'environnement */

/* Manipulation des variables d'environnement */
char *get_environ(const char *s);
void  set_environ(const char *var, const char *valeur);

/* Impression de l 'environnement sur le fichier f */
void  print_environ(FILE *f);

/* Ajouter les paramètres (dans argv) à l'environnement. De plus, 
 *  construire, la variable spéciale  "$#"  */
void add_program_parameters_environ(int argc, char *argv[]);

/* Notes:
 *    - L'environnement contient au moins les variables suivantes:
 *        . HOME qui contient le chemin où l'on va si on fait 
 *	    un cd sans paramètre - Défaut le "homedir de l'utilisateur
 *	  . PATH (comme sh) - Defaut: /bin:/usr/bin:/usr/local/bin
 *	  . IFS  (comme sh) - Défaut: espace tab et newline
 *	  . PROMPT qui contient la chaîne affichée en guise de prompt 
 *        . TERM qui contient le type de terminal - Défaut: xterm
 *	  . PWD qui contient le répertoire courant
 *	  . $1 ... $9 qui contiennent les paramètres de la commande polysh
 *    - L'environnement est initialisé avec DEFAULT_ALLOC_INCR cases. Si 
 *      le nombre de variables d'environnement augmente, la taille de 
 *      l'environnement est augmentée dynamiquement
 */
#endif
