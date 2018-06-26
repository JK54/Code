#include <iostream>
#include <sstream>
void handlewithcomma(int &n,std::istream &is)
{
	std::string tmp;
	std::getline(is,tmp,',');
	std::istringstream tmp2(tmp);
	tmp2>>n;
}

void solve(int a,int b,int m)
{
	int i,j;
	for(i = 1; i <= m;i++)
		for(j = 1; j <= m;j++)
			if(a * i + b * j <= m && j >= i)
				std::cout<<i<<","<<j<<std::endl;
}
int main()
{
	int a, b, m;
	handlewithcomma(a,std::cin);
	handlewithcomma(b,std::cin);
	std::cin>>m;
	solve(a,b,m);
	return 0;
}
