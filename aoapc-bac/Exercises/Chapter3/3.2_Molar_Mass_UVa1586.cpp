#include <iostream>
#include <cstring>
#include <iomanip>

double amass(char a)
{
	if(a == 'C')
		return 12.01;
	else if(a == 'H')
		return 1.008;
	else if(a == 'O')
		return 16;
	else 
		return 14.01;
}

int main()
{
	int T,i,j,tmp;
	double *mass;
	char atom;
	std::string data;
	std::cin>>T;
	mass = new double [T];
	std::memset(mass,0,sizeof(double) * T);
	for(i = 0;i < T;i++)
	{
		std::cin>>data;
		for(j = 0,tmp = 1;data[j] != '\0';j++)
		{
			if(isalpha(data[j]))
			{
				atom = data[j];
				if(isalpha(data[j + 1]) || data[j + 1] == '\0')
					tmp = 1;
				else
					tmp = 0;
			}
			else
				tmp = tmp * 10 + data[j] - '0';
			if(isalpha(data[j + 1]) || data[j + 1] == '\0')
				mass[i] += amass(atom) * tmp;
		}
	}
	for(i = 0;i < T;i++)
		std::cout<<std::fixed<<std::setprecision(3)<<mass[i]<<std::endl;
	delete [] mass;
	return 0;
}
