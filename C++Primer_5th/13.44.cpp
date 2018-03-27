#include "13.44.h"

using namespace std;

allocator<string>String::alloc;
int main()
{
	vector<String> evc;
	string tmp = "124asd";
	evc.push_back(tmp);
}
