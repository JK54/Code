#include "../Include/Forest.hpp"

using namespace std;

int main()
{
	ifstream is("./forest.txt");
	ifstream is2("./forest.txt");
	Forest<int> fff;
	fff.CreateForest(is);
	fff.BFS();
	getchar();
}
