#include <iostream>

int mininorder(int data[],int left,int right)
{
	int result = data[left];
	for(int i = left;i <= right;i++)
		 if(result > data[i])
			 result = data[i];
	return result;
}

int solution(int data[],int len)
{
	int left,right,mid;
	left = 0;
	mid = left;
	right = len - 1;
	while(data[left] >= data[right])
	{
		if(right - left == 1)
			return data[right];
		mid = (left + mid) / 2;
		if(data[left] == data[right] && data[left] == data[mid])
			return mininorder(data,left,right);
		if(data[mid] >= data[left])
			left = mid;
		else if(data[mid] >= data[right])
			right = mid;
	}
	return data[mid];
}
