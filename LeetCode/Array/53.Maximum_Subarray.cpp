#include <iostream>
#include <vector>

class Solution 
{
	public:
    	int maxSubArray(std::vector<int>& nums)
		{
			int size;
			int cur,maxsum;
			size = nums.size();
			if(size == 0)
				return 0;
			for(int i = 1;i < size;i++)
			{
			}
    	}
};

class Solution2 {
public:
    int maxSubArray(std::vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
        int curSum = nums[0], maxSum = nums[0]; //store first element
        for(int i = 1; i < nums.size(); i++)
        {
            curSum = nums[i] > curSum + nums[i] ? nums[i] : curSum + nums[i];
            maxSum = curSum > maxSum ? curSum : maxSum;
        }
        return maxSum;
    }
};
int main()
{
	int aa[] = {-2,1,-3,4,-1,2,1,-5,4};
	std::vector<int> nums(aa,aa + sizeof(aa) / sizeof(aa[0]));
	class Solution r;
	int sum = r.maxSubArray(nums);
	std::cout<<sum<<std::endl;
}
