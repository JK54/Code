#include <iostream>
#include <fstream>
#include <string.h>

#define LENGTH 100
#define MAXWORDLEN 20
//5 situation:1.one less char;2.one more char;3.one wrong char;4.absolutely correct;5.others,just return "NOANSWER"
void Check(std::string *list,int n,std::string wanted,std::string &result)
{
	int i,j,k,l,m;
	l = wanted.length();
	std::string::iterator p,q;
	std::string tmp;
	std::string tmpresult;
	result = "";
	for(i = 0;i < n;i++)
	{
		tmp = list[i];
		p = tmp.begin();
		q = wanted.begin();
		m = tmp.length();
		if(m == l - 1)
		{
			k = 0;
			for(j = 0;j < l;j++)
			{
				if(*p == *q)
					p++,q++,k++;
				else
					q++;
			}
			if(k == m && tmpresult == "")
				tmpresult = tmp;
		}
		else if(m == l + 1)
		{
			k = 0;
			for(j = 0;j < m;j++)
			{
				if(*p == *q)
					p++,q++,k++;
				else
					p++;
			}
			if(k == l && tmpresult == "")
				tmpresult = tmp;
		}
		else if(m == l)
		{
			if(tmp == wanted)
			{
				result = tmp;
				return;
			}
			else
			{
				k = 0;
				for(j = 0;j < m;j++)
				{
					if(*p == *q)
						p++,q++,k++;
					else
						p++,q++;
				}
				if(k == l - 1&& tmpresult == "")
					tmpresult = tmp;				
			}
		}
	}
	if(tmpresult =="")
		result = "NOANSWER";
	else
		result = tmpresult;
}
int main()
{
	int n,i;
	std::string wanted;
	std::cin>>wanted;
	std::cin>>n;
	std::string result;
	std::string *list = new std::string [n];
	for(i = 0;i < n;i++)
		std::cin>>list[i];
	Check(list,n,wanted,result);
	std::cout<<result<<std::endl;
	delete [] list;
	return 0;
}
