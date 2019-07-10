#include <iostream>

void swap(int &a,int &b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}

int partition(int data[],int left,int right)
{
	int dstone = data[left];
	int pos = left;
	for(int i = left + 1;i <= right;i++)
		if(data[i] < dstone)
			if(++pos != i)
				swap(data[pos],data[i]);
	if(pos != left)
		swap(data[pos],data[left]);
	return pos;
}

bool check(int data[],int len,int value)
{
	int times = 0;
	for(int i = 0; i< len;i++)
		if(data[i] == value)
			times++;
	if(2 * times > len)
		return true;
	return false;
}

int findmorethanhalf(int data[],int len)
{
	if(data == nullptr || len <= 0)
		return 0;
	int begin = 0,end = len - 1;
	int mid = partition(data,begin,len - 1);
	int mlen = len >> 1;
	while(mid != mlen)
	{
		if(mid > mlen)
			end = mid - 1;
		else
			begin = mid + 1;
		mid = partition(data,begin,end);
	}
	if(check(data,len,data[mid]))
		return data[mid];
	return 0;

}
int findmorethanhalf2(int data[],int len)
{
	int times = 0;
	int dstone;
	for(int i = 0;i < len;i++)
	{
		if(times == 0)
		{
			dstone = data[i];
			times++;
		}
		else if(dstone != data[i])
			times--;
		else
			times++;
	}
	if(times != 0)
		if(check(data,len,dstone))
			return dstone;
	return 0;
}

int main()
{
	int a[] = {1,5,10,10,10,6,8,7,10,10,10,3,10,2,10,45,10,10,65,8,3,2,10};
	int b[] = {10,5,10,10,10,6,8,7,10,10,10,3,10,2,10,10,10,10,45,10,10,65,8,3,2,10};
	int na = sizeof(a) / sizeof(a[0]);
	int nb = sizeof(b) / sizeof(b[0]);
	std::cout<<findmorethanhalf(a,na)<<std::endl;
	std::cout<<findmorethanhalf(b,nb)<<std::endl;
	return 0;
}
