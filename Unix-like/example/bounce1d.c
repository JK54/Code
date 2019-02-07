#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#define MESSAGE "hello"
#define BLANK "       "

int row;
int col;
int dir;

int set_ticker(int n_msecs)
{
	struct itimerval new_timeset;
	long n_secs,n_usecs;
	n_secs = n_msecs / 1000;
	n_usecs = (n_msecs % 1000) * 1000L;
	new_timeset.it_value.tv_sec = n_secs;
	new_timeset.it_value.tv_usec = n_usecs;
	new_timeset.it_interval.tv_sec = n_secs;
	new_timeset.it_interval.tv_usec = n_usecs;
	return setitimer(ITIMER_REAL,&new_timeset,NULL);
}

void move_msg(int signum)
{
	signal(SIGALRM,move_msg);
	move(row,col);
	addstr(BLANK);
	col += dir;
	move(row,col);
	addstr(MESSAGE);
	refresh();

	if(dir == -1 && col <= 0)
		dir = 1;
	else if(dir == 1 && col + strlen(MESSAGE) >= COLS)
		dir = -1;
}

int main()
{
	int delay;
	int ndelay;
	int c;
	
	initscr();
	crmode();
	noecho();
	clear();

	row = 10;
	col = 0;
	dir = 1;
	delay = 1000;
	
	move(row,col);
	addstr(MESSAGE);
	signal(SIGALRM,move_msg);
	set_ticker(delay);

	while(1)
	{
		ndelay = 0;
		c = getch();
		if(c == 'Q' || c == 'q') 
			break;
		else if(c == ' ')
			dir *= -1;
		else if(c == 'f' && delay > 2)
			ndelay = delay / 2;
		else if(c == 's')
			ndelay = delay * 2;

		if(ndelay > 0)
			set_ticker(delay = ndelay);
	}
	endwin();
	return 0;
}
