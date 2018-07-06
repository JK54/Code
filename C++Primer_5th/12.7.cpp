#include "comm.h"

std::shared_ptr<std::vector<int>>  init_vector(void)
{
	 return std::make_shared<std::vector<int>>();
	/*
	 * std::shared_ptr<std::vector<int>> p;
	 * return p;
	 */
}

void input_vector(std::shared_ptr<std::vector<int>> p,std::istream &is)
{
	int tmp;
	while(is>>tmp)
	{
		(*p).push_back(tmp);
		std::cout<<"next elem"<<std::endl;
	}
	std::cout<<"use count"<<p.use_count()<<std::endl;
}

void print_vector(std::shared_ptr<std::vector<int>> p)
{
	for(auto i : *p)
		std::cout<<i<<std::endl;
}

int main()
{
	auto p = init_vector();
	std::cout<<p.use_count()<<std::endl;
	input_vector(p,std::cin);
	print_vector(p);
}
