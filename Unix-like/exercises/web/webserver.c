#include "webserver.h"

void read_request(int fd,char *buffer,int size)
{
	memset(buffer,'\0',size);
	if(read(fd,buffer,BUFSIZ) == -1)
		oops("read quest");
}

char* newstr(char *source,int pos,int len)
{
	char *res = malloc(len + 1);
	if(res == NULL)
		oops("malloc");
	strncpy(res,source + pos,len);
	return res;
}

char** split_args(char *buf)
{
	char **args;
	int ps,pe,count;
	int len = strlen(buf);
	args = malloc(BUFSIZ);
	pe = 0;
	count = 0;
	while(pe < len)
	{
		while(pe < len && isblank(buf[pe]))
			pe++;
		if(pe == len)
			break;
		ps = pe;
		while(pe < len && !isblank(buf[pe]))
			pe++;
		args[count++] = newstr(buf,ps,pe - ps);
	}
	args[count] = NULL;
	return args;
}

void freelist(char **buf)
{
	char **tmp = buf;
	while(*tmp != NULL)
		free(*tmp++);
	free(buf);
}

void header(int fd,char *content_type)
{
	char buf[BUFSIZ] = "HTTP/1.0 200 OK\r\n";
	if(content_type != NULL)
	{
		strncat(buf,"Content-type : ",strlen("Content-type : "));
		strncat(buf,content_type,strlen(content_type));
		strncat(buf,"\r\n",strlen("\r\n"));
	}
	write(fd,buf,strlen(buf));
}

void error_404(int fd,char *item)
{
	char buf[BUFSIZ] = "HTTP/1.0 404 Not Found\r\nContent-type : text/plain\r\n\r\nThe item you requested : ";
	strncat(buf,item,strlen(item));
	strncat(buf," is not found\r\n",strlen(" is not found\r\n"));
	write(fd,buf,strlen(buf));
}

void error_501(int fd)
{
	char buf[] = "HTTP/1.0 501 Not Implement\r\nContent-type : text/plain\r\n\r\nThat command is not yet implement\r\n";
	write(fd,buf,strlen(buf));
}

bool is_exist(char *name)
{
	struct stat info;
	return (stat(name,&info) != -1);
}

bool is_dir(char *name)
{
	struct stat info;
	return (stat(name,&info) != -1 && S_ISDIR(info.st_mode));
}

char* file_type(char *name)
{
	char *file_extension_name;
	if((file_extension_name = strrchr(name,'.')) != NULL)
		return file_extension_name + 1;
	return "";
}

bool is_cgi(char *name)
{
	char *type = file_type(name);
	return (strlen(type) == 3 && strncmp(type,"cgi",3) == 0);
}

void do_ls(int fd,char *dirname)
{
	if(dup2(fd,STDOUT_FILENO) == -1 || dup2(fd,STDERR_FILENO) == -1)
		oops("do_ls : dup2");
	close(fd);
	header(STDOUT_FILENO,"text/plain");
	write(STDOUT_FILENO,"\r\n",2);
	execlp("ls","ls","-l",dirname,NULL);
	oops(dirname);
}

void do_cat(int fd,char *filename)
{
	char *exten = file_type(filename);
	int extlen = strlen(exten);
	char *content = "text/plain";
	char buf[BUFSIZ];
	int namelen = strlen(filename) + strlen("./") + 1;
	char pathname[namelen];
	FILE *fp;
	
	if(extlen == 4 && strncmp(exten,"html",4) == 0)
		content = "text/html";
	else if(extlen == 4 && strncmp(exten,"jpeg",3) == 0)
		content = "image/jpeg";	
	else if(extlen == 3 && strncmp(exten,"gif",3) == 0)
		content = "image/gif";
	else if(extlen == 3 && strncmp(exten,"jpg",3) == 0)
		content = "image/jpg";	

	header(fd,content);
	write(fd,"\r\n",2);

	memset(pathname,'\0',namelen);
	snprintf(pathname,namelen,"./%s",filename);
	fp = fopen(pathname,"r");
	memset(buf,'\0',BUFSIZ);
	while(fread(buf,sizeof(char),BUFSIZ,fp) != 0)
	{
		write(fd,buf,strlen(buf));
		memset(buf,'\0',BUFSIZ);
	}
	fclose(fp);
}

void do_exec(int fd,char *prog)
{
	int len = strlen(prog) + 3;
	int pid;
	char pathname[len];
	memset(pathname,'\0',len);
	snprintf(pathname,len,"./%s",prog);
	if((pid = fork()) == -1)
		oops("fork");
	if(pid == 0)
	{
		if(dup2(fd,STDOUT_FILENO) == -1 || dup2(fd,STDERR_FILENO) == -1)
			oops("do_exec : dup2");
		execl(pathname,pathname,NULL);
		oops("execl");
	}
}

