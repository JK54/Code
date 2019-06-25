#include<iostream>
using namespace std;
void Merge(int arr[],int low,int mid,int high)//递归和非递归均一样 
{//将两个有序区归并为一个有序区
	int i=low,j=mid+1,k=0;
	int *temp=new(nothrow) int[high-low+1];
	while(i<=mid&&j<=high)
	{
		if(arr[i]<=arr[j])
			temp[k++]=arr[i++];
		else
			temp[k++]=arr[j++];
	}
	while(i<=mid) temp[k++]=arr[i++];
	while(j<=high) temp[k++]=arr[j++];
	for(i=low,k=0;i<=high;i++,k++)
		arr[i]=temp[k];	
	delete []temp;
}
//void MergeSort(int arr[],int low,int high)//递归版本的形参表 
void MergeSort(int arr[],int n)//参数和递归略不同，n代表数组中元素个数，即数组最大下标是n-1 
{//非递归实现 
	/*
	int step = 1;
	while(step<n) //当元素个数不是2的幂时可能会出错，未考虑第2个序列个数不足的情况 
	{
		for(int i=0;i<=n-step-1;i+=2*step)
			Merge(arr,i,i+step-1,i+2*step-1);
		step*=2;
	}*/
 
	int size=1,low,mid,high;
	while(size<=n-1)
	{
		low=0;
		while(low+size<=n-1)
		{
			mid=low+size-1;
			high=mid+size;
			if(high>n-1)//第二个序列个数不足size 
				high=n-1;		
			Merge(arr,low,mid,high);//调用归并子函数 
			cout<<"low:"<<low<<" mid:"<<mid<<" high:"<<high<<endl;//打印出每次归并的区间 
			low=high+1;//下一次归并时第一关序列的下界 
		}
		size*=2;//范围扩大一倍 
	}
}
int main()
{
	int x[] = {294,410,525,877,794,408,689,815,60,379,152,203,73,884,255,705,622,607,930,636,617,355,812,304,71,915,458,399,822,882,734,779,302,938,143,111,971,736,68,483,100,657,395};
	int size = sizeof(x) / sizeof(x[0]);
	MergeSort(x, size);
	for(int i=0;i < size;i++)
		cout<<x[i]<<"  ";
	cout<<endl;
	return 0;
}
/* ---------------------  */
// 作者：枫轩缘 
// 来源：CSDN 
// 原文：https://blog.csdn.net/prstaxy/article/details/8166360 
/* 版权声明：本文为博主原创文章，转载请附上博文链接！               */          
