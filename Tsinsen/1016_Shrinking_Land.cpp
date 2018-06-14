#include <iostream>
#include <math.h>

#define SHRINKING_AREA 50
#define PI 3.14
int main()
{
	int i,n;
	double *x,*y;
	int *years;
	std::cin>>n;
	x = new double[n];
	y = new double[n];
	years = new int[n];
	for(i = 0;i < n;i++)
	{
		std::cin>>x[i]>>y[i];
		years[i] = ceil(PI * (pow(x[i],2) + pow(y[i],2))/(SHRINKING_AREA * 2));
	}
	for(i = 0;i < n;i++)
		std::cout<<years[i]<<std::endl;
	delete [] years;
	return 0;
}
