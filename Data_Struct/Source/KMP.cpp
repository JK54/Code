#include <iostream>
#include <cstdlib>

using namespace std;

int KMP(string T,string P)
{
	int lengthP = P.length();
	int lengthT = T.length();
	int j = 0,k = -1;
	int * next = new int[lengthP];
	int posT = 0,posP = 0;
	next[0] = -1;
	while(j < lengthP)
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
	for(int l = 0;l < lengthP; ++l)cout<<l<<"\t";cout<<endl;
	for(int l = 0;l < lengthP; ++l)cout<<P[l]<<"\t";cout<<endl;
	for(int l = 0;l < lengthP; ++l)cout<<next[l]<<"\t";cout<<endl;
	while(posP < lengthP && posT < lengthT)
	{
		if( posP == -1 || P[posP] == T[posT])
		{
			++posP;
			++posT;
		}
		else
			posP = next[posP];
	}
	if( posP < lengthP)
	{
		cout<<"failed"<<endl;
		return -1;
	}
	else
	{
		cout<<"successed"<<endl;
		cout<<T<<endl;
		for(int i = 1; i <= posT - posP ;++i)
			cout<<" ";
		cout<<P<<endl<<endl;
		return posT - posP;
	}
	delete [] next;
}


int main()
{
	string T,P;
	std::cin>>T>>P;
	KMP(T,P);
	return 0;
}
