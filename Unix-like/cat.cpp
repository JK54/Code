#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

int main(int argc,char ** argv)
{
	if(argc != 2)
	{
		perror("Usage:cat filename");
		exit(1);
	}
	std::ifstream inn(argv[1]);
	std::string str;
	while(std::getline(inn,str))
		std::cout<<str<<std::endl;
	return 0;
}
