#include <iostream>

void swap(char &a,char &b)
{
	char tmp = a;
	a = b;
	b = tmp;
}

void perm(char a[],int start,int size)
{
	if(start > size)
	{
		for(int i = 0;i <= size;i++)
			std::cout<<a[i];
		std::cout<<std::endl;
	}
	else
	{
		for(int i = start ;i <= size;i++)
		{
			swap(a[start],a[i]);
			perm(a,start + 1,size);
			swap(a[start],a[i]);
		}
	}
}

int main()
{
	char a[] = "abc";
	int size = sizeof(a) / sizeof(a[0]);
	perm(a,0,size - 2);
	return 0;
}
