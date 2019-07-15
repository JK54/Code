#include <iostream>
#include <cstring>

void reverseword(char *wd,int left,int right)
{
	if(left >= right)
		return;
	for(int i = left,j = right;i < j;i++,j--)
		std::swap(wd[i],wd[j]);
}

void reversestring(char *str)
{
	if(str == nullptr)
		return;
	std::cout<<str<<std::endl;
	int len = strlen(str);
	for(int i = 0,j = len - 1;i < j;i++,j--)
		std::swap(str[i],str[j]);
	std::cout<<str<<std::endl;
	for(int wordbegin = 0;wordbegin < len;)
	{
		int wordend = wordbegin;
		while(str[wordend] != '\0' && str[wordend] != ' ')
		{
			if(str[wordend] == '.' && str[wordend + 1] != '\0' && isalpha(str[wordend + 1]))
				break;
			wordend++;
		}
		reverseword(str,wordbegin,wordend - 1);
		wordbegin = wordend + 1;
	}
	std::cout<<str<<std::endl;
}

int main()
{
	char str[] = "I am the bone of my sword.Unknown to Death.Nor Unknownn to life.Unlimited Blade Works.";
	reversestring(str);
}
