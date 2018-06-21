#include "13.39.h"

using namespace std;

int main()
{
	initializer_list<string> s1{"a","b","c","d"};
	StrVec S1(s1);
	StrVec S2(S1);
	StrVec S3 = S1;
	S3.push_back("e");
	S1.print();
	S2.print();
	S3.print();
}
