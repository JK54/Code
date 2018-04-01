#include "12.19.h"

int main()
{
    ifstream is("12.20.txt");
    StrBlob str;
    string line,word;
    while (getline(is, line)) 
	{
		istringstream istr(line);
		while(istr>>word)
			str.push_back(word);
    }
	for(StrBlobPtr wstr = str.begin();wstr !=str.end();wstr.incr())
	{
		cout<<wstr.deref()<<endl;
	}
	return 0;
}
