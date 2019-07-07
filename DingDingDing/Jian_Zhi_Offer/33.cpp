#include <iostream>

bool isbst(int seq[],int len)
{
	if(seq == nullptr)
		return false;
	if(len == 1 || len == 0)
		return true;
	int rootpos = len - 1;
	int departpos;
	for(departpos = 0;departpos < len && seq[departpos] < seq[rootpos];departpos++);
	for(int j = departpos;j < rootpos;j++)
		if(seq[j] < seq[rootpos])
			return false;

	return isbst(seq,departpos) && isbst(seq + departpos,len - departpos - 1);
}

int main()
{
	int a[] = {5,7,6,9,11,10,8};
	int b[] = {7,4,6,5};
	int c[] = {1,3,2,5,6,7,4,11,10,15,14,13,12,8};
	int as = sizeof(a) / sizeof(a[0]);
	int bs = sizeof(b) / sizeof(b[0]);
	int cs = sizeof(c) / sizeof(c[0]);
	std::cout<<isbst(a,as)<<std::endl;
	std::cout<<isbst(b,bs)<<std::endl;
	std::cout<<isbst(c,cs)<<std::endl;
	return 0;
}
