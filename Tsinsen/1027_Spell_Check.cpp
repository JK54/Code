#include <iostream>
#include <fstream>
#include <string.h>

#define LENGTH 100
#define MAXWORDLEN 20
//5 situation:1.one less char;2.one more char;3.one wrong char;4.absolutely correct;5.others,just return "NOANSWER"
void Check(std::string *list,std::string wanted,std::string &result)
{
	size_t i,j,k;
	std::string::iterator p,q;
	std::string tmp;
	std::string tmpresult;
	result = "";
	for(i = 0;i < LENGTH;i++)
	{
		tmp = list[i];
		p = tmp.begin();
		q = wanted.begin();
		if(tmp.length() == wanted.length() - 1)
		{
			k = 0;
			for(j = 0;j < wanted.length();j++)
			{
				if(*p == *q)
					p++,q++,k++;
				else
					q++;
			}
			if(k == wanted.length() - 1 && tmpresult == "")
				tmpresult = tmp;
		}
		else if(tmp.length() == wanted.length() + 1)
		{
			k = 0;
			for(j = 0;j < tmp.length();j++)
			{
				if(*p == *q)
					p++,q++,k++;
				else
					p++;
			}
			if(k == wanted.length() && tmpresult == "")
				tmpresult = tmp;
		}
		else
		{
			if(tmp == wanted)
			{
				result = tmp;
				return;
			}
			else
			{
				k = 0;
				for(j = 0;j < tmp.length();j++)
				{
					if(*p == *q)
						p++,q++,k++;
					else
						p++,q++;
				}
				if(k == wanted.length() && tmpresult == "")
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
	int i = 0;
	std::ifstream is("1027_Word_List.txt");
	std::string *list = new std::string [LENGTH];
	std::string wanted;
	std::string result;
	while(is)
		std::getline(is,list[i++]);
	std::cin>>wanted;
	Check(list,wanted,result);
	std::cout<<result<<std::endl;
	delete [] list;
}
