/*						-*- coding: utf-8 -*-
 * tokenize.h			-- shell tokenizer
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 22-May-2010 08:39 (eg)
 * Last file update:  7-Jun-2012 21:41 (eg)
 */

#ifndef TOKENIZE_H
#  define TOKENIZE_H

#define MAX_TOK_SIZE 500	/* taille max d'un "mot" renvoyé par get_token */
#define MAX_TOKEN 200		/* nombre max de tokens dans une ligne shell   */
#define MAX_EXPAND_LOOP 30	/* Nombre max de tour pou expansion des alias  */

enum token_type { item, less, greater, append, semicolon, pip, amper, eol,
		  error };


struct token {
  enum token_type type;
  char *content; 	/* content ne sert que quand type = item ou error */
};

/* Trouver le prochain token dans line
 * Cette  fonction a un comportement proche de celui de la fonction
 * standard strtok:
 *     - quand la fonction est appelée avec line non NULL, on renvoie
 *       le premier token de line.
 *     - quand line est NULL, on continue de là où l'on s'était arrêté
 *       précédemment (i.e. on renvoie le token suivant).
 */
struct token *get_token(char *line);


/* Expansion des tokens:
 * Cette fonction part d'une liste de token de longueur count et en
 * reconstruit une autre. La valeur de retour de cette fonction correpond à la
 * taille de la liste construite
 *
 * expand_tokens travaille en deux temps:
 *   - Dans un premier temps: elle s'occupe de l'expansion des aliases. Voir la note
 *     à ce sujet plus bas.
 *   - Dans une second temps: elle s'occupe de remplacer les utilisations de variable
 *     shell par leur valeur. Ainsi, $XYZ est remplacé par la valeur de la variable
 *     XYZ, ou la chaîne vide si cette variable n'existe pas
 */
int expand_tokens(struct token *tokens, int count);


/* Libération des token contenant de l'information allouée dynamiquement
 * (item et error) */
void free_tokens(struct token *tokens, int count);



/* Notes:
 *     - Type de token renvoyé:
 *         '<'	           less
 *	   '>'	           greater
 *	   '>>'	           append
 *	   ';'	           semicolon
 *	   '|'	           pip
 *	   '&'	           amp
 *         fin de ligne    eol
 *	   autre           item (et dans ce cas 'content' contient
 *                               la valeur de l'item)
 *
 *     - get_token saute les commentaires (de # à la fin de la ligne)
 *     - Quand on rencontre une variable ($XYZ) on renvoie sa valeur
 *     - get_token reconnait les chaînes entre simples quotes ou guillemets
 *     - Il n'y a pas d'évaluation des variables dans les chaînes (même
 *       celles avec des guillemets (contrairement aux shells classiques)
 *     - le caractère \ peut être utilisé dans une chaine pour protéger un
 *       guillemet ou une quote
 *     - en cas  d'erreur (typiquement une chaîne non terminée sur fin de ligne
 *       le type du token est "error" et "content" contient un message d'erreur
 *
 * Notes sur l'expansion des alias:
 * -------------------------------
 *
 * Supposons que l'on ait l'alias "l" défini à "ls -l"
 *
 * Soit la ligne de shell:
 *     $ l > l; cat l; l
 * on a en entrée la suite d'items:
 *   [item l] [greater] [item l] [semicolon] [item cat] [item l] [semicolon] [item l]
 * après expansion, on doit avoir dans notre tableaiu, la suite:
 *   [item ls] [item l] [greater] [item l] [semicolon] [item cat] [item l]
 *   [semicolon] [item ls] [item l]
 * ce qui correpond à la commande
 *     $ ls -l > l; cat l; ls -l
 * Tous les "l" ne sont donc pas remplacés par "ls -l"
 *
 * Expansion d'alias multiple
 * si on a
 *    $ alias a b
 *    $ alias b c
 *    $ alias c l
 * alors la commande "a" provoquera l'éxécution de "ls -l".
 * 
 * Attention: ce mécanisme peut introduire des boucle (si a => b et b =>a).
 * La recherche d'expansions se fait donc au maximum MAX_EXPAND_LOOP fois dans
 * une ligne.
 */
#endif
