#include <iostream>
#include <cstring>

bool solutin(char *str,char *pattern)
{
	if(*str == '\0' && *pattern == '\0')
		return true;
	if((*str != '\0' && *pattern == '\0') || (*str == '\0' && *pattern != '\0'))
		return false;
	if(*(pattern + 1) == '*')
	{
		if(*pattern == *str || (*pattern == '.' && *str != '\0'))
		{
			return solutin(str + 1,pattern + 2) || solutin(str + 1,pattern) || solutin(str,pattern + 2);
		}
		else
			return solutin(str,pattern + 2);
	}
	else
	{
		if(*str == *pattern || (*pattern == '.' && *str != '\0'))
				return solutin(str + 1,pattern + 1);
		else
			return false;
	}
}

bool match(char *str,char *pattern)
{
	if(str == nullptr || pattern == nullptr)	
		return false;
	return solutin(str,pattern);
}

int main()
{
	char str[BUFSIZ],pattern[BUFSIZ];
	std::cin>>str>>pattern;
}
