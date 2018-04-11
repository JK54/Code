#include <iostream>

#define PAGLEN 24
#define LINELEN 512
int see_more(FILE *);
void do_more(FILE *);
int main(int ac,char *av[])
{
	FILE *fp;
	if(ac == 1)
		do_more(stdin);
	else
		while(--ac)
			if((fp = fopen(*++av,"r")) != nullptr)
			{
				do_more(fp);
				fclose(fp);
			}
			else
				exit(1);
	return 0;
}

void do_more(FILE *fp)
{
	char line[LINELEN];
	int num_of_line = 0;
	FILE *fp_tty;
	int reply;
	fp_tty = fopen("/dev/tty","r");
	if(fp_tty == nullptr)
		exit(1);
	while(fgets(line,LINELEN,fp))
	{
		if(num_of_line == PAGLEN)
		{
			reply = see_more(fp_tty);
			if(reply == 0)
				break;
			num_of_line -= reply;
		}
		if(fputs(line,stdout) == EOF)
			exit(1);
		num_of_line++;
	}
}

int see_more(FILE *cmd)
{
	int c;
	std::cout<<"\033[7m more? \033[m";
	while((c = getc(cmd)) != EOF)
	{
		if( c == 'q')
			return 0;
		if( c == ' ')
			return PAGLEN;
		if( c == '\n')
			return 1;
	}
	return 0;
}
