#include <iostream>
#include <string.h>

#define MAXLEN 20
int main()
{
	int m,n,i,res = 0;
	char *A = new char [MAXLEN];
	char *B = new char [MAXLEN];
	std::cin>>A>>B;
	m = strlen(A);
	n = strlen(B);
	if(m != n)
		res =  1;
	else
	{
		for(i = 0;i < m;i++)
		{
			if(A[i] != B[i])
			{
				if(A[i] - 'a' == B[i] - 'A' || A[i] - 'A' == B[i] - 'a')
					res = 3;
				else
				{
					res = 4;
					break;
				}
			}
		}
		if(res == 0)
			res = 2;
	}
	std::cout<<res<<std::endl;
	return 0;
}

