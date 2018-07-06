#include <iostream>

void value(long long **source,long long **dest,long long n)
{
	for(long long i = 0;i < n;i++)
		for(long long j = 0;j < n;j++)
			dest[i][j] = source[i][j];
}

void value2(long long vle,long long **dest,long long n)
{
	for(long long i = 0;i < n;i++)
		for(long long j = 0;j < n;j++)
			dest[i][j] = vle;
}
void muti(long long **data,long long **result,long long n,long long m)
{
	long long i,j,k,l;
	long long **tmp = new long long* [n];
	for(i = 0;i < n;i++)
	{
		tmp[i] = new long long[n];
		for(j = 0;j < n;j++)
			tmp[i][j] = 0;
	}
	if(m > 0)
		value(data,result,n);
	for(l = 1;l < m;l++)
	{
		for(i = 0;i < n;i++)
			for(j = 0;j < n;j++)
				for(k = 0;k < n;k++)
					tmp[i][j] += result[i][k] * data[k][j];
		value(tmp,result,n);
		value2(0,tmp,n);
	}
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
			std::cout<<result[i][j]<<" ";
		std::cout<<std::endl;
	}
	for(i = 0;i < n;i++)
		delete [] tmp[i];
	delete [] tmp;
}

int main()
{
	long long n,m,i,j;
	long long **data,**result;
	std::cin>>n>>m;
	data = new long long*[n];
	result = new long long*[n];
	for(i = 0;i < n;i++)
	{
		data[i] = new long long[n];
		result[i] = new long long[n];
		result[i][i] = 1;
		for(j = 0;j < n;j++)
			if(j != i)
				result[i][j] = 0;
	}
	for(i = 0;i < n;i++)
		for(j = 0;j < n;j++)
			std::cin>>data[i][j];
	muti(data,result,n,m);
	for(i = 0;i < n;i++)
		delete [] data[i];
	delete [] data;
	for(i = 0;i < n;i++)
		delete [] result[i];
	delete [] result;
	return 0;
}
