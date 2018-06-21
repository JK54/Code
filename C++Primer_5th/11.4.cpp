#include "comm.h"
#include <array>
#include <fstream>
using namespace std;

void Word_Count(map<string, size_t>& word_count)
{
    string tmp;
    ifstream is("11.3.txt");
    while (is >> tmp) 
	{
	tmp.erase((remove_if(tmp.begin(), tmp.end(), [](char a) { return ispunct(a); })), tmp.end());
	for (auto& ch : tmp)
	    ch = tolower(ch);
	++word_count[tmp];
    }
}

int main()
{
    map<string, size_t> word_count;
    ofstream os("11.12.txt");
    Word_Count(word_count);
    for (auto i : word_count)
		cout << i.first << " occur " << i.second << endl;

    for (auto i : word_count)
		os<<i.first<<" "<<i.second<<endl;
    return 0;
}
