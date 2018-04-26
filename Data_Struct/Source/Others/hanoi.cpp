#include "../../Include/sys_comm.h"

using namespace std;

void Hanoi(int n,string A, string B, string C)
{
	if(n == 1)
	{
		cout<<"Move top disk from peg "<<A<<" to peg "<<C<<endl;
	}
	else
	{
		Hanoi(n-1,A,C,B);
		cout<<"Move top disk from peg "<<A<<" to peg "<<B<<endl;
		Hanoi(n-1,B,A,C);
	}
}

int main()
{
	Hanoi(9,"A","B","C");
}
