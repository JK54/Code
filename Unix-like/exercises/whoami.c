#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

int main()
{
	uid_t id;
	struct passwd *pbuf;
	id = geteuid();//unistd.h
	pbuf = getpwuid(id);//pwd.h
	printf("%s\n",pbuf->pw_name);
	return 0;
}
