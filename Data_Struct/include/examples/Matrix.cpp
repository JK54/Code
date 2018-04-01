#include "../Sparse_Matrix.h"

using namespace std;

int main()
{
	Sparse_Matrix aaa,bbb;
	ifstream is1("matrix1.txt");
	ifstream is2("matrix2.txt");
	aaa.Build_Matrix(is1);
	bbb.Build_Matrix(is2);
	aaa.Sort_X();
	aaa.Traverse();
	bbb.Sort_Y();
	bbb.Traverse();
	Sparse_Matrix result(aaa.X(),bbb.Y());
	aaa.Mutiply(bbb,result);
	result.Traverse();
}
