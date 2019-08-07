// #include "square.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <iomanip>

double square_root_newton(double a)
{
	double preresult,result = 1,deviation;
	int count = 0;
	do
	{
		preresult = result;
		result = (result + a / result) / 2;
		count++;
		deviation = fabs(result - preresult);
	}while(deviation > 0.0000001);
	std::cout<<count<<std::endl;
	return result;
}

//https://blog.csdn.net/xusiwei1236/article/details/25657611
//放到这里是因为不知道博主为什么说初始上界需要加0.25
double Sqrt(double A)
{
	double x0 = A + 0.25, x1, xx = x0;
	double DBL_EPSILON = 0.0000001;
	int count = 0;
	for(;;) 
	{
		count++;
		x1 = (x0*x0 + A) / (2*x0);
		if(fabs(x1 - x0) <= DBL_EPSILON) break;
		if(xx == x1) break; // to break two value cycle.
		xx = x0;
		x0 = x1;
	}
	std::cout<<count<<std::endl;
	return x1;
}

double square_root_binary(double a)
{
	double left = 0,right = a,mid,deviation;
	int count = 0;
	double DBL_EPSILON = 0.0000001;
	do
	{
		count++;
		mid = (left + right) / 2;
		deviation = mid * mid - a;
		if(deviation > 0)
			right = mid;
		else
			left = mid;
	}while(right -  left > DBL_EPSILON);
	std::cout<<count<<std::endl;
	return mid;
}

float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;
 
	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
	 y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
	  
		  return y;
}

double square(double a)
{
	return a * a;
}

double Secant_General(double f(double),double y)
{
	double x0,x1,x2,f0,f1,deviation;
	const double PRECISION = 0.0000001;
	x0 = 0,f0 = f(x0) - y;
	x1 = ((static_cast<long long >(y)) >> 1),f1 = f(x1) - y;
	int count = 0;
	do
	{
		count++;
		x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
		x0 = x1,f0 = f1;
		x1 = x2,f1 = f(x2) - y;
		double tmp = x1 - x0;
		deviation = tmp > 0 ? tmp : -1 * tmp;
	}while(deviation > PRECISION);
	std::cout<<count<<std::endl;
	return x1;
}

int main(int argc,char **argv)
{
	if(argc != 2)
		return 1;
	double a = atof(argv[1]);
	std::cout<<std::setprecision(6)<<square_root_newton(a)<<std::endl;
	std::cout<<std::endl;
	std::cout<<std::setprecision(6)<<square_root_binary(a)<<std::endl;
	std::cout<<std::endl;
	std::cout<<std::setprecision(6)<<Secant_General(square,a)<<std::endl;
	std::cout<<std::endl;
	std::cout<<std::setprecision(6)<<sqrt(a)<<std::endl;
}
