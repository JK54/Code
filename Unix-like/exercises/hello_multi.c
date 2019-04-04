#include <stdio.h>
#include <pthread.h>

void *world()
{
	printf("world\n");
	return NULL;
}

void *hello()
{
	printf("hello\t");
	pthread_t t;
	pthread_create(&t,NULL,world,NULL);
	pthread_join(t,NULL);
	return NULL;
}

int main()
{
	pthread_t t;
	pthread_create(&t,NULL,hello,NULL);
	pthread_join(t,NULL);
}
