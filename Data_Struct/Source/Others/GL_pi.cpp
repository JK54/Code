#include "include/sys_comm.h"

void super_pi(long double *a,long double *b,long double *t,long double *p,int N0)
{

	while(--N0 > 0)
	{
		std::cout<<"aaa"<<std::endl;
		long double tmpa = *a,tmpb = *b,tmpt = *t,tmpp = *p;
		*(a + 1) = (tmpa +tmpb)/2.0;
		*(b + 1) = sqrt(tmpa * tmpb);
		*(t + 1) = tmpt - tmpp*pow((tmpa - *(a + 1)),2);
		*(p + 1) = 2*tmpp;
		super_pi(a+1,b+1,t+1,p+1,N0);
	}
}

void print(long double a[],int N)
{
	for(auto i = 0; i< N ; ++i)
		std::cout<<std::setprecision(100)<<a[i]<<std::endl;
	std::cout<<std::endl;
}
int main()
{
	size_t N;
	std::cin>>N;
	long double *a = new long double [N];
	long double *b = new long double [N];
	long double *t = new long double [N];
	long double *p = new long double [N];
	a[0] = 1.0;
	b[0] = 1/sqrt(2);
	t[0] = 1/4.0;
	p[0] = 1.0;
	super_pi(a,b,t,p,N - 1);
	std::cout<<std::endl;
	print(a,N);
	print(b,N);
	print(t,N);
	print(p,N);
	long double pi = pow((a[N - 2] + b[N - 2]),2)/(4*t[N - 2]);
	std::cout<<std::setprecision(100)<<pi<<std::endl;
	delete [] a;
	delete [] b;
	delete [] t;
	delete [] p;
}
