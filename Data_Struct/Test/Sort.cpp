#include "../Include/Sort.hpp"

#define N 1000
#define RANGE 1000000000

using namespace std;
int main()
{
	// int b[] = {18,11,21,12,1,3,5,7,9,12,12,9,22,34,18,6,5};
	// int b[] = {98,36,-9,0,47,23,1,8,10,7};
	// int b[] = {10,9,8,7,6,5,4,3,2,1,11};
	// int b[] = {1,0,1,2,0,0,0,2,2,2,0,0,1,1,1,2,1,0,1,0,2};//Netherland Flag sequence.
	// int b[] = {3,5,2,1,4};
   // int b[] = {294,410,525,877,794,408,689,815,60,379,152,203,73,884,255,705,622,607,930,636,617,355,812,304,71,915,458,399,822,882,734,779,302,938,143,111,971,736,68,483,100,657,395};
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
 	cout<<"Array : ";
	aaa.Traverse();
     // aaa.IsSorted(b,sizeof(b)/sizeof(b[0]));
 	cout<<endl;
	// aaa.CountingSort();
	// aaa.LSD(10);
	// aaa.MSD(10);
	// aaa.BucketSort();
	// aaa.CountingSort();
	// aaa.MSD(0,10);
	// aaa.LSD(0,10);
	// aaa.MaxHeapSort();
	// aaa.MinHeapSort();
	// aaa.QuickSort();
	// aaa.Quick_Insert_Mixed_Sort(aaa,1,aaa.Length());
	// aaa.HybirdSort(aaa,1,aaa.Length());
	aaa.QuickSort(aaa,1,sizeof(b)/sizeof(b[0]));
	// aaa.BubbleSort_I();
	// aaa.CocktailSort();
	// aaa.ShellSort();
	// aaa.MergeSort(1,aaa.Length());
	// aaa.MergeSort();
	// aaa.TournamentSort();
	// aaa.BinaryInsertSort();
	// aaa.InsertSort_Ascend();
	// aaa.IfLosted(b,sizeof(b) / sizeof(b[0]));
	aaa.Traverse();
	 aaa.IsSorted(b,sizeof(b)/sizeof(b[0]));
	 cout<<endl;
	
	// aaa.InsertSort_Descend();
	// aaa.Traverse();
     // aaa.IsSorted(b,sizeof(b)/sizeof(b[0]));
	// std::cout<<aaa.DivKSearch(34,8)<<endl;
	return 0;
}
