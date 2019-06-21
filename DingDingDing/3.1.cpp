#include <iostream>
#include <vector>

void disp(std::vector<int> nums)
{
	for(int i = 0;i < nums.size();i++)
		std::cout<<nums[i]<<" ";
	std::cout<<std::endl;
}

bool duplicate(std::vector<int> nums,std::vector<int> &result)
{
	int size;
	size = nums.size();
	if(size == 0)
		return false;
	for(int i = 0;i < size;i++)
	{
		if(nums[i] < 0 || nums[i] > size)
			return false;
	}
	//clear vector result
	std::vector<int>().swap(result);
	for(int i = 0;i < size;i++)
	{
		while(i != nums[i])
		{
			if(nums[i] == nums[nums[i]])
			{
				result.push_back(nums[i]);
				break;
			}
			else
			{
				int tmp = nums[i];
				nums[i] = nums[nums[i]];
				nums[tmp] = tmp;
			}
			disp(nums);
		}
	}
	if(result.size() != 0)
		return true;
	return false;
}

int main()
{
	int aa[] = {2,3,1,0,2,5,3};
	std::vector<int> nums(aa,aa + sizeof(aa) / sizeof(aa[0]));
	std::vector<int> re;
	duplicate(nums,re);
	disp(re);
}
