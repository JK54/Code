#include "queue.hpp"
#include <random>

int main()
{
	Queue<int> aaa;
	std::mt19937 mt(std::random_device {}());
	int n = 100;
	int a[n];
	std::cout<<"push_back max : ";
	for(int i = 0;i < n;i++)
	{
		a[i] = mt() % n;
		// a[i] = n - i;
		aaa.push_back(a[i]);
		std::cout<<aaa.max()<<" ";
	}
	std::cout<<std::endl;
	for(int i = 0;i < n;i++)
		std::cout<<a[i]<<" ";
	std::cout<<std::endl;
	std::cout<<"pop_front max : ";
	for(int i = 0;i < n ;i++)
	{
		std::cout<<aaa.max()<<" ";
		aaa.pop_front();
	}
	std::cout<<std::endl;
}
