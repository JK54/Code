#include "comm.h"

using namespace std;

class Example
{
public:
		static double rate;
		static constexpr int vecSize = 20;
		static vector<double>vec;
		Example() = default;
};
double Example::rate = 6.5;
int main()
{
		cout<<Example::vecSize<<endl;
}
