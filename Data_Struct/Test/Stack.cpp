#include "../Include/Stack.hpp"

using namespace std;

int main()
{
	Stack<int> s;
	for(int i = 1;i < 6; ++i)
		s.Push(i);
	cout<<s.Max()<<endl;
}
