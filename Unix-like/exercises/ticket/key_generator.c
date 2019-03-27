#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#define KEYLEN 23

int main(int argc,char **argv)
{
	FILE *rd = fopen("/dev/random","r");
	FILE *wd = fopen("./licenses.dat","w+");
	char tmp[KEYLEN + 1];
	int buf;
	/* int num = atoi(argv[1]); */
	int num = 5;
	tmp[KEYLEN] = '\0';
	for(int i = 0;i < num;i++)
	{
		for(int j = 0; j < KEYLEN;j++)
		{
			if( (j + 1) % 6 == 0)
				tmp[j] = '-';
			else
			{
				buf = getc(rd);
				while(!((buf >= 'a' && buf <= 'z') || (buf >= 'A' && buf <= 'Z') || (buf >= '0' && buf <= '9')))
					buf = getc(rd);
				if(buf >= 'a' && buf <= 'z')
					tmp[j] = toupper(buf);
				else
					tmp[j] = buf;
			}
		}
		fwrite(tmp,sizeof(char),KEYLEN,wd);
		fputc('\n',wd);
	}
	fclose(rd);
	fclose(wd);
}
