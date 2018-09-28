#include "../Include/Sort.hpp"

#define N 200
#define RANGE 100000000

using namespace std;
int main()
{
	// int b[] = {18,11,21,12,1,3,5,7,9,12,12,9,22,34,18,6,5};
	// int b[] = {98,36,-9,0,47,23,1,8,10,7};
	// int b[] = {10,9,8,7,6,5,4,3,2,1,11};
	// int b[] = {1,0,1,2,0,0,0,2,2,2,0,0,1,1,1,2,1,0,1,0,2};//Netherland Flag sequence.
	unsigned int a[N];
	int b[N];
	std::random_device rd;
	std::mt19937 mt(rd());
	for(int i = 0;i < N;i++)
	{
		a[i] = mt() % RANGE;
		b[i] = a[i];
	}
	DataList<int> aaa;
	aaa.Initial(b,sizeof(b)/sizeof(b[0]));
 	aaa.Traverse();
 	cout<<endl;
	aaa.CountingSort();
	// aaa.LSD(10);
	// aaa.MSD(10);
	// aaa.BucketSort();
	// aaa.CountingSort();
	// aaa.MSD(0,10);
	// aaa.LSD(0,10);
	// aaa.MaxHeapSort();
	// aaa.MinHeapSort();
	// aaa.QuickSort();
	// aaa.MergeSort();
	// aaa.Quick_Insert_Mixed_Sort(aaa,1,aaa.Length());
	// aaa.HybirdSort(aaa,1,aaa.Length());
	// aaa.QuickSort(aaa,1,sizeof(b)/sizeof(b[0]));
	// aaa.BubbleSort_I();
	// aaa.CocktailSort();
	// aaa.ShellSort();
	// aaa.MergeSort(1,aaa.Length());
	// aaa.MergeSort();
	// aaa.TournamentSort();
	// aaa.InsertSort();
	// aaa.BinaryInsertSort();
	aaa.Traverse();
 	cout<<endl;
 	aaa.IsSorted(b,sizeof(b)/sizeof(b[0]));
	// std::cout<<aaa.DivKSearch(34,8)<<endl;
	return 0;
}
