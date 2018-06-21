#include <iostream>
#include <sstream>
#include <stdlib.h>

int add(std::string str)
{
	int result,tmp,flag;
	std::string tmps;
	char ts;
	std::string::iterator is = str.begin();
	result = flag = 0;
	while(is != str.end())
	{
		ts = *is;
		if(ts != '+' && ts != '-' && ts != '=')
			tmps += ts;
		else
		{
			if(ts == '=')
			{
				if(flag == 1)
					result += tmp;
				else if( flag == 2)
					result -= tmp;
				return result;
			}
			tmp = atoi(tmps.c_str());
			if(flag == 1)
				result += tmp;
			else if( flag == 2)
				result -= tmp;
			if(ts == '+')
			{
				flag = 1;
				tmps = "";
			}
			else
			{
				flag = 2;
				tmps = "";
			}
		}
		is++;
	}
	exit(1);
}
int main()
{
	std::string str;
	int result;
	std::cin>>str;
	if(str[str.length() - 1] != '=')
	{
		perror("ended with '=' !");
		return 1;
	}
	result = add(str);
	std::cout<<result<<std::endl;
	return 0;
}
