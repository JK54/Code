#include <iostream>
#include <cstring>

int main()
{
	char a1[] = "101110010";
	char a2[] = "111100001";
	int size = strlen(a1) + 2;
	char res[size];
	char carry = '0';

	std::memset(res,'\0',size);
	for(int i = size - 3;i >= 0;i--)
	{
		if(a1[i] == '0')
		{
			if(a2[i] == '0')
			{
				if(carry == '0')
					res[i + 1] = '0';
				else if(carry == '1')
				{
					res[i + 1] = '1';
					carry = '0';
				}
			}
			else if(a2[i] == '1')
			{
				if(carry == '0')
					res[i + 1] = '1';
				else if(carry == '1')
					res[i + 1] = '0';
			}
		}
		else if(a1[i] == '1')
		{
			if(a2[i] == '0')
			{
				if(carry == '0')
					res[i + 1] = '1';
				else if(carry == '1')
					res[i + 1] = '0';
			}
			else if(a2[i] == '1')
			{
				if(carry == '0')
				{
					res[i + 1] = '0';
					carry = '1';
				}
				else if(carry == '1')
					res[i + 1] = '1';
			}
		}
		std::cout<<a1[i]<<" + " <<a2[i]<<"\t"<<" = "<<res[i + 1]<<'\t'<<" : "<<carry<<std::endl;
	}
	res[0] = carry;
	std::cout<<a1<<std::endl;
	std::cout<<a2<<std::endl<<std::endl;
	std::cout<<res<<std::endl;
}
