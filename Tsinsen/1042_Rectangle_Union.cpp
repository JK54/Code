#include <iostream>
#include <iomanip>

bool isamong(double a,double b,double c)
{
	return (a < b) && (b < c);
}
double calunion(double *data)
{

	double result;
	if((isamong(data[4],data[0],data[6]) || isamong(data[4],data[1],data[6])) && (isamong(data[5],data[1],data[7]) || isamong(data[5],data[3],data[7])))
	{
	
	}
	else
		result = 0;
}

int main()
{
	int i;
	double data[8];
	for(i = 0;i < 7;i += 2)
		std::cin>>data[i]>>data[i + 1];
	std::cout<<std::setprecision(2)<<calunion(data)<<std::endl;
	return 0;
}
