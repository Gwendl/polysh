/*						-*- coding: utf-8 -*-
 * toplevel.h	-- Toplevel de l'interprète
 * 
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 22-May-2010 18:14 (eg)
 * Last file update:  5-Jun-2012 11:56 (eg)
 */

#ifndef TOPLEVEL_H
#  define TOPLEVEL_H

/* La fonction toplevel execute toutes les lignes du fichier (ouvert)
 * qui lui est passé en paramètre. C'est la boucle centrale du shell.
 */
void toplevel(FILE *f);

/* La fonction execute_script essaie d'ouvrir le fichier path en
 * lecture et lance la fonction toplevel dessus. Si le fichier peut
 * être ouvert, elle renvoie EXIT_SUCCESS. Sinon, elle renvoie la
 * valeur EXIT_FAILURE
 */
int execute_script(char *path);
#endif
