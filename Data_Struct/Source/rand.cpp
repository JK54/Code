/*
 * 作者：Pluto Hades
 * 链接：https://www.zhihu.com/question/20397465/answer/28102335
 * 来源：知乎
 * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 */
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
unsigned int GetRandom(int range)
{
	unsigned int rnum = 0;
#if defined _MSC_VER
#if defined _WIN32_WCE
	CeGenRandom(sizeof(int), (PBYTE)&rnum);
#else
	HCRYPTPROV hProvider = 0;
	const DWORD dwLength = sizeof(int);
	BYTE pbBuffer[dwLength] = {};
	DWORD result =::CryptAcquireContext(&hProvider, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	assert(result);
	result = ::CryptGenRandom(hProvider, dwLength, pbBuffer);
	rnum = *(int*)pbBuffer;
	assert(result);
	::CryptReleaseContext(hProvider, 0);
#endif
#elif defined __GNUC__
	int fd = open("/dev/urandom", O_RDONLY);
	if (fd != -1) 
	{
		(void) read(fd, (void *) &rnum, sizeof(int));
		(void) close(fd);
	}
#endif
	return rnum % range;
}

//p17
int main()
{
	std::ios::sync_with_stdio(false);
	int i,num1,num2,ran1,ran2;
	int a[2] = {50,30};
	int b[2] = {10,18};
	double result;
	for(i = 0,num1 = 0,num2 = 0;i < 5e5;i++)
	{
		ran1 = GetRandom(2);
		ran2 = GetRandom(a[ran1]);
		if(ran2 < b[ran1])
		{
			num1++;
			ran2 = GetRandom(a[ran1] - 1);
			if(ran2 < b[ran1] - 1)
				num2++;
		}
		if(i % 10000 == 0)
			std::cout<<i<<std::endl;
	}
	result = static_cast<double>(num2) / static_cast<double>(num1);
	std::cout<<result<<std::endl;
	return 0;
}

