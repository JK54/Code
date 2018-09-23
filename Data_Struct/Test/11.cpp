#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<vector<int>> aaa(10,vector<int>());
	for(int i = 0;i < 10;i++)
	{
		for(int j = 0;j < 10;j++)
			aaa[i].push_back(j);
	}
	for(int i = 0;i < 10;i++)
	{
		for(int j = 0;j < 10;j++)
			std::cout<<aaa[i][j]<<" ";
		cout<<endl;
	}
}
