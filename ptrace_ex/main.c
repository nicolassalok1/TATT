#include "ptrace.h"


int main(int argc, char *argv[])
{
  pid_t pid;

  pid = fork();
  if (pid == -1)
    exit(1);
  if (pid != 0) /* papa */
  {
    debug_loop(pid);
    exit(0);
  }
  /* fiston */
  if (activate_debug() == -1)
  {
    perror("Cannot ptrace :");
    exit(2);
  }
  /* génère un SIGTRAP car le débogage est activé */
  execl("../OG/original", "../OG/original", "argv[1]", "test", NULL);
  exit(42);
}
