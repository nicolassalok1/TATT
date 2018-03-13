#ifndef LOCAL
#define LOCAL


#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bp
{
  unsigned addr;
  char val;
};

#define BPS_MAX 100
struct bp bps[BPS_MAX];

void callback_breakpoint(pid_t pid, unsigned addr);
void callback_begin(pid_t pid);

void callback_sigtrap(pid_t pid);
void  callback_generic(pid_t pid, int signal);
void debug_loop(pid_t pid);
        
long activate_debug(void);
long cont_signal(pid_t pid, int signal);
long mem_read(pid_t pid, unsigned addr);
long singlestep(pid_t pid);
long mem_write(pid_t pid, unsigned addr, long val);
long regs_read(pid_t pid, struct user_regs_struct *regs);
long regs_write(pid_t pid, struct user_regs_struct *regs);

int bp_enable(pid_t pid, unsigned addr);
int bp_set(pid_t pid, unsigned addr);
int bp_disable(pid_t pid, unsigned addr);

void callback_breakpoint(pid_t pid, unsigned addr);
void callback_begin(pid_t pid);

void regs_dump(pid_t pid);
void mem_print_chars(pid_t pid, unsigned addr);
unsigned char mem_read_char(pid_t pid, unsigned addr);
long cont(pid_t pid);
long mem_write_char(pid_t pid, unsigned addr, unsigned char c);

#endif 

