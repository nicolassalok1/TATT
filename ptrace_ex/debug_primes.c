#include "ptrace.h"

/****************** primitives de debug **************/

long activate_debug(void)
{
  //FIXME: appel � ptrace pour indiquer qu'on veut se faire d�boguer
  return ptrace (PTRACE_TRACEME, 0, NULL, NULL);
}

long cont_signal(pid_t pid, int signal)
{
  //FIXME: appel � ptrace pour continuer l'ex�cution du fils
  return ptrace  (PTRACE_CONT, pid, NULL, signal);
}

long mem_read(pid_t pid, unsigned addr)
{
  //FIXME: appel � ptrace pour lire un long dans la m�moire du fils
  return ptrace  (PTRACE_PEEKDATA, pid, addr, NULL);
  /*if (word == -1)
    if (errno)
      fail ();*/
}

long singlestep(pid_t pid)
{
  //FIXME: appel � ptrace pour ex�cuter une seule instruction du fils
  return ptrace  (PTRACE_SINGLESTEP, pid, NULL, NULL);
}

long mem_write(pid_t pid, unsigned addr, long val)
{
  //FIXME: appel � ptrace pour �crire un long dans la m�moire du fils
  return ptrace  (PTRACE_POKEDATA, pid, addr, val);
}

long regs_read(pid_t pid, struct user_regs_struct *regs)
{
  memset(regs, 0, sizeof (struct user_regs_struct));
  //FIXME: appel � ptrace pour r�cup�rer les registres du fils
  return ptrace  (PTRACE_GETREGS, pid, NULL, regs);
}

long regs_write(pid_t pid, struct user_regs_struct *regs)
{
  //FIXME: appel � ptrace pour remplacer les registres du fils
  return ptrace  (PTRACE_SETREGS, pid, NULL, regs);
}
