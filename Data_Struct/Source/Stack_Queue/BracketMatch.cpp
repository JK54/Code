#include "../../Include/Stack.hpp"

bool BracketMatch(std::string &str)
{/*{{{*/
	Stack<char> brack;
	char trev;
	std::string::iterator cg = str.begin();
	while(cg != str.end())
	{
		switch(*cg)
		{
			case '(':
			case '[':
			case '{':
				brack.Push(*cg);
				break;
			case '}':
				if(!brack.Pop(trev))
					return false;
				else
				{
					if(trev == '{');
					else
						return false;
				}
				break;
			case ']':
				if(!brack.Pop(trev))
					return false;
				else
				{
					if(trev == '[');
					else
						return false;
				}
				break;
			case ')':
				if(!brack.Pop(trev))
					return false;
				else
				{
					if(trev == '(');
					else
						return false;
				}
				break;
		}
		cg++;
	}
	if(brack.IsEmpty())
		return true;
	else
		return false;
}/*}}}*/

int main(int agrv,char **argc)
{
	if(agrv <= 1)
	{
		std::cout<<"Usage: ./a.out string"<<std::endl;
		return 1;
	}
	std::string tmp = std::string(argc[1]);
	std::cout<<tmp<<std::endl;
	std::cout<<BracketMatch(tmp)<<std::endl;
	return 0;
}
