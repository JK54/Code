#include "comm.h"
using namespace std;

int main()
{
		class Debug
		{
		public:
				constexpr Debug(bool b = false,bool c = true):hw(c),io(b),other(b){}
				bool hw,io,other;
		};
		Debug ggg;
		cout<<ggg.hw<<ggg.io<<ggg.other<<endl;
		return 0;
}
