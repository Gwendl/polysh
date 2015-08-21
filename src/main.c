/*						-*- coding: utf-8 -*-
 * main.c	-- Polysh: le programme principal
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 22-May-2010 18:05 (eg)
 * Last file update:  8-Jun-2012 21:53 (eg)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include "polysh.h"
#include "toplevel.h"
#include "history.h"
#include "environ.h"


static char *absolute_path(const char *fn) /* Quick & dirty */
{
  char path[PATH_MAX] = "";
  char *home = getenv("HOME");

  if (home)
    snprintf(path,  PATH_MAX, "%s/%s", home, fn);

  return strdup(path);
}


int main(int argc, char *argv[])
{
  FILE *f         = stdin;
  char *rc_file   = absolute_path(RC_FILE);
  char *hist_file = absolute_path(HIST_FILE);

  if (argc > 1) {
    /* On travaille sur un shell script: lui passer les arguments et le lancer */
    add_program_parameters_environ(argc-1, argv+1);
    return execute_script(argv[1]);
  }
  else {
    /* Imprimer une bannière */
    fprintf(stderr, "Bienvenue sur %s version %s\n", SHELL_NAME, VERSION);

    /* lancer éventuellement le script d'initialisation de l'utilisateur*/
    if (access(rc_file, R_OK) == 0)
      execute_script(rc_file);

    /* Passer les paramètres (ici 0 param) et appeler le toplevel de l'interprete */
    add_program_parameters_environ(1, argv);

    /* Gérer l'historique (la sauvegarde se fera automatiquement)  */
    init_history(HISTORY_DEFAULT_SIZE, hist_file);

    /* Lancement du toplevel de l'interprète */
    toplevel(f);
    fprintf(stderr, "Bye\n");
  }

  return EXIT_SUCCESS;
}
