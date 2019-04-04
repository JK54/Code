#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>

int c0 = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *f0()
{
	while(c0 < 100)
	{
		pthread_mutex_lock(&lock);
		c0++;
		printf("0");
		pthread_mutex_unlock(&lock);
	}
	pthread_cond_signal(&cond);
	return NULL;
}

void *f1()
{
	while(c0 < 100)
	{
		pthread_mutex_lock(&lock);
		c0++;
		printf("1");
		pthread_mutex_unlock(&lock);
	}
	pthread_cond_signal(&cond);
	return NULL;
}

int main()
{
	pthread_t t0,t1;
	pthread_mutex_lock(&lock);
	pthread_create(&t0,NULL,f0,NULL);
	pthread_create(&t1,NULL,f1,NULL);
	pthread_cond_wait(&cond,&lock);
	pthread_join(t0,NULL);
	pthread_join(t1,NULL);
	printf("\n");
}
