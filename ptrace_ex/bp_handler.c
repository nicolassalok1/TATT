#include "ptrace.h"

/***************** gestion des breakpoints **************/

int nb_bps = 0;
const unsigned int3 = 0xcc;

int bp_set(pid_t pid, unsigned addr)
{
  if (nb_bps >= BPS_MAX)
    return 1;

  struct bp new_bp;
  new_bp.addr = addr;
  new_bp.val = mem_read(pid, addr);

  bps[nb_bps] = new_bp;

  mem_write(pid, addr, int3);
  nb_bps++;

  printf("bp #%d : [%08x]=0x%02x\n", 
            nb_bps, addr,  int3);

  return 0;

  /*
    FIXME: récupérer la valeur initiale, ajouter dans la liste des
    breakpoints, écrire un 'int 3' à l'adresse et afficher sur
    stderr un message contenant le numéro du breakpoint, l'adresse et la
    valeur originale : 'bp #%d : [%08x]=0x%02x'
  */
}

int bp_disable(pid_t pid, unsigned addr)
{
  for(int i = 0; i <= nb_bps; i++)
  {
    if (bps[i].addr == addr)
    {
      mem_write(pid, addr, bps[i].val);
      printf("disable bp #%d : [%08x] 0x%02x -> 0x%02x\n", 
                i, bps[i].addr, int3, bps[i].val);
      return 0;
    }
    return 1;
  }
  
  /*
    FIXME: retrouver le breakpoint correspondant à l'adresse donnée,
    lire l'octet et vérifier la présence d'un 'int 3', restaurer la
    valeur initiale puis afficher sur stderr la nouvelle valeur lue dans
    la mémoire : 'disable bp #%d : [%08x] 0x%02x -> 0x%02x'
  */
}

int bp_enable(pid_t pid, unsigned addr)
{
  for(int i = 0; i <= nb_bps; i++)
  {
    if (bps[i].addr == addr)
    {
      mem_write(pid, addr, int3);
      printf("enable bp #%d : [%08x] 0x%02x -> 0x%02x\n", 
                i, bps[i].addr, bps[i].val, int3);
      return 0;
    }
    return 1;
  }
  /*
    FIXME: retrouver le breakpoint correspondant à l'adresse donnée,
    lire l'octet et vérifier qu'il correspond à la valeur initiale,
    écrire un 'int 3' puis afficher sur stderr la nouvelle valeur lue dans
    la mémoire : 'enable bp #%d : [%08x] 0x%02x -> 0x%02x'
  */

}
