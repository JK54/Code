#include <vector>
#include <iostream>
#include <map>

class Solution 
{
	public:
		std::vector<int> twoSum(std::vector<int> &nums,int target)
		{
			int size = nums.size();
			std::vector<int> result;
			for(int i = 0;i < size;i++)
			{
				for(int j = size - 1;j > i;j--)
				{
					if(nums[i] + nums[j] == target)
					{
						result.push_back(i);
						result.push_back(j);
					}
					else if((nums[i] + nums[j] < target && target > 0) || (nums[i] + nums[j] > target && target < 0))
						break;
				}
			}
			return result;
		}
};

class Solution2 
{
	public:
		std::vector<int> twoSum(std::vector<int> &nums,int target)
		{
			int size = nums.size();
			std::vector<int> result;
			std::map<int,int> aux;
		}
};int main()
{
	std::vector<int> aaa;
	class Solution ccc;
	aaa.push_back(2);
	aaa.push_back(7);
	aaa.push_back(11);
	aaa.push_back(15);
	std::vector<int> r(ccc.twoSum(aaa,9));
	for(int i = 0;i < r.size();i++)
		std::cout<<r[i]<<std::endl;
}
