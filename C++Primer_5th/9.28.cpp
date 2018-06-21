#include "comm.h"

using namespace std;

void string_insert_flst(forward_list<string> & F,string a,string b)
{
	auto curr = F.begin();
	while(curr != F.end())
	{
		if(*curr == a)
		{
			F.insert_after(curr,b);
			break;
		}
		++curr;
	}
	if(curr ==F.end())
		F.insert_after(curr,b);
	for(auto i:F)
		cout<<i<<endl;
}

int main()
{
	string a = "Hello,";
	string b = "World!";
	forward_list<string> F{"Hello","Heeeee","F word","Hello,"};
	string_insert_flst(F,a,b);
	return 0;
}
