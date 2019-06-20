#include <vector>
#include <iostream>

class Solution 
{
	public:
    	int removeElement(std::vector<int>& nums, int val) 
		{
			int size;
			size = nums.size();
			if(size == 0)
				return 0;
			int lowp,highp;
			if(nums[0] == val)
				lowp = 0;
			else
				lowp = 1;
			highp = 1;
			while(highp < size)
			{
				if(nums[highp] == val)
					highp++;
				else
					nums[lowp++] = nums[highp++];
			}
			return lowp;
    	}
};

int main()
{
	int aa[] = {0,1,2,2,3,0,4,2};
	std::vector<int> nums(aa,aa + sizeof(aa) / sizeof(aa[0]));
	class Solution r;
	int len = r.removeElement(nums,2);
	for(int i = 0;i < len;i++)
		std::cout<<nums[i]<<std::endl;
}
