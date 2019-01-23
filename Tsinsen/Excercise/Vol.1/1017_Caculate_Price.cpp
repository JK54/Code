#include <iostream>

#define BANANA 3
#define ORANGE 2
#define GRAPE 8
int main()
{
	int a,b,c;
	std::cin>>a>>b>>c;
	std::cout<<(a * BANANA + b * ORANGE + c * GRAPE)<<std::endl;
}
