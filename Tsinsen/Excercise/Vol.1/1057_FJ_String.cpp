#include <iostream>

void strrr(int n,std::string &str)
{
	str = "A";
	for(int i = 1;i < n;i++)
		str = str + static_cast<char>('A' + i) + str;
}

int main()
{
	int n;
	std::string str;
	std::cin>>n;
	strrr(n,str);
	std::cout<<str<<std::endl;
	return 0;
}
