#include "comm.h"
#include <array>
#include <fstream>
using namespace std;

class ptr
{
	public:
		ptr():pp(new int(1)){}
		~ptr()
		{
			delete pp;
		}

		 int getv(){return *pp;}
	private:
		int *pp;
};


ptr f(ptr pr)
{
	auto m = pr;
	return m;
}

int main()
{
	ptr pp;
	cout<<pp.getv()<<endl;
	auto m = f(pp);
	cout<<pp.getv()<<endl;
	cout<<m.getv()<<endl;
}
