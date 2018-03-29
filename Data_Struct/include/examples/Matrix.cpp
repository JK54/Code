#include "../Sparse_Matrix.h"

using namespace std;

int main()
{
	Sparse_Matrix aaa,bbb;
	ifstream is1("matrix.txt");
	ifstream is2("matrix.txt");
	aaa.Build_Matrix(is1);
	bbb.Build_Matrix(is2);
	aaa.Traverse();
	bbb.Traverse();
	Sparse_Matrix result(aaa.X(),bbb.Y());
	aaa.Mutiply(bbb,result);
	result.Traverse();
}
