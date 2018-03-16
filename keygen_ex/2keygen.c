#include<stdio.h>

int main ()
{
	int code1 = 0x83;
	int code2 = 0xc4;
	int code3 = 0x04;
	int code4 = 0xeb;
	int code5 = 0x70;


	int fd = fopen ("OG/crackme", "r+");
	
	int fs = fseek(fd, 1540, SEEK_SET);

	fwrite(&code1, 1, 1, fd);
	fwrite(&code2, 1, 1, fd);
	fwrite(&code3, 1, 1, fd);
	fwrite(&code4, 1, 1, fd);
	fwrite(&code5, 1, 1, fd);
	fclose (fd);
}
