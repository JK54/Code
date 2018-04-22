#include "../Include/Stack.hpp"

using namespace std;

int main()
{
	Stack<int> s;
	int j;
	for(int i = 1;i < 6; ++i)
	{
		s.Push(i);
		s.Top(j);
		cout<<j<<endl;
	}
	s.Top(j);
	cout<<j<<endl;
}
