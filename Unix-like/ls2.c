#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

void do_f(char *name,void f(),int *llen,int *ulen,int *glen,int *slen);
void show_info(struct stat sta,char *name,int *llen,int *ulen,int *glen,int *slen);
void adjustlen(struct stat sta,char *name,int *llen,int *ulen,int *glen,int *slen);
void mode_to_letters(int ,char *);
char* uid_to_name(uid_t);
char* gid_to_name(uid_t);
int countlen(long long);

int main(int argc,char **argv)
{
	int llen,ulen,glen,slen;
	llen = ulen = glen = slen = 0;
	if(argc == 1)
	{
		do_f(".",adjustlen,&llen,&ulen,&glen,&slen);
		do_f(".",show_info,&llen,&ulen,&glen,&slen);
	}
	else
	{
		for(int i = 1;i < argc;i++)
			do_f(argv[i],adjustlen,&llen,&ulen,&glen,&slen);
		for(int i = 1;i < argc;i++)
			do_f(argv[i],show_info,&llen,&ulen,&glen,&slen);
	}
}

void do_f(char name[],void f(),int *llen,int *ulen,int *glen,int *slen)
{
	struct stat sta;
	if(stat(name,&sta) == -1)
		perror(name);
	else
	{
		if(S_ISREG(sta.st_mode))
			f(sta,name,llen,ulen,glen,slen);
		else if(S_ISDIR(sta.st_mode))
		{
			DIR *dir_ptr;
			struct dirent *dirp;
			if((dir_ptr = opendir(name)) == NULL)
			{
				perror(name);
				return;
			}
			while((dirp = readdir(dir_ptr)) != NULL)
			{
				char filename[100];
				sprintf(filename,"%s%c%s",name,'/',dirp->d_name);
				stat(filename,&sta);
				if(S_ISREG(sta.st_mode))
					f(sta,dirp->d_name,llen,ulen,glen,slen);
				else if(S_ISDIR(sta.st_mode))
					if((strncmp(dirp->d_name,".",1) && strncmp(dirp->d_name,"..",2)))
						do_f(filename,f,llen,ulen,glen,slen);
			}
			closedir(dir_ptr);
		}
	}
}

void show_info(struct stat sta,char *name,int *llen,int *ulen,int *glen,int *slen)
{
	char modeletter[] = "----------";
	char uname[100],gname[100],*timep;
	mode_to_letters(sta.st_mode,modeletter);
	strcpy(uname,uid_to_name(sta.st_uid));
	strcpy(gname,uid_to_name(sta.st_gid));
	timep = ctime(&sta.st_mtime);
	printf("%s ",modeletter);
	printf("%*ld ",*llen,sta.st_nlink);
	printf("%-*s ",*ulen,uname);
	printf("%-*s ",*glen,gname);
	printf("%*ld ",*slen,sta.st_size);
	/* printf("%.12s ",timep); */
	printf("%.12s ",4 + timep);
	printf("%s\n",name);
}

void adjustlen(struct stat sta,char *name,int *llen,int *ulen,int *glen,int *slen)
{
	int ll,uu,gg,ss;
	ll = countlen(sta.st_nlink);
	uu = strlen(uid_to_name(sta.st_uid));
	gg = strlen(gid_to_name(sta.st_gid));
	ss = countlen(sta.st_size);
	*llen = ll > *llen ? ll : *llen;
	*ulen = uu > *ulen ? uu : *ulen;
	*glen = gg > *glen ? gg : *glen;
	*slen = ss > *slen ? ss : *slen;
}

void mode_to_letters(int mode,char *letters)
{
	if(S_ISDIR(mode))
		letters[0] = 'd';
	else if(S_ISCHR(mode))
		letters[0] = 'c';
	else if(S_ISBLK(mode))
		letters[0] = 'b';
	if(mode & S_IRUSR)
		letters[1] = 'r';
	if(mode & S_IWUSR)
		letters[2] = 'w';
	if(mode & S_IXUSR)
		letters[3] = 'x';
	if(mode & S_IRGRP)
		letters[4] = 'r';
	if(mode & S_IWGRP)
		letters[5] = 'w';
	if(mode & S_IXGRP)
		letters[6] = 'x';
	if(mode & S_IROTH)
		letters[7] = 'r';
	if(mode & S_IWOTH)
		letters[8] = 'w';
	if(mode & S_IXOTH)
		letters[9] = 'x';
}

char* uid_to_name(uid_t uid)
{
	struct passwd *pd;
	if((pd = getpwuid(uid)) == NULL)
	{
		static char numstr[10];
		sprintf(numstr,"%d",uid);
		return numstr;
	}
	else
		return pd->pw_name;
}

char* gid_to_name(gid_t gid)
{
	struct group *gp;
	if((gp = getgrgid(gid)) == NULL)
	{
		static char numstr[10];
		sprintf(numstr,"%d",gid);
		return numstr;
	}
	else
		return gp->gr_name;
}

int countlen(long long size)
{
	int len = 0;
	while(size)
	{
		len++;
		size /= 10;
	}
	return len;
}

