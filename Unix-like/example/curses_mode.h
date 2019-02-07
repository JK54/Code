#include <sys/time.h>
#include <stdio.h>

int set_ticker(int n_msecs)
{
	struct itimerval new_timeset;
	long n_sec,n_uses;
	n_sec = n_msecs / 1000;
	n_uses = (n_msecs % 1000) * 1000;
	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_uses;
	new_timeset.it_value.tv_sec = n_sec;
	new_timeset.it_value.tv_usec = n_uses;
	return setitimer(ITIMER_REAL,&new_timeset,NULL);
}

