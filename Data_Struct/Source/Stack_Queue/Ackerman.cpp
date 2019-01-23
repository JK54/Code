#include <iostream>

long double akm_nr(long double m,long double n)
{
	if( m == 0)
		return n + 1;
	else if( m != 0 && n == 0)
		return akm_nr(m-1,1);
	else
		return akm_nr(m-1,akm_nr(m,n-1));
}

long double akm(long double m ,long double n)
{
	long int i,j,top = -1;
	long double k;
	long double Sm[100000],Sn[100000];
	Sm[++top] = m;
	Sn[top] = n;
	while(1)
	{
		i = Sm[top];
		j = Sn[top];
		top--;
		if(i == 0)
		{
			k = j + 1;
			if(top != -1)
				Sn[top] = k;
			else
				return k;
		}
		else if( j == 0)
		{
			Sm[++top] = i - 1;
			Sn[top] = 1;
		}
		else
		{
			Sm[++top] = i - 1;
			Sm[++top] = i;
			Sn[top] = j - 1;
		}
	}
}
int main()
{
	long double m,n;
	while(std::cin>>m>>n)
		std::cout<<akm(m,n)<<std::endl;
}
