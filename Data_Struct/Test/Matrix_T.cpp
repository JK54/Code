#include "../Include/Sparse_Matrix_Trituple.hpp"

using namespace std;

int main()
{
	Sparse_Matrix_T<int> aaa,bbb;
	ifstream is("matrix1.txt");
	aaa.Init(is);
	aaa.Traverse();
	aaa.Transpose(bbb);
	bbb.Traverse();
}
