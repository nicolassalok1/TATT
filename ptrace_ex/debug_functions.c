#include "ptrace.h"

/****************** fonctions de debug **************/

long cont(pid_t pid)
{
  return (cont_signal(pid, 0));
}

long mem_write_char(pid_t pid, unsigned addr, unsigned char c)
{
  long data;

  data = mem_read(pid, addr);
  data = (data & 0xffffff00) | c;  // endianness
  return (mem_write(pid, addr, data));
}

unsigned char mem_read_char(pid_t pid, unsigned addr)
{
  return (mem_read(pid, addr) % 0x100);  // endianness
}

void mem_print_chars(pid_t pid, unsigned addr)
{
  unsigned data;

  data = mem_read(pid, addr);
  fprintf(stderr, "@%8x : %02x %02x %02x %02x\n", addr,
                data % 0x100, (data >> 8) % 0x100,
                (data >> 16) % 0x100, (data >> 24) % 0x100);
}

void regs_dump(pid_t pid)
{
  struct user_regs_struct regs;

  if (regs_read(pid, &regs) == -1)
    fprintf(stderr, "Erreur regs_read !\n");
  fprintf(stderr, "eax=%08x ebx=%08x ecx=%08x edx=%08x\n",
                  regs.eax, regs.ebx, regs.ecx, regs.edx);
  fprintf(stderr, "esi=%08x edi=%08x\n", regs.esi, regs.edi);
  fprintf(stderr, "eip=%08x esp=%08x ebp=%08x\n",
                  regs.eip, regs.esp, regs.ebp);
}
