#include "../Include/Queue.hpp"

using namespace std;

int main()
{
	Queue<int> aaa,bbb;
	ifstream is1("matrix1.txt");
	ifstream is2("matrix2.txt");
	int i;
	while(is1>>i)
		aaa.Enqueue_Priority(i);
	aaa.Traverse();	
	bbb.Copy(aaa);
	aaa.Traverse();	
	bbb.Traverse();
}
