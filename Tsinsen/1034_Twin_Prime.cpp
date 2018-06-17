#include <iostream>

bool isprime(int n)
{
	for(int i = 2;i < n;i++)
		if(n % i == 0)
			return false;
	return true;
}

void twin(int left_bound,int right_bound)
{
	int i,tmpa,tmpb;
	bool cc;
	tmpa = tmpb = 0;
	for(i = left_bound;i <= right_bound;i++)
	{
		cc = isprime(i);
		if(cc)
			tmpa = tmpb,tmpb = i;
		if(cc && tmpb - tmpa == 2 && tmpa != 0)
			std::cout<<tmpa<<'\t'<<tmpb<<std::endl;
	}
	if(tmpa == 0 || tmpb == 0)
		std::cout<<-1<<std::endl;
}

int main()
{
	int a,b;
	std::cin>>a>>b;
	twin(a,b);
}


