#include <iostream>
#include <iomanip>

double calunion(double *data)
{
	double x,y,result;
	if(data[0] > data[2])
		std::swap(data[0],data[2]);
	if(data[1] > data[3])
		std::swap(data[1],data[3]);
	if(data[4] > data[6])
		std::swap(data[4],data[6]);
	if(data[5] > data[7])
		std::swap(data[5],data[7]);
	x = std::min(data[2],data[6]) - std::max(data[0],data[4]);
	x = x < 0 ? 0 : x;
	y = std::min(data[3],data[7]) - std::max(data[1],data[5]);
	y = y < 0 ? 0 : y;
	result = x * y;
	return result;
}

int main()
{
	int i;
	double data[8];
	for(i = 0;i < 7;i += 2)
		std::cin>>data[i]>>data[i + 1];
	std::cout<<std::fixed<<std::setprecision(2)<<calunion(data)<<std::endl;
	return 0;
}
