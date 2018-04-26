#include "../Include/sys_comm.h"

using namespace std;

int KMP(string T,string P)
{
int j = 0,k = -1;//计算next数组
int *next = new int[P.length()];
next[0] = -1;
int posT = 0,posP = 0;//匹配过程
int lengthP = P.length();
int lengthT = T.length();
//先计算next
while(j < lengthP)
{
	if( k == -1||P[j] == P[k])
		next[++j] = ++k;
	else
		k = next[k];
}
//打印next的结果
for(int l = 0;l < lengthP; ++l)cout<<l<<"\t";cout<<endl;
for(int l = 0;l < lengthP; ++l)cout<<P[l]<<"\t";cout<<endl;
for(int l = 0;l < lengthP; ++l)cout<<next[l]<<"\t";cout<<endl;

// 匹配过程
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
	cout<<"匹配失败"<<endl;
	return -1;
}
else
{
	cout<<"匹配成功"<<endl;
	cout<<T<<endl;
	for(auto i = 1; i <= posT - posP ;++i)
		cout<<" ";
	cout<<P<<endl<<endl;
	return posT - posP;
}
delete [] next;
}


int main(int argc,char **argv)
{
	string T = argv[1];
	string P = argv[2];
	KMP(T,P);
}
