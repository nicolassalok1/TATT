#include "ptrace.h"


/**************** callbacks programme ******************/

// A partir d'ici, le code à remplir est spécifique au keygen

void callback_begin(pid_t pid)
{
  unsigned addr = 0x804861b;
  bp_set(pid, addr);
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

//NOT SURE

  struct user_regs_struct regs;

  regs_read(pid, &regs);

  for (unsigned i = 8; i < 20; i++)
  {
    mem_read_char(pid, regs.ebp + i);
  }
}
