#include "../../Include/Stack.hpp"

void conv(int n)
{
	Stack<int> s;
	int m;
	while( n != 0)
	{
		m = n % 2;
		n = n /2;
		s.Push(m);
	}
	s.Traverse();
}

int main()
{
	conv(100);
}
