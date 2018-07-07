#include <iostream>
#include <string.h>

std::string cow(std::string *data,int n,std::string checked)
{
	int i;
	std::string next = checked;
	for(i = 0;i < n;i++)
	{
		if((data[i] > checked && data[i] < next) || (next == checked && next < data[i] ))
			next = data[i];
	}
	if(next == checked)
		return "The End";
	return next;
}

int main()
{
	int n,i;
	std::string checked,next,*data;
	std::cin>>n;
	std::cin>>checked;
	data = new std::string [n];
	for (i = 0; i < n; i++)
		std::cin>>data[i];
	next = cow(data,n,checked);
	std::cout<<next<<std::endl;
	delete [] data;
	return 0;
}
