#include <iostream>

void combinate(int A[],int m,int n,int r)
{
	int i,j;
	for(i = m;i >=n;i--)
	{
		A[n-1] = i;
		if(n > 1)
			combinate(A,i-1,n-1,r);
		else
		{
			for(j = r -1;j >= 0;j--)
				std::cout<<A[j];
			std::cout<<std::endl;
		}
	}
}
int main()
{
	int A[5];
	for(int i = 1;i<6;i++)
		A[i - 1] = i;
	combinate(A,5,3,3);
}
