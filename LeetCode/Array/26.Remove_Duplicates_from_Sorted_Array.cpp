#include <iostream>
#include <vector>

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) 
	{
        int aux;
		int size = nums.size();
  
		int i,j;
		i = 0,j = 1;
		if(size == 0)
			return 0;
		else
		{
			while(j < size)
			{
				if(nums[i] == nums[j])
					j++;
				else
					nums[++i] = nums[j++];
			}
			return i + 1;
		}
		// std::vector<int>::iterator ss;
		// for(int i = 0;i < size;i++)
		// {
			// aux = nums[i];
			// while(i + 1 < size && aux == nums[i + 1])
			// {
				// ss = nums.begin() + i + 1;
				// nums.erase(ss);
				// size--;
			// }
		// }
		/* return size; */

   /*      std::vector<int> res; */
		// for(int i = 0;i < size;i++)
		// {
			// aux = nums[i];
			// while(i + 1 < size && aux == nums[i + 1])
				// i++;
			// res.push_back(aux);
		/* } */
		// return res.size();
    }
};

int main()
{
	int arr[] = {0,0,1,1,1,2,2,3,3,4};
	class Solution aa;
	std::vector<int> bb(arr,arr + sizeof(arr) / sizeof(arr[0]));
	for(int i = 0;i < bb.size();i++)
		std::cout<<bb[i]<<" ";
	std::cout<<std::endl;
	int len = aa.removeDuplicates(bb);
	for(int i = 0;i < bb.size();i++)
		std::cout<<bb[i]<<" ";
	std::cout<<std::endl;
	std::cout<<len<<std::endl;
}
