#include "../Queue.h"

using namespace std;

int main()
{
	Queue<int> aaa;
	ifstream is("matrix1.txt");
	int i;
	while(is>>i)
		aaa.Enqueue_Priority(i);
	aaa.Traverse();	
}
