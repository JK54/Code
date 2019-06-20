#include <iostream>
#include <vector>

class Solution 
{
public:
	std::vector<std::vector<int>> generate(int numRows) 
	{
		std::vector<std::vector<int>> triang(numRows);
		int temp;
		for(int i = 0;i < numRows;i++)
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
		// for(int i = 0;i < numRows;i++)
		/*
		 * {
		 *     for(int j = 0;j <= i;j++)
		 *         std::cout<<triang[i][j]<<" ";
		 *     std::cout<<std::endl;
		 * }		
		 */
		return triang;
    }
};

int main()
{
	class Solution r;
	int num = 5;
	std::vector<std::vector<int>> aa(r.generate(num));
	for(int i = 0;i < num;i++)
	{
		for(int j = 0;j <= i;j++)
			std::cout<<aa[i][j]<<" ";
		std::cout<<std::endl;
	}
}
