#include <iostream>

void insertsort(int*,int);
void print(int *,int);
int main()
{
	int m,n,i,j,k,*A,*B,*C;
	std::cin>>m;
	A = new int[m];
	for(i = 0 ; i < m;i++)
		std::cin>>A[i];
	std::cin>>n;
	B = new int[n];
	for(i = 0 ; i < n;i++)
		std::cin>>B[i];
	C = new int [m + n];
	insertsort(A,m);
	insertsort(B,n);
	for(i = 0,j = 0,k = 0;i < m && j < n;)
	{
		if(A[i] == B[j])
			C[k++] = A[i++];
		else if(A[i] > B[j])
			j++;
		else
			i++;
	}
	print(C,k);
	for(i = 0,j = 0,k = 0;i < m && j < n;)
	{
		if(A[i] == B[j])
		{
			C[k++] = A[i++];
			j++;
		}
		else if(A[i] > B[j])
			C[k++] = B[j++];
		else
			C[k++] = A[i++];
	}
	while(i < m)
		C[k++] = A[i++];
	while(j < n)
		C[k++] = B[j++];
	print(C,k);
	for(i = 0,j = 0,k = 0;i < m && j < n;)
	{
		if(A[i] == B[j])
			i++,j++;
		else if(A[i] > B[j])
			j++;
		else
			C[k++] = A[i++];
	}
	while(i < m)
		C[k++] = A[i++];
	print(C,k);
	delete [] A;
	delete [] B;
	delete [] C;
	return 0;
}

void insertsort(int *data,int n)
{
	int i,j;
	int tmp;
	for(i = 1;i < n;i++)
	{
		if(data[i - 1] > data[i])
		{
			tmp = data[i];
			for(j = i;j >= 1 && tmp < data[j - 1];j--)
				data[j] = data[j - 1];
			data[j] = tmp;
		}
	}
}

void print(int *data,int n)
{
	for(int i = 0;i < n;i++)
		std::cout<<data[i]<<" ";
	std::cout<<std::endl;
}
