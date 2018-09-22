#include <iostream>
#include <cstring>
using namespace std;
void KMP(char T[],char P[])
{
	int lengthP,lengthT,j,k,*next;
	lengthP = strlen(P);
	lengthT = strlen(T);
	next = new int[lengthP];
	//get next.
	for(j = 0,k = -1,next[0] = -1;j < lengthP - 1;)
	{
		if(k == -1||P[j] == P[k])
		{
			++j;
			++k;
			next[j] = k;
		}
		else
			k = next[k];
	}
	//output1
	for(j = 0;j < lengthP;j++)
		cout<<j<<'\t';
	cout<<endl;
	for(j = 0;j < lengthP;j++)
		std::cout<<P[j]<<'\t';
	cout<<endl;
	for(j = 0;j < lengthP; ++j)
		cout<<next[j]<<'\t';
	cout<<endl;
	j = k = 0;
	//patch
	while(j < lengthP && k < lengthT)
	{
		if( j == -1 || P[j] == T[k])
		{
			++j;
			++k;
		}
		else
			j = next[j];
	}
	//output2
	if( j < lengthP)
		cout<<"failed"<<endl;
	else
	{
		cout<<"successed"<<endl;
		cout<<T<<endl;
		for(int i = 1; i <= k - j ;++i)
			cout<<" ";
		cout<<P<<endl<<endl;
	}
	delete [] next;
}

int main()
{
	char T[1000],P[1000];
	std::cin>>T>>P;
	KMP(T,P);
	return 0;
}
