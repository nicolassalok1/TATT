#include "ptrace.h"


/**************** callbacks programme ******************/

// A partir d'ici, le code à remplir est spécifique au keygen

void callback_begin(pid_t pid)
{
  unsigned addr = 0x8048616;
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
  char teub[30];

  regs_read(pid, &regs);

  fprintf(stderr, "\n");

  for (unsigned i = 0; i < 24; i++)
  {
    teub[i] = mem_read_char(pid, regs.edi + i);
  }

  fprintf(stderr, "%s", &teub);
  fprintf(stderr, "\n");
  fprintf(stderr, "\n");
}
