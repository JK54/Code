#include <vector>
#include <iostream>

class Solution {
public:
	std::vector<int> plusOne(std::vector<int>& digits) 
	{
        int size = digits.size();
		int index,carry;
		if(digits[size - 1] == 9)
		{
			digits[size - 1] = 0;
			carry = 1;	
		}
		else
		{
			digits[size - 1] += 1;
			carry = 0;
		}
		for(index = size - 2;index >= 0 && carry == 1;index--)
		{
			if(digits[index] == 9)
			{
				digits[index] = 0;
				carry = 1;
			}
			else
			{
				digits[index] += 1;
				carry = 0;
			}
		}
		if(carry == 1)
			digits.insert(digits.begin(),1);
		return digits;
    }
};

int main()
{
	int aa[] = {4,3,2,1};
	std::vector<int> digits(aa,aa + sizeof(aa) /sizeof(aa[0]));
	class Solution r;
	std::vector<int> res(r.plusOne(digits));
	for(int i = 0;i < digits.size();i++)
		std::cout<<digits[i];
	std::cout<<std::endl;
}
