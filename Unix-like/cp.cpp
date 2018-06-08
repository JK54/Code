#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#define BUFFERSIZE 4096
#define COPYMODE 0644
int main(int argc,char **argv)
{
	int in_fd,out_fd,n_chars;
	char buf[BUFFERSIZE];
	if(argc < 3)
	{
		std::cout<<"Usage: source destination"<<std::endl;
		exit(1);
	}
	// while()
	// {
		if((in_fd = open(argv[1],O_RDONLY)) == -1)
		{
			std::cout<<"cannot open"<<argv[1]<<std::endl;
			exit(1);
		}
		if((out_fd = creat(argv[2],COPYMODE)) == -1)
		{
			std::cout<<"cannot write"<<argv[2]<<std::endl;
			exit(1);
		}
		while((n_chars = read(in_fd,buf,BUFFERSIZE)) > 0)
			if(write(out_fd,buf,n_chars) != n_chars)
			{
				std::cout<<"error when writing"<<std::endl;
				exit(1);
			}
		if(n_chars == -1)
		{
			std::cout<<"error when reading"<<std::endl;
			exit(1);
		}
	if(close(in_fd) == -1 || close(out_fd) == -1)
	{
		std::cout<<"error when closing "<<std::endl;
		exit(1);
	}
}
