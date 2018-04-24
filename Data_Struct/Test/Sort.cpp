#include "../Include/Sort.hpp"

using namespace std;
int main()
{
	int a[] = {9,60,1,37,4,6,12,21,43,34,5,7,86,68};
	DataList<int> aaa;
	aaa.Initial(a,sizeof(a)/sizeof(a[0]));
   /*  for(int i = 300; i > 0;--i) */
		/* aaa.Insert(i); */
	aaa.Traverse();
 	cout<<endl;
	/*  aaa.BubbleSort_I(); */
	// aaa.InsertSort();
	// aaa.BinaryInsertSort();
	// aaa.ShellSort();
	// aaa.QuickSort(aaa,0,aaa.Length());
	// aaa.Quick_Insert_Mixed_Sort(aaa,0,aaa.Length() - 1);
	 aaa.HybirdSort(aaa,0,aaa.Length());
	aaa.Traverse();
}
