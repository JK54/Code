#include <iostream>
#include <cstring>

void disp(char *digits,int bits)
{
	int offset = -1;
	for(int i = 0;offset == -1 && i < bits;i++)
		if(digits[i] != '0')
			offset = i; 
	std::cout<<digits + offset<<std::endl;
}

bool inc(char *digits,int bits)
{
	bool isoverflow = false,finish = false;
	int carry= 1;
	int bit = bits - 1;
	while(!finish)
	{
		if(carry == 1)
		{
			if(digits[bit] == '9')
			{
				if(bit > 0)
				{
					digits[bit--] = '0';
					carry = 1;
				}
				else
				{
					finish = true;
					isoverflow = true;
				}
			}
			else
			{
				digits[bit] += 1;
				carry = 0;
			}
		}
		if(carry == 0)
			finish = true;
	}
	if(isoverflow)
		return false;
	return true;
}

void printnum(int bits)
{
	if(bits <= 0)
		return;
	char digits[bits + 1];
	memset(digits,'0',sizeof(char) * (bits));
	digits[bits] = '\0';
	while(inc(digits,bits))
		disp(digits,bits);
}

int main()
{
	int bits;
	std::cin>>bits;
	printnum(bits);
}
