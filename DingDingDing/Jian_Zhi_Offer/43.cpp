#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;


int countone(int n)
{
	if(n <= 0)
		return 0;
	int count = 0;
	for(int i = 1;i <= n;i++)
	{
		int j = i;
		while(j)
		{
			if(j % 10 == 1)
				count++;
			j /= 10;
		}
	}
	cout<<count<<endl;
	return count;
}

int countdigit(int n,int k)
{
	if(n <= 0)
		return 0;
	int count = 0;
	int base = 1;
	for(int round = n;round != 0;)
	{
		int weight = round % 10;
		round /= 10;
		count += round * base;
		if(weight == k)
			count += n % base + 1;
		else if(weight > k)
			count += base;
		base *= 10;
	}
	cout<<count<<endl;
	return count;
}

/* int countdigit(char *str,int n,int k) */
// {
	// if(n <= 0)
		// return 0;
	// for(int i = 0; i < n;i++)
		// if(!isdigit(str[i]))
			// return 0;
	// int count = 0;
	// int base = 1;
	// for(int i = 0;i < n;i++)
	// {
		// int weight = str[i];
		
	// }	
	// cout<<count<<endl;
	// return count;
/* } */

int main()
{
	int n;
	char str[1000];
	cin>>n;
	// cin>>str;
	// countone(n);
	countdigit(n,1);
	// countdigit(str,strlen(str),1);
}
