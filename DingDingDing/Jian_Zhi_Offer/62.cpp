#include <iostream>

//约瑟夫环推导过程：
//1）将上一轮剩余的序列f'(n-1,m)从本轮开始的数字k + 1（上一轮被剔除的数字序号为k)开始，映射为从0开始的序列f(n-1,m)，映射关系为p(x) = (x - k - 1) % n，逆映射关系为p-1(x) = (x + k + 1) % n.
//2）显然，存在递推关系f(n,m) = f'(n - 1,m)
//3) n为序列长度，m为顺序第m个数字，为两个数的间隔加1，在计算的时候不需要减1.
//
//   f'(n - 1,m) = p-1{f(n - 1,m)} }                                                                                                a%n%n=a%n
//                                 }==>  f(n,m) = p-1{f(n - 1,m)} = (f(n - 1,m) + k + 1) % n }==>(f(n - 1,m) + (m - 1) % n + 1) % n ===============> (f(n - 1,m) + m) % n
//     f(n,m) = f'(n - 1,m)        }                                        k = (m - 1) % n  }                        				a%n+b%n=(a+b)%n
//
// 推导完成，得到递推式 f(n,m) = {       0				,n = 1
// 								 {(f(n - 1,m) ) m) % n  ,n > 1
//	
int Josephus(int n,int m)
{
	if(n < 1 || m < 1)
		return -1;
	int last = 0;
	for(int i = 2;i <= n;i++)
		last = (last + m) % i;
	return last;
}

int main()
{
	int nums,wd;
	nums = 5;
	wd = 3;
	std::cout<<Josephus(nums,wd)<<std::endl;
}
