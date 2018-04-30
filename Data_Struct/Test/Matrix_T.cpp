#include "../Include/Sparse_Matrix_Trituple.hpp"

using namespace std;

int main()
{
	Sparse_Matrix_T<int> aaa,bbb;
	ifstream is1("matrix1.txt");
	ifstream is2("matrix2.txt");
	aaa.Init(is1);
	aaa.Traverse();
	cout<<endl;
	aaa.Transpose(bbb);
	bbb.Traverse();
	cout<<endl;
	aaa.Add(bbb);
	aaa.Traverse();
}
