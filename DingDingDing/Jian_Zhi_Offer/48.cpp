#include <iostream>
#include <cstring>

//动态规划，辅助数组每一个元素存储以该下标为结尾的最长不重复子串长度，因为对于每一个字母，都需要往前寻找是否存在重复，最差时间复杂度为O(n^2)
int uniquesubstring1(char *str,int len)
{
	if(str == nullptr || len <= 0)
		return 0;
	int acc[len],maxlen,index;
	acc[0] = 1;
	for(int i = 1;i < len;i++)
	{
		acc[i] = -1;
		for(int j = i - 1;j >= i - acc[i - 1] && acc[i] == -1;j--)
		{
			if(str[j] == str[i])
				acc[i] = i - j;
		}
		if(acc[i] == -1)
			acc[i] = acc[i - 1] + 1;
	}

	maxlen = 0;
	index = 0;
	for(int i = 0;i < len;i++)
	{
		if(acc[i] > maxlen)
		{
			maxlen = acc[i];
			index = i;
		}
	}

   /*  for(int i = 0;i < len;i++) */
		// std::cout<<str[i]<<" ";	
	// std::cout<<std::endl;
	// for(int i = 0;i < len;i++)
		// std::cout<<acc[i]<<" ";	
	/* std::cout<<std::endl; */
	for(int i = index - maxlen + 1;i <= index;i++)
		std::cout<<str[i];
	std::cout<<std::endl;
	return maxlen;
}

//换一种思路,还是动态规划，但是辅助数组存储的是最近一次的字符出现下标，时间复杂度改善为O(n)
int uniquesubstring2(char *str,int len)
{
	if(str == nullptr || len <= 0)
		return 0;
	int position[26];
	int curlen = 0;
	int maxlen = 0,maxendindex = 0;
	for(int i = 0;i < 26;i++)
		position[i] = -1;
	for(int i = 0;i < len;i++)
	{
		int preindex = position[str[i] - 'a'];
		if(preindex < 0 || i - preindex > curlen)
			++curlen;
		else
			curlen = i - preindex;
		if(curlen > maxlen)
		{
			maxlen = curlen;
			maxendindex = i;
		}
		position[str[i] - 'a'] = i;
	}
	for(int i = maxendindex - maxlen + 1;i <= maxendindex;i++)
		std::cout<<str[i];
	std::cout<<std::endl;
	return maxlen;
}

int main()
{
	char str[] = "arabcacfrabcdef";
	int len = strlen(str);
	std::cout<<uniquesubstring1(str,len)<<std::endl;
	std::cout<<uniquesubstring2(str,len)<<std::endl;
}
