#include "ptrace.h"


/**************** callbacks programme ******************/

// A partir d'ici, le code à remplir est spécifique au keygen

void callback_begin(pid_t pid)
{
  /*
    FIXME: code exécuté au début du débogage : placer un breakpoint à la
    bonne adresse, grâce à bp_set, pour pouvoir lire le serial dans la
    mémoire au moment du breakpoint
  */
}

void callback_breakpoint(pid_t pid, unsigned addr)
{
  /*
    FIXME: code exécuté au breakpoint : vérifier l'adresse du
    breakpoint, lire les registres et dans la mémoire pour récupérer et
    afficher le serial sur stderr
  */
}
