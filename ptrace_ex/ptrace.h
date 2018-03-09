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

#endif 

