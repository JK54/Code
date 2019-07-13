#include <iostream>
#include "quicksort.cpp"

//3次二分查找，将时间复杂度优化到O(logn)
int findnum(int a[],int n,int k)
{
	if(a == nullptr || n <= 0 || k > a[n - 1] || k < a[0])
		return 0;
	int left = 0,right = n - 1,mid = (left + right) / 2;
	int len = 0;
	while(a[mid] != k && left < right)
	{
		if(a[mid] < k)
			left = mid + 1;
		else
			right = mid - 1;
		mid = (left + right) >> 1;
	}

	if(a[mid] != k)
		return 0;
	int leftleft = left,leftright = mid;
	int leftmid = (leftleft + leftright) >> 1;
	while(leftleft < leftright)
	{
		if(a[leftmid] < k)
			leftleft = leftmid + 1;
		else
			leftright = leftmid - 1;
		leftmid = (leftleft + leftright) >> 1;
	}
	if(a[leftleft] < k)
		leftleft++;

	int rightleft = mid,rightright = right;
	int rightmid = (rightleft + rightright) >> 1;
	while(rightleft < rightright)
	{
		if(a[rightmid] > k)
			rightright = rightmid;
		else
			rightleft = rightmid + 1;
		rightmid = (rightright + rightleft) >> 1;
	}
	//没有这行检查结果可能会比实际大1，原因是如果初始右边界正好在所找元素右一位时，结束查找的时候·右边界将会保持不变
	if(a[rightright] > k)
		rightright--;

	len = rightright - leftleft + 1;
   /*  for(int i = mid;i < n && a[i] == k;i++) */
		// len++;
	// for(int i = mid - 1;i >= 0 && a[i] == k;i--)
		/* len++; */
	return len;
}

int main()
{
	int a[] = {1,3,3,3,3,3,1,1,1,1,2,2,2,2,2,2,10,12,11,6,7,8,9,22};
	int n = sizeof(a) / sizeof(a[0]);
	quicksort(a,0,n - 1);
	std::cout<<findnum(a,n,1)<<std::endl;
	std::cout<<findnum(a,n,2)<<std::endl;
	std::cout<<findnum(a,n,3)<<std::endl;
	std::cout<<findnum(a,n,6)<<std::endl;
	for(int i = 0;i < n;i++)
		std::cout<<a[i]<<" ";
	std::cout<<std::endl;
}
