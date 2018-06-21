#include "../../Include/SeqList.hpp"

//s,begin pos,m,interval,n,total num.
void Josephus(int a[],int s,int m,int n)
{
	int pos,num;
	int i,j;
	pos = (s + n - 1) %n;
	num = n;
	for(i = 1;i <= n;i++)
		a[i - 1] = i;
	while(num > 0)
	{
		for(i = 1; i < m;++i)//because after the num minus one,pos automatically turn to the next one,so the count plus one equals the interval.
			pos = (pos + 1) % num;
		std::cout<<a[pos]<<" ";
		for(j = pos;j < num - 1;j++)
			a[j] = a[j + 1];
		num--;
	}
	std::cout<<std::endl;
}

/* int main() */
// {
	// int s = 1,m = 5,n = 9;
	// int *a = new int[n];
	// Josephus(a,s,m,n);
	// delete [] a;
/* } */
