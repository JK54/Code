#include "../Include/Hash.hpp"

using namespace std;

int main()
{
	ifstream is("hash.txt");
	HashTable<int> ss;
	// ss.BuildHash(is);
	for(int i = 0; i<300;++i)
		ss.Insert(i);
	ss.Traverse();
}
