#include "comm.h"

using namespace std;

void cast1(vector<int> vi)
{
	auto iter = vi.begin();
	while(iter != vi.end())
	{
		if(*iter % 2)	
		{
			iter = vi.insert(iter,*iter);
			iter +=2;
		}
		else
			iter = vi.erase(iter);
	}
	for (auto i : vi)
		cout<<i<<" ";
	cout<<endl;
}
void cast2(list<int> vi)
{
	auto iter = vi.begin();
	while(iter != vi.end())
	{
		if(*iter % 2)	
		{
			iter = vi.insert(iter,*iter);
			++iter;
			++iter;
		}
		else
			iter = vi.erase(iter);
	}
	for (auto i : vi)
		cout<<i<<" ";
	cout<<endl;
}
void cast3(forward_list<int> vi)
{
	auto preiter = vi.before_begin();
	auto iter = vi.begin();
	while(iter != vi.end())
	{
		if(*iter % 2)	
		{
			iter = vi.insert_after(iter,*iter);
			++iter;
			++preiter;
			++preiter;
		}
		else
		{
			iter = vi.erase_after(preiter);
		}
	}
	for (auto i : vi)
		cout<<i<<" ";
	cout<<endl;
}
int main()
{
	vector<int> vi = {0,1,1,2,3,5,8,13,21,34,55,89};
	cast1(vi);
	list<int> vii(vi.begin(),vi.end());
	cast2(vii);
	forward_list<int> viii(vi.begin(),vi.end());
	cast3(viii);
	return 0;
}
