#include <iostream>
#include <cstring>
#include <limits.h>

template<typename T>
void swap(T &a,T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

int countbit(int num)
{
	int tmp = num;
	int bit = 0;
	while(tmp)
	{
		tmp /= 10;
		bit++;
	}
	return bit;
}

void perm(int a[],int start,int end,char *min,char *result)
{
	if(start == end)
	{
		int size = strlen(result);
		if(strlen(min) == 0 || strncmp(min,result,size) > 0)
			strncpy(min,result,size);
		// std::cout<<result<<std::endl;
	}
	else
	{
		for(int i = start;i < end;i++)
		{
			swap<int>(a[start],a[i]);
			int bit = countbit(a[start]);
			char chart[bit + 1];
			snprintf(chart,sizeof(chart),"%d",a[start]);
			strncat(result,chart,bit);
			perm(a,start + 1,end,min,result);
			swap<int>(a[start],a[i]);
			std::memset(result + strlen(result) - bit,'\0',sizeof(char) * bit);
		}
	}
}
//---------------------------------------------------------------------------------------------------

template<typename T>
int partition(T a[],int left,int right,int f(const T,const T))
{
	T dstone = a[left];
	int pos = left;
	for(int i = left + 1;i <= right;i++)
	{
		if(f(dstone,a[i]) > 0)
			if(++pos != i)
				swap<char*>(a[pos],a[i]);
	}
	swap<char*>(a[left],a[pos]);
	return pos;
}

template<typename T>
void quicksort(T a[],int left,int right,int f(T,T))
{
	if(left < right)
	{
		int pos = partition(a,left,right,f);
		quicksort(a,left,pos - 1,f);
		quicksort(a,pos + 1,right,f);
	}
}

int compare(char *str1,char *str2)
{
	int len = strlen(str1) + strlen(str2) + 1;
	char c1[len],c2[len];
	snprintf(c1,len,"%s%s",str1,str2);
	snprintf(c2,len,"%s%s",str2,str1);
	return strncmp(c1,c2,len);
}

void qsort4min(int data[],int n,int maxbit)
{
	char **nums;
	nums = new char* [n];
	for(int i = 0;i < n;i++)
	{
		nums[i] = new char [maxbit + 1];
		std::memset(nums[i],'\0',sizeof(char) * (maxbit + 1));
	}
	for(int i = 0;i < n;i++)
		snprintf(nums[i],maxbit,"%d",data[i]);
	quicksort<char*>(nums,0,n - 1,&compare);
	for(int i = 0;i < n;i++)
	{
		std::cout<<nums[i];
		delete [] nums[i];
	}
	std::cout<<std::endl;
	delete [] nums;
}
//-----------------------------------------------------------------------------------------------------
int main()
{
	int a[] = {3,32,321,9,12,7,8,11,13};
	int n = sizeof(a) / sizeof(a[0]);
	int maxbit = 0;
	for(int tmp = INT_MAX;tmp != 0;tmp /= 10,maxbit++);
	qsort4min(a,n,maxbit);
	char *min = new char [n * maxbit + 1];
	char *result = new char [n * maxbit + 1];
	std::memset(min,'\0',sizeof(char) * (n * maxbit + 1));
	std::memset(result,'\0',sizeof(char) * (n * maxbit  + 1));
	perm(a,0,n,min,result);
	std::cout<<min<<std::endl;
	delete [] min;
	delete [] result;
}
