#include<stdio.h>

int main ()
{
	int code = 0x90;

	int fd = fopen ("./crackme", "r+");

	int fs = fseek(fd, 1613, SEEK_SET);

	fwrite(&code, 1, 1, fd);
	fwrite(&code, 1, 1, fd);
	fwrite(&code, 1, 1, fd);
	fwrite(&code, 1, 1, fd);
	fclose (fd);
}
