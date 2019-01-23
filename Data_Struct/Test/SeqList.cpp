#include "../Include/SeqList.hpp"

using namespace std;

int main()
{
	SeqList<int> aaa,bbb;
	int a1[] = {90,14,12,1,3,5,67,8,9,21,34,54,65,67,22,21};
	int b1[] = {101,201,22,1,1,33,44,55,66};
	aaa.Init(a1,sizeof(a1)/sizeof(a1[0]));
	bbb.Init(a1,sizeof(a1)/sizeof(a1[0]));
	// aaa.Merge(bbb);
	// aaa.RemoveRepeat();
	// aaa.Traverse();
	// int i,j;
	// aaa.Min_Max(i,j);
	// cout<<i<<"\t"<<j<<endl;
	// aaa.Reserve(5);
	// aaa.Traverse();
	aaa.Traverse();
	bbb.Traverse();
	cout<<aaa.Compare(bbb)<<endl;
}
