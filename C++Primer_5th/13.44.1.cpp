#include "13.44.h"

using namespace std;
allocator<string>String::alloc;
int main()
{
	String i("asd");
	String j("asfsgdfsgdg");
	j = i;
}
