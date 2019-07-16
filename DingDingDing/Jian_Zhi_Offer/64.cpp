#include <iostream>

class Temp
{
	public:
		Temp(){++N;Sum += N;}
		static unsigned int GetSum(){return Sum;}
		static void Reset(){N = 0;Sum = 0;}
	private:
		static unsigned int N;
		static unsigned int Sum;
};

unsigned int Temp::N = 0;
unsigned int Temp::Sum = 0;

unsigned int solution1(unsigned int n)
{
	Temp::Reset();
	Temp *a = new Temp [n];
	delete [] a;
	a= nullptr;
	return Temp::GetSum();
}

typedef unsigned int (*fun)(unsigned int);
unsigned int solution2_terminator(unsigned int n)
{
	return 0;
}
unsigned int solution2(unsigned int n)
{
	static fun f[2] = {solution2_terminator,solution2};
	return n + f[!!n](n - 1);
}


template <unsigned int n>
struct solution3
{
	enum Value{N = solution3<n - 1>::N + n};
};

template<> 
struct solution3<1>
{
	enum Value{N = 1};
};

int main()
{
	unsigned int n = 100;
	std::cout<<solution1(n)<<std::endl;
	std::cout<<solution2(n)<<std::endl;
	std::cout<<solution3<100>::N<<std::endl;
}
