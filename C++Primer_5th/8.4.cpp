#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

int main(int argc,char **argv)
{
		vector<string> vec;
		for(auto i = argv + 1;i != argv + argc - 1; ++i)
		{
				ifstream input(*i);
				ofstream output(*(argv + argc - 1),ofstream::app);
				if(input)
				{
						string tmp;
						while(input>>tmp)
						{
								vec.push_back(tmp);
								output<<tmp<<endl;
								cout<<tmp<<endl;
						}
				}
				else
						cerr<<"couldn't open :"+string(*i)<<endl;
		}
		return 0;
}
