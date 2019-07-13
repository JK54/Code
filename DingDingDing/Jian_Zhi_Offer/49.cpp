#include <iostream>

bool isuglynum(int num)
{
	while(num % 2 == 0)
		num >>= 1;
	while(num % 3 == 0)
		num /= 3;
	while(num % 5 == 0)
		num /= 5;
	return (num == 1) ? true : false;
}

int uglynum(int index)
{
	if(index <= 0)
		return 0;
	int num = 0,uglyindex = 0;
	while(uglyindex < index)
	{
		++num;
		if(isuglynum(num))
			uglyindex++;
	}
	return num;
}

int min(int a,int b,int c)
{
	return a > b ? (b > c ? c : b) : (a > c ? c : a);
}

int uglynum2(int index)
{
	int ugly[index];
	int *T2,*T3,*T5;
	ugly[0] = 1;
	T2 = T3 = T5 = ugly;
	int uglynum = 1;
	while(uglynum < index)
	{
		ugly[uglynum] = min(*T2 * 2,*T3 * 3,*T5 * 5);
		while(*T2 * 2 <= ugly[uglynum])
			T2++;
		while(*T3 * 3 <= ugly[uglynum])
			T3++;
		while(*T5 * 5 <= ugly[uglynum])
			T5++;
		++uglynum;
	}
	return ugly[uglynum - 1];
}

int main()
{
	int n = 1500;
	std::cout<<uglynum2(n)<<std::endl;
}
