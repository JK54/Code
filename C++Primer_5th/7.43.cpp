#include "comm.h"

using namespace std;

int main()
{
		class NoDeFault
		{
		public:
			//	NoDeFault(int i);
				int i;
		};
		class C
		{
		public:
				C()=default;
				NoDeFault Ci;
		};
		C iav;
		cout<<iav.Ci.i<<endl;
		return 0;
}
