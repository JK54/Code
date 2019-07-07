#include <iostream>

bool isodd(int x)
{
	return x & 1;
}

bool div3(int x)
{
	return x % 3 == 0;
}

void solution(int data[],int size,bool f(int ))
{
	if(data == nullptr || size <= 0)
		return;
	int *begin = data;
	int *end = data + size - 1;
	while(begin != end)
	{
		while(begin != end && !f(*begin))
			begin++;
		while(end != begin && f(*end))
			end--;
		int tmp = *begin;
		*begin = *end;
		*end = tmp;
	}
	for(int i = 0; i < size;i++)
		std::cout<<data[i]<<" ";
	std::cout<<std::endl;
}

int main()
{
	int a[] = {1,2,3,4,5,6,7,8,9,0,10};
	int size = sizeof(a) / sizeof(a[0]);
	solution(a,size,isodd);
	solution(a,size,div3);
}
