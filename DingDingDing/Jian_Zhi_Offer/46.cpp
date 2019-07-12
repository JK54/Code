#include <iostream>
#include <cstring>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::memset;
using std::vector;

char transnum2char(int n)
{
	if(n > 25)
		return '$';
	return 'a' + n;
}

int transchar2num(char c)
{
	if(c >= 'a' && c <= 'z')
		return c - 'a';
	return -1;
}

void handleinput(char *nums,int len)
{
	std::memset(nums,'\0',sizeof(char) * len);
	bool fin = false;
	while(!fin)
	{
		fin = true;
		cout<<"输入数字"<<endl;
		cin.get(nums,len);
		cin.get();
		for(int i = 0;fin && i < len && nums[i] != '\0';i++)
			if(!isdigit(nums[i]))
				fin = false;
		if(!fin)
			memset(nums,'\0',sizeof(char) * strlen(nums));
	}
}

void countcon(char *nums,char *result,int &count)
{
	if(*nums == '\0')
	{
		count++;
		cout<<result<<endl;
		return;
	}
	int num1 = *nums - '0';
	char tmp1 = transnum2char(num1);
	char res1[strlen(result) + 2];
	memset(res1,'\0',sizeof(char) * (strlen(result) + 2));
	snprintf(res1,strlen(result) + 2,"%s%s",result,&tmp1);
	countcon(nums + 1,res1,count);
	if(*(nums + 1) != '\0')
	{
		int num2 = num1 * 10 + *(nums + 1) - '0';
		if(num2 >= 10 && num2 <= 25)
		{
			char tmp2 = transnum2char(num2);
			char res2[strlen(result) + 2];
			memset(res2,'\0',sizeof(char) * (strlen(result) + 2));
			snprintf(res2,strlen(result) + 2,"%s%s",result,&tmp2);
			countcon(nums + 2,res2,count);
		}
	}
}
	
int countcon2(char *nums,int &count)
{
	count = 0;
	if(nums == nullptr)
		return 0;

	int numlen = strlen(nums);
	int counts[numlen];
	std::vector<char*> result,transition;
	char tmp[numlen + 1];

	if(numlen == 0)
		return 0;
	counts[numlen - 1] = 1;
	snprintf(tmp,2,"%c",transnum2char(nums[numlen - 1] - '0'));
	result.push_back(tmp);
	if(numlen == 1)
		count = 1;
	else
	{
		for(int i = numlen - 2 ;i >= 0;i--)
		{
			count = counts[i + 1];
			int num1 = nums[i] - '0',num2 = nums[i + 1] - '0';
			int num = 10 * num1 + num2;
			if(num >= 10 && num <= 25)
			{
				if(i < numlen - 2)
					count += counts[i + 2];
				else
					count += 1;
			}
			counts[i] = count;

			while(result.size () != 0)
			{
				int charlen = strlen(result.back()) + 2;
				char *res1 = new char [charlen];
				snprintf(res1,charlen,"%c%s",transnum2char(num1),result.back());
				result.pop_back();
				transition.push_back(res1);
				if(num >= 10 && num <= 25)
				{
					if(i <= numlen - 3 && transchar2num(res1[1]) == (num2 * 10 + nums[i + 2] - '0'))
						continue;
					char *res2 = new char [charlen];
					snprintf(res2,charlen,"%c%s",transnum2char(num),res1 + 2);
					transition.push_back(res2);
				}
			}
			for(int j = 0,size = transition.size();j < size;j++)
			{
				result.push_back(transition.back());
				transition.pop_back();
			}
		}
	}
	for(vector<char*>::iterator i = result.begin();i != result.end();++i)
	{
		cout<<*i<<endl;
		delete [] *i;
	}
	count = counts[0];
	cout<<count<<endl;
	return count;
}

int main()
{
	char nums[BUFSIZ],result[BUFSIZ];
	handleinput(nums,BUFSIZ);
	int count = 0;
	memset(result,'\0',BUFSIZ);
	// countcon(nums,result,count);
	countcon2(nums,count);
}
