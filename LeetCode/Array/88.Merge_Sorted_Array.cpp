#include <iostream>
#include <vector>

class Solution 
{
	public:
    	void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n)
		{
			int indexs1,indexs2;
			indexs1 = indexs2 = 0;
			std::vector<int> temp;
			while(indexs1 < m && indexs2 < n)
			{
				if(nums1[indexs1] < nums2[indexs2])
					temp.push_back(nums1[indexs1++]);
				else
					temp.push_back(nums2[indexs2++]);
			}
			while(indexs1 < m)
				temp.push_back(nums1[indexs1++]);
			while(indexs2 < n)
				temp.push_back(nums2[indexs2++]);
			for(int i = 0;i < m + n;i++)
			{
				nums1[i] = temp[i];
				// std::cout<<nums1[i]<<",";
			}
			// std::cout<<std::endl;
		}
};

int main()
{
	int s1[] = {1,2,3};
	int s2[] = {2,5,6};
	std::vector<int> nums1(s1,s1 + sizeof(s1) / sizeof(s1[0]));
	std::vector<int> nums2(s2,s2 + sizeof(s2) / sizeof(s2[0]));
	class Solution r;
	r.merge(nums1,3,nums2,3);
}
