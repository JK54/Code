#include <iostream>


int main()
{
	std::string str;
	int i,j,n[4];
	std::cin>>str;
	for(i = 3;i >= 0;i--)
		n[i] = str[3 - i] - '0';
	for(i = 0;i <= 1;i++)
	{
		n[i] = (n[i] + 5) % 10;
		n[3 - i] = (n[3 - i] + 5) % 10;
		std::swap(n[i],n[3 - i]);
	}
	if(n[3] == 0)
		j = 2;
	else
		j = 3;
	for(i = j;i >= 0;i--)
		std::cout<<n[i];
	std::cout<<std::endl;
	return 0;
}
