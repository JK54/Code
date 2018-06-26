#include <iostream>
#include <math.h>
int main()
{
	int result,count;
	std::string tmp;
	std::string::iterator p;
	count = 0;
	std::cin>>tmp;
	for(p = tmp.begin(); p != tmp.end(); p++)
	{
		if(*p == 'C' || *p == 'G')
			count++;
	}
	result = ceil(100 * static_cast<double>(count)/static_cast<double>(tmp.length()));
	std::cout<<result<<std::endl;
	return 0;
}
