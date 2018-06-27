#include <iostream>
#include <math.h>

void twin(long long int left_bound,long long int right_bound)
{
	long long int i,j,tmp;
	bool cc,cp;
	tmp = 0;
	cp = false;
	for(i = left_bound > 2 ? left_bound : 3;i <= right_bound;i++)
	{
		if(i % 2 == 0)
			continue;
		cc= true;
		for(j = 2;j < sqrt(i) + 1;j++)
			if(i % j == 0)
			{
				cc =  false;
				break;
			}
		if(cc)
		{
			if(i - tmp == 2)
			{
				std::cout<<tmp<<" "<<i<<std::endl;
				cp = true;
			}
			tmp = i;
		}
	}
	if(!cp)
		std::cout<<-1<<std::endl;
}

int main()
{
	long long int a,b;
	std::cin>>a>>b;
	twin(a,b);
	return 0;
}


