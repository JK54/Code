#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include "curses_mode.h"

#define MESSAGE "hello"
#define BLANK   "     "

int row = 10;
int col = 0;
int dir = 1;
int delay = 200;
int done = 0;

int main()
{
	void on_alarm(int);
	void on_input(int);
	void enable_kbd_signals();

	initscr();
	crmode();
	noecho();
	clear();

	signal(SIGIO,on_input);
	enable_kbd_signals();
	signal(SIGALRM,on_alarm);
	set_ticker(delay);
	
	move(row,col);
	addstr(MESSAGE);

	while(!done)
		pause();
	endwin();
	return 0;
}

void on_input(int signum)
{
	signal(SIGIO,on_input);
	int c = getchar();
	if(c == EOF || c == 'q')
	/* if(c == 'q') */
		done = 1;
	else if(c == ' ')
		dir *= -1;
}

void on_alarm(int signum)
{
	signal(SIGALRM,on_alarm);
	mvaddstr(row,col,BLANK);
	col += dir;
	mvaddstr(row,col,MESSAGE);
	refresh();

	if(dir == -1 && col <= 0)
		dir = 1;
	else if(dir == 1 && col >= COLS)
		dir = -1;
}

void enable_kbd_signals()
{
	int fd_flags;
	fcntl(0,F_SETOWN,getpid());
	fd_flags = fcntl(0,F_GETFL);
	fcntl(0,F_SETFL,(fd_flags | O_ASYNC));
}
