#include <iostream>
#include <fstream>
#define PAGLINE 24

void do_more(std::ifstream &is);
int see_more();

void do_more(std::ifstream &is)
{
	std::string line;
	int act;
	for(int i = 0; i < PAGLINE && std::getline(is,line);++i)
		std::cout<<line<<std::endl;
	while(std::getline(is,line))
	{
		std::cout<<line<<std::endl;
		act = see_more();
		if(act == 0)
			break;
		if(act == 1)
			continue;
		if(act == 2)
			for(int i = 0; i < PAGLINE && std::getline(is,line);++i)
				std::cout<<line<<std::endl;
	}
}

int see_more()
{
	int in;
	std::cout<<"\033[7m more? \033[m";
	while((in = getchar()))
	{
		if(in == 'q')
			return 0;
		if(in == '\n')
			return 1;
		if(in == 'n')
			return 2;
	}
	return 0;
}

int main(int argc, char * argv[])
{
	if(argc == 1)
	{
		std::cout<<"no file.."<<std::endl;
		exit(1);
	}
	else
	{
		while(argc > 1)
		{
			std::ifstream is(*(++argv));
			do_more(is);
			argc--;
		}
	}
}
