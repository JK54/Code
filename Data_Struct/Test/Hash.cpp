#include "../Include/Hash.hpp"

using namespace std;

int main()
{
	ifstream is("hash.txt");
	HashTable<int> ss;
	ss.BuildHash(is);
	ss.Traverse();
}
