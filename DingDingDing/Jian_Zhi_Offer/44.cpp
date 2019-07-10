#include <iostream>

int printnth(int n)
{
	std::string str;
	for(int i = 0;i <= n;i++)
		str += std::to_string(i);
	std::cout<<str<<std::endl;
	while(std::cin>>n)
		std::cout<<str[n]<<std::endl;
	return 0;	
}

int findnth(int n)
{
	if(n < 0)
		return -1;
	n--;
	int num,bit;
	int digitscount;
	int digits = 1;
	int round = 1;
	digitscount = digits * 9 * round;
	while(n > digitscount)
	{
		n -= digitscount;
		round *= 10;
		digits++;
		digitscount = digits * 9 * round;
	}
	num = round + n / digits;
	bit = digits - n % digits - 1;
	while(bit--)
		num /= 10;
	num %= 10;
	return num;	
}

int main()
{
	int n;
	std::cin>>n;
	// std::cout<<printnth(n)<<std::endl;
	std::cout<<findnth(n)<<std::endl;
	return 0;
}
