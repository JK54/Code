#include <iostream>
#include <math.h>

#define SHRINKING_AREA 50
#define PI 3.1415926
int main()
{
	int i,n;
	double *x,*y,tmp;
	int *years;
	std::cin>>n;
	x = new double[n];
	y = new double[n];
	years = new int[n];
	for(i = 0;i < n;i++)
	{
		std::cin>>x[i]>>y[i];
		tmp = PI * (pow(x[i],2) + pow(y[i],2))/(SHRINKING_AREA * 2);
		if(int(tmp) < tmp)
			tmp = ceil(tmp);
		else
			tmp += 1;
		years[i] = tmp;
	}
	for(i = 0;i < n;i++)
		std::cout<<years[i]<<std::endl;
	delete [] years;
	return 0;
}
