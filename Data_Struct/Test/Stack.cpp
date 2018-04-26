#include "../Include/Stack.hpp"

using namespace std;

int main()
{
	Stack<int> s;
	cout<<s.Size()<<endl;
	for(int i = 1;i < 6; ++i)
	{
		s.Push(i);
		cout<<s.Size()<<endl;
	}
	s.Traverse();
}
