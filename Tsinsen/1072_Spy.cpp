#include <iostream>

#define SIZE 26

bool crack(char *table,std::string encrypted,std::string decrypted)
{
	int i = 0;
	int anti_tble[SIZE];
	std::string::iterator p,q;
	for(i = 0;i < SIZE;i++)
		anti_tble[i] = 0;
	for(i = 0,p = encrypted.begin(),q = decrypted.begin();p != encrypted.end();p++,q++)
	{
		if(table[*p - 'A'] =='\0')
		{
			table[*p - 'A'] = *q;
			i++;
			anti_tble[*q - 'A']++;
		}
		else
		{
			if(table[*p - 'A'] != *q)
			{
				std::cout<<"Failed"<<std::endl;
				return false;
			}
		}
	}
	if(i != SIZE)
	{
		std::cout<<"Failed"<<std::endl;
		return false;
	}
	for(i = 0;i < SIZE;i++)
	{
		if(anti_tble[i] > 1)
		{
			std::cout<<"Failed"<<std::endl;
			return false;
		}
	}
	return true;
}

int main()
{
	char table[SIZE];
	int i;
	std::string encrypted,decrypted,source;
	for(i = 0;i < SIZE;i++)
		table[i] = '\0';
	std::cin>>encrypted>>decrypted>>source;
	if(crack(table,encrypted,decrypted))
	{
		i = 0;
		while(source[i] != '\0')
		{
			std::cout<<table[source[i] - 'A'];
			i++;
		}
		std::cout<<std::endl;
	}
	return 0;
}
