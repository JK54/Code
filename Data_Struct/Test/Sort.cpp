#include "../Include/Sort.hpp"

using namespace std;
int main()
{
	int a[] = {18,19,21,12,1,3,5,7,9,12,12,9,22,34,18,6,5};
	DataList<int> aaa(32767,100);
	aaa.Initial(a,sizeof(a)/sizeof(a[0]));
   /*  for(int i = 300; i > 0;--i) */
		/* aaa.Insert(i); */
	// aaa.ShellSort();
	// aaa.MergeSort(1,aaa.Length());
	aaa.TournamentSort();
	aaa.Traverse();
 	cout<<endl;
	std::cout<<aaa.DivKSearch(34,8)<<endl;
	 // aaa.BubbleSort();
	// aaa.InsertSort();
	// aaa.BinaryInsertSort();
	// aaa.QuickSort(aaa,1,aaa.Length());
	// aaa.Quick_Insert_Mixed_Sort(aaa,0,aaa.Length() - 1);
	 // aaa.HybirdSort(aaa,1,aaa.Length());
	// aaa.CocktailSort();
	// aaa.QuickSort2();
	// aaa.HeapSort2();
	// aaa.MergeSort();
	// aaa.Traverse();
}
