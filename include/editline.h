/*						-*- coding: utf-8 -*-
 * editline.h	-- Editeur en mode ligne
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 20-May-2010 23:09 (eg)
 * Last file update:  8-Jun-2012 20:08 (eg)
 */

#ifndef EDITLINE_H
#  define EDITLINE_H
/* Description de l'éditeur de commandes de Polysh
 *
 * Les caractères traités sont un sous-ensemble de ceux de emacs. Ils
 * se limitent toutefois aux commandes suivantes:
 *   - Ctrl-A: aller au début de la ligne
 *   - Ctrl-B: caractère précédent
 *   - Ctrl-D: effacer le caractère courant (sortie de polysh si la ligne
 *             est vide)
 *   - Ctrl-E: aller à la fin de la ligne
 *   - Ctrl-F: caractère suivant
 *   - Ctrl-H (Backspace) ou Delete: effacer le caractère précédent
 *   - Ctrl-K: effacer jusqu'à la fin de la ligne
 *   - Ctrl-L: ré-afficher la ligne courante
 *   - Ctrl-M (Return): exécuter la ligne saisie
 *   - Ctrl-N: commande suivante de l'historique
 *   - Ctrl-P: commande précédente de l'historique
 *   - Ctrl-Y: restituer le texte détruit par Ctrl-K
 *   - Note: l'éditeur prend aussi en compte les touches fléchées.
 * 
 * Cette fontion prend en paramètre un buffer dont on spécifie la taille où
 * la ligne devra être rangée. Elle rend l'adresse de la ligne saisie
 * ou NULL si la fin de fichier est atteinte.
 */

extern char *editline(char *s, const int size, const char *prompt);


/* Note:
   Pour construire l'éditeur on jouera avec les caractères suivants:
      '\b' qui recule d'une position
      '\r' qui se place en début de ligne.
      ' '  pour effacer du texte qui se trouve déjà sur la ligne
  Principe:
     Soit une ligne contenant le texte "ABCDE" et le curseur placé sur
     le "B". Si on efface le caractère courant. Il suffit d'afficher
     la chaîne "CDE \b\b\b\b" pour obtenir "ACDE" sur l'écran (en fait il y
     a un espace supplémentaire à la fin, mais comme on ne le voit pas,
     l'illusion sera parfaite (bon, si on a une ligne longue qui dépasse
     une ligne du terminal, c'est plus tout à fait vrai, et cela
     dépend du terminal que l'on utilise).
 */
#endif
