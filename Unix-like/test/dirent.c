#include <stdio.h>
#include <dirent.h>

int main()
{
	DIR *dir;
	struct dirent *dirp;
	dir = opendir("..");
	dirp = readdir(dir);
	closedir(dir);
	printf("%s\n",dirp->d_name);
}
