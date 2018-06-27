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
			tmp = atoi(tmps.c_str());
			if(ts == '=')
			{
				if(flag == 1 || flag == 0)
					result += tmp;
				else if( flag == 2)
					result -= tmp;
				return result;
			}
			if(flag == 1 || flag == 0)
				result += tmp;
			else if( flag == 2)
				result -= tmp;
			if(ts == '+')
				flag = 1;
			else
				flag = 2;
			tmps = "";
		}
		is++;
	}
	return result;
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
