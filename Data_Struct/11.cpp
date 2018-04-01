#include "./include/sys_comm.h"

using namespace std;

int main()
{
	int a;
	int *b = &a;
	cout<<typeid(b).name()<<endl;
}
