#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <stdlib.h>

#define DEFAULT_SIZE 64
#define UTMP_SIZE sizeof(struct utmp)
int main()
{
	int fd;
	struct utmp utbuf[DEFAULT_SIZE];
	struct utmp utuser;
	int count,num_read,rcount;
	double total = 0;
	if((fd = open(WTMP_FILE,O_RDONLY)) == -1)
	{
		perror("Can't open wtmp file");
		exit(1);
	}
	while(((num_read = read(fd,utbuf,UTMP_SIZE*DEFAULT_SIZE)/UTMP_SIZE) != 0))
	{
		count = 0;
		while(count < num_read)
		{
			rcount = count;
			if(utbuf[count].ut_type == USER_PROCESS)
			{
				utuser = utbuf[count];
				rcount++;
				//the logic need to reconsider,but the basic idea is right
				while(utbuf[rcount].ut_type != DEAD_PROCESS && utbuf[rcount].ut_user != utuser.ut_user && rcount < num_read)
					rcount++;
				total += (utuser.ut_tv.tv_sec - utbuf[rcount].ut_tv.tv_sec)/3600;
			}
			count++;
		}
	}
	close(fd);
	printf("\ttotal\t%-f\n",total);
}
