#include "ptrace.h"

/**************** callbacks bas niveau ********************/

void callback_sigtrap(pid_t pid)
{
  static int first = 1;
  unsigned addr;

  if (first == 1)
  {
    // premier signal de debug, on appelle le callback programme
    callback_begin(pid);
    first = 0;
  }
  else
  {
    /*
      FIXME: décrémenter EIP qui pointe vers l'instruction suivante (le 'int 3'
      a été exécuté) et afficher sur stderr le message 'sigtrap @%x'
    */
    struct user_regs_struct regs;

    regs_read(pid, &regs);
    regs_dump(pid);

    addr = --regs.eip;

    regs_write(pid, &regs);
    //regs_dump(pid);

    fprintf(stderr, "sigtrap @%x\n", addr);

    // on appelle le callback programme
    callback_breakpoint(pid, addr);

    /*
      FIXME: désactiver le breakpoint, effectuer un singlestep du fils,
      utiliser 'waitpid' pour récupérer le signal SIGTRAP et réactiver le
      breakpoint
    */
    bp_disable(pid, addr);
    singlestep(pid);
    wait(&pid);
    bp_enable(pid, addr);
  }

  /* on continue */
  cont(pid);
}

void  callback_generic(pid_t pid, int signal)
{
  unsigned addr;
  struct user_regs_struct regs;

  regs_read(pid, &regs);
  addr = regs.eip;

  if (signal == SIGILL)
    printf("Illegal instruction @%x\n", addr);
  else if (signal == SIGSEGV)
    printf("Segmentation fault @%x\n", addr);
  else
    printf("signal %d @%x\n", signal, addr);
  mem_print_chars(pid, addr);
  regs_dump(pid);
  exit(1);
}

void debug_loop(pid_t pid)
{
  int status;
  int signal;

  while (1)
  {
    waitpid(pid, &status, 0);
    if (WIFSTOPPED(status))
    {
      /* signal ptrace */
      signal = WSTOPSIG(status);
      if (signal == SIGTRAP)
        callback_sigtrap(pid);
      else
        callback_generic(pid, signal);
    }
    else
    {
      fprintf(stderr, "Signal, exit !\n");
      break;
    }
  }
}
