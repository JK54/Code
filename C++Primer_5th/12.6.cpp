#include "comm.h"

std::vector<int>  *init_vector(void)
{
	std::vector<int> *p = new std::vector<int>;
	return p;
}

void input_vector(std::vector<int> *p,std::istream &is)
{
	int tmp;
	while(is>>tmp)
	{
		p->push_back(tmp);
		std::cout<<"next elem"<<std::endl;
	}
}

void print_vector(std::vector<int> *p)
{
	for(auto i : *p)
		std::cout<<i<<std::endl;
	delete p;
}

int main()
{
	std::vector<int> *p = init_vector();
	input_vector(p,std::cin);
	print_vector(p);
}
