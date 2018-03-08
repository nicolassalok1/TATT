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

/****************** primitives de debug **************/
long activate_debug(void)
{
	//FIXME: appel à ptrace pour indiquer qu’on veut se faire déboguer
}

long cont_signal(pid_t pid, int signal)
{
	//FIXME: appel à ptrace pour continuer l’exécution du fils
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




/***************** gestion des breakpoints **************/


struct bp bps[BPS_MAX];
int nb_bps = 0;



int bp_set(pid_t pid, unsigned addr)
{
	if (nb_bps >= BPS_MAX)
		return 0;
	/*
	FIXME: récupérer la valeur initiale, ajouter dans la liste des
	breakpoints, écrire un ’int 3’ à l’adresse et afficher sur
	stderr un message contenant le numéro du breakpoint, l’adresse et la
	valeur originale : ’bp #%d : [%08x]=0x%02x’
	*/
	return 1;
	}

int bp_disable(pid_t pid, unsigned addr)
{
	/*
	FIXME: retrouver le breakpoint correspondant à l’adresse donnée,
	lire l’octet et vérifier la présence d’un ’int 3’, restaurer la
	valeur initiale puis afficher sur stderr la nouvelle valeur lue dans
	la mémoire : ’disable bp #%d : [%08x] 0x%02x -> 0x%02x’
	*/
	return 1;
}

int bp_enable(pid_t pid, unsigned addr)

{
	/*
	FIXME: retrouver le breakpoint correspondant à l’adresse donnée,
	lire l’octet et vérifier qu’il correspond à la valeur initiale,
	écrire un ’int 3’ puis afficher sur stderr la nouvelle valeur lue dans
	la mémoire : ’enable bp #%d : [%08x] 0x%02x -> 0x%02x’
	*/
	return 1;
}


/**************** callbacks bas niveau ********************/
void callback_breakpoint(pid_t pid, unsigned addr);
void callback_begin(pid_t pid);
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
		FIXME: décrémenter EIP qui pointe vers l’instruction suivante (le ’int 3’
		a été exécuté) et afficher sur stderr le message ’sigtrap @%x’
		*/
		// on appelle le callback programme
		callback_breakpoint(pid, addr);
		/*
		FIXME: désactiver le breakpoint, effectuer un singlestep du fils,
		utiliser ’waitpid’ pour récupérer le signal SIGTRAP et réactiver le
		breakpoint
		*/
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

/**************** callbacks programme ******************/
// A partir d’ici, le code à remplir est spécifique au keygen
void callback_begin(pid_t pid)
{
/*
FIXME: code exécuté au début du débogage : placer un breakpoint à la
bonne adresse, grâce à bp_set, pour pouvoir lire le serial dans la
mémoire au moment du breakpoint
*/

}
void callback_breakpoint(pid_t pid, unsigned addr)

{
/*
FIXME: code exécuté au breakpoint : vérifier l’adresse du
breakpoint, lire les registres et dans la mémoire pour récupérer et
afficher le serial sur stderr
*/

}
/****************** programme *****************/

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
	execl("./crackme", "./crackme", argv[1], "test", NULL);
	exit(42);

}
