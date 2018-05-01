#include "../Include/Sparse_Matrix_Trituple.hpp"

using namespace std;

int main()
{
	Sparse_Matrix_T<int> aaa,bbb,ccc;
	ifstream is1("matrix1.txt");
	ifstream is2("matrix2.txt");
	aaa.Init(is2);
	aaa.Traverse();
	cout<<endl;
	// bbb.Init(is2);
	aaa.Transpose(bbb);
	bbb.Traverse();
	cout<<endl;
	aaa.Multiply(bbb,ccc);
	ccc.Traverse();
}
