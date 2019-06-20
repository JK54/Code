#include <iostream>
#include <vector>

class Solution 
{
public:
	std::vector<int> getRow(int numRows)
	{
		std::vector<std::vector<int>> triang(numRows + 1);
		std::vector<int> res;
		int temp;
		for(int i = 0;i <= numRows;i++)
		{
			for(int j = 0;j <= i;j++)
			{
				if(j == 0 || j == i)
					triang[i].push_back(1);
				else
				{
					temp = triang[i - 1][j - 1] + triang[i - 1][j];
					triang[i].push_back(temp);
				}
			}
		}
		for(int i = 0;i <= numRows;i++)
			res.push_back(triang[numRows][i]);
		return res;
    }
};

int main()
{
	class Solution r;
	int num = 0;
	std::vector<int> aa(r.getRow(num));
	for(int i = 0;i <= num;i++)
		std::cout<<aa[i]<<" ";
	std::cout<<std::endl;
}
