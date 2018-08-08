#include "../Include/BSTree.hpp"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

int main()
{
	int fd = open("/dev/urandom",O_RDONLY);
	unsigned int arr2[1399999];
	read(fd,&arr2[0],sizeof(int));
	// BSTree<int> aaa(arr2[0]);
	BSTree<int> aaa(0);
	for(int i = 1 ;i < 1399999;i++)
	{
		/*
		 * read(fd,&arr2[i],sizeof(int));
		 * while(aaa.Search(arr2[i]))
		 * {
		 *     read(fd,&arr2[i],sizeof(int));
		 * }
		 */
		aaa.Insert(i);
	}
	for(int i = 0;i < 1399999;i++)
		aaa.Remove(i);
	cout<<endl;
	close(fd);
}
