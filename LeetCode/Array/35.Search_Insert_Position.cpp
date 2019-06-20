#include <iostream>
#include <vector>

class Solution {
public:
    int searchInsert(std::vector<int>& nums, int target) 
	{
		int size = nums.size();
		if(size == 0)
			return 0;
		for(int i = 0;i < size;i++)
		{
			if(nums[i] >= target)
				return i;
		}
		return size;
	}
};

int main()
{
	int aa[] = {1,3,5,6};
	std::vector<int> nums(aa,aa + sizeof(aa) / sizeof(aa[0]));
	class Solution r;
	int len = r.searchInsert(nums,7);
	std::cout<<len<<std::endl;
}
