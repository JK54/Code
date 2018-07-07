#include <iostream>

int race(int v1,int v2,int t,int s,int l)
{
	int i,j,n,s1,s2;
	i = j = n = s1 = s2 = 0;
	for(i = 0;s1 < l && s2 < l;i++)
	{
		s1 = v1 * (i - n * s);
		s2 = v2 * i;
		if(s1 - s2 >= t)
			n++;
	}
	i--;
	if(s1 == s2)
		std::cout<<"D"<<"\n"<<i<<std::endl;
	else if(s1 > s2)
		std::cout<<"R"<<"\n"<<i<<std::endl;
	else
		std::cout<<"T"<<"\n"<<i<<std::endl;
	return i;
}
int main()
{
	int v1,v2,t,s,l;
	std::cin>>v1>>v2>>t>>s>>l;
	race(v1,v2,t,s,l);
}
