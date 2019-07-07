#include <iostream>

bool scanunsigned(char **str)
{
	const char *mark = *str;
	while(**str != '\0' && **str >= '0' && **str <= '9')
		(*str)++;
	return *str != mark;	
}

bool scansigned(char **str)
{
	if(**str == '+' || **str == '-')
		++(*str);
	return scanunsigned(str);
}

bool isnum(char *str)
{
	if(str == nullptr)
		return false;
	bool numric = scansigned(&str);
	if(*str == '.')
	{
		++str;
		//小数点后面可以没有数字
		numric = scanunsigned(&str) || numric;
	}
	if(*str == 'e' || *str == 'E')
	{
		++str;
		//e前面必须有数字
		numric = scansigned(&str) && numric;
	}
	return numric && *str == '\0';
}

int main()
{
	char str[BUFSIZ];
	std::cin>>str;
	std::cout<<isnum(str)<<std::endl;
}
