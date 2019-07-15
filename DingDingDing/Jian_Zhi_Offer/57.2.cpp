#include <iostream>

void disp(int a,int b,int c)
{
	for(int i = a;i < b;i++)
		std::cout<<i<<" + ";
	std::cout<<b<<" = "<<c<<std::endl;
}

int findcontinouspositiveseq(int k)
{
	if(k < 3)
		return 0;
	int left,right,sum,count;
	left = 1,right = 2,count = 0;
	sum = left + right;
	while(left < ((1 + k) >> 1))
	{
		if(sum >= k)
		{
			if(sum == k)
			{
				count++;
				disp(left,right,k);		
			}
			sum -= left++;
		}
		else
			sum += ++right;
	}
	return count;
}

int main()
{
	int k;
	std::cin>>k;
	std::cout<<findcontinouspositiveseq(k)<<std::endl;
	return 0;
}
