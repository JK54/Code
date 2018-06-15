#include <iostream>
#include <fstream>

#define LENGTH 100
#define MAXWORDLEN 20
void Check(std::string *list,std::string wanted,std::string &result)
{
	int i = 0;
	std::string::iterator p,q;
	std::string tmp;
	tmp = list[0];
	result = "";
	q = wanted.begin();
	while(tmp != "")
	{
		p = tmp.begin();
		while(*q == *p && p != tmp.end() && q != wanted.end())
			p++,q++;
		if( p == tmp.end() && q == wanted.end())
			result = tmp;
		else
			tmp = list[++i];
	}
	if(result == "")
		result = "NOANSWER";
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
