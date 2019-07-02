#include <cstdio>
#include <iostream>

using namespace std;

const int MOD = 10000;

struct matrix//定义矩阵结构体
{
    int m[2][2];
}ans, base;

matrix multi(matrix a, matrix b)//定义矩阵乘法
{
    matrix tmp;
    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 2; ++j)
        {
            tmp.m[i][j] = 0;
            for(int k = 0; k < 2; ++k)
                tmp.m[i][j] = (tmp.m[i][j] + a.m[i][k] * b.m[k][j]) % MOD;
        }
    }
    return tmp;
}
int fast_mod(int n)  // 求矩阵 base 的  n 次幂 
{
    base.m[0][0] = base.m[0][1] = base.m[1][0] = 1;
    base.m[1][1] = 0;
    ans.m[0][0] = ans.m[1][1] = 1;  // ans 初始化为单位矩阵 
    ans.m[0][1] = ans.m[1][0] = 0;
    while(n)
    {
        if(n & 1)  //实现 ans *= t; 其中要先把 ans赋值给 tmp，然后用 ans = tmp * t 
            ans = multi(ans, base);

        base = multi(base, base);
        n >>= 1;
    }
    return ans.m[0][1];
}

int main()
{
    int n;
    while(scanf("%d", &n) && n != -1)
    {   
        printf("%d\n", fast_mod(n));
    }
    return 0;
}

//https://www.zhihu.com/question/28062458
