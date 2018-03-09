#include "ptrace.h"

/***************** gestion des breakpoints **************/

int nb_bps = 0;

int bp_set(pid_t pid, unsigned addr)
{
  if (nb_bps >= BPS_MAX)
    return 0;

  /*
    FIXME: récupérer la valeur initiale, ajouter dans la liste des
    breakpoints, écrire un 'int 3' à l'adresse et afficher sur
    stderr un message contenant le numéro du breakpoint, l'adresse et la
    valeur originale : 'bp #%d : [%08x]=0x%02x'
  */
        
  return 1;
}

int bp_disable(pid_t pid, unsigned addr)
{
  /*
    FIXME: retrouver le breakpoint correspondant à l'adresse donnée,
    lire l'octet et vérifier la présence d'un 'int 3', restaurer la
    valeur initiale puis afficher sur stderr la nouvelle valeur lue dans
    la mémoire : 'disable bp #%d : [%08x] 0x%02x -> 0x%02x'
  */

  return 1;
}

int bp_enable(pid_t pid, unsigned addr)
{
  /*
    FIXME: retrouver le breakpoint correspondant à l'adresse donnée,
    lire l'octet et vérifier qu'il correspond à la valeur initiale,
    écrire un 'int 3' puis afficher sur stderr la nouvelle valeur lue dans
    la mémoire : 'enable bp #%d : [%08x] 0x%02x -> 0x%02x'
  */

  return 1;
}
