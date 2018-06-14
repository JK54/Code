#include <iostream>

#define HOUR 3600
#define MINUTE 60
int main()
{
	int sec;
	std::cin>>sec;
	std::cout<<(sec /HOUR) <<":"<<(sec % HOUR /MINUTE)<<":"<<(sec %MINUTE)<<std::endl;
}
