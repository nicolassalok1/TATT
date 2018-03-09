#include "ptrace.h"

/****************** primitives de debug **************/

long activate_debug(void)
{
  //FIXME: appel à ptrace pour indiquer qu'on veut se faire déboguer
}

long cont_signal(pid_t pid, int signal)
{
  //FIXME: appel à ptrace pour continuer l'exécution du fils
}

long mem_read(pid_t pid, unsigned addr)
{
  //FIXME: appel à ptrace pour lire un long dans la mémoire du fils
}

long singlestep(pid_t pid)
{
  //FIXME: appel à ptrace pour exécuter une seule instruction du fils
}

long mem_write(pid_t pid, unsigned addr, long val)
{
  //FIXME: appel à ptrace pour écrire un long dans la mémoire du fils
}

long regs_read(pid_t pid, struct user_regs_struct *regs)
{
  memset(regs, 0, sizeof (struct user_regs_struct));
  //FIXME: appel à ptrace pour récupérer les registres du fils
}

long regs_write(pid_t pid, struct user_regs_struct *regs)
{
  //FIXME: appel à ptrace pour remplacer les registres du fils
}
