#include <iostream>
#include <cstring>

void reverse(char *str,int left,int right)
{
	if(left >= right)
		return;
	for(int i = left,j = right;i < j;i++,j--)
		std::swap(str[i],str[j]);
}

void leftreverse(char *str,int k)
{
	if(str == nullptr)
		return;
	int n = strlen(str);
	if(k >= n || k < 0)
		return;
	std::cout<<str<<std::endl;
	char tmp[n + 1];
	strncpy(tmp,str + k,n - k + 1);
	strncpy(tmp + (n - k),str,k);
	strncpy(str,tmp,n);
	std::cout<<str<<std::endl;
}

void leftreverse2(char *str,int k)
{
	if(str == nullptr)
		return;
	int n = strlen(str);
	if(k >= n || k < 0)
		return;
	std::cout<<str<<std::endl;
	int leftbegin,leftend,rightbegin,rightend;
	leftbegin = 0;
	leftend = k - 1;
	rightbegin = k;
	rightend = n - 1;
	reverse(str,leftbegin,leftend);
	reverse(str,rightbegin,rightend);
	reverse(str,0,n - 1);
	std::cout<<str<<std::endl;
}

int main()
{
	char str1[] = "I am Gundam!";
	char str2[] = "I am Gundam!";
	leftreverse(str1,4);	
	leftreverse2(str2,4);	
}
