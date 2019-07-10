#include <iostream>
#include <cstring>

void swap(int &a,int &b)
{
	int tmp = a;
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

char *perm(int a[],int start,int end,char *min,char *result)
{
	if(start == end)
	{
		int size = strlen(result);
		if(strlen(min) == 0 || strncmp(min,result,size) > 0)
			strncpy(min,result,size);
		std::cout<<result<<std::endl;
	}
	else
	{
		for(int i = start;i < end;i++)
		{
			swap(a[start],a[i]);
			int bit = countbit(a[start]);
			char chart[bit + 1];
			snprintf(chart,sizeof(chart),"%d",a[start]);
			strncat(result,chart,bit);
			perm(a,start + 1,end,min,result);
			swap(a[start],a[i]);
			std::memset(result + strlen(result) - bit,'\0',sizeof(char) * bit);
		}
	}
	return min;
}

int main()
{
	int a[] = {3,32,321,9};
	int n = sizeof(a) / sizeof(a[0]);
	char min[30],result[30];
	std::memset(min,'\0',sizeof(char) * 30);
	std::memset(result,'\0',sizeof(char) * 30);
	perm(a,0,n,min,result);
	std::cout<<min<<std::endl;
}
