#include <iostream>
#include <cstring>

char mirr(char a)
{
	char ref[] = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
	if(isdigit(a))
		return ref[a - '0' + 25];
	else
		return ref[a - 'A'];
}

void judge()
{
	std::string data;
	std::string::iterator travb,trave;
	int p,m;
	p = m = 1;
	std::cin>>data;
	travb = data.begin();
	trave = data.end() - 1;
	while(travb != data.end() && travb != trave && (m == 1 || p == 1))
	{
		if(*travb != *trave)
			p = 0;
		if(mirr(*travb) != *trave)
			m = 0;
		travb++;
		trave--;
	}
	if(p == 0 && m == 1)
		std::cout<<"mirror string"<<std::endl;
	else if(p == 1 && m == 0)
		std::cout<<"palindrome string"<<std::endl;	
	else if(p == 0 && m == 0)
		std::cout<<"regular string"<<std::endl;
	else
		std::cout<<"mirror palindrome string"<<std::endl;
}

int main()
{
	judge();
	return 0;
}
