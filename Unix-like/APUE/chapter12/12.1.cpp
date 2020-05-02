#include "../include/myapue.h"

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare()
{
    int err;
    printf("preparing locks...\n");
    if ((err = pthread_mutex_lock(&lock1)))
    {
        perror("can't lock lock1 in prepare handler");
        return;
    }
    if ((err = pthread_mutex_lock(&lock2)))
    {
        perror("can't lock lock2 in prepare handler");
        return;
    }
}

void parent()
{
    int err;
    printf("parent unlocking locks\n");
    if ((err = pthread_mutex_unlock(&lock1)))
    {
        perror("can't unlock lock1 in parent handler");
        return;
    }
    if ((err = pthread_mutex_unlock(&lock2)))
    {
        perror("can't lock lock2 in parent handler");
        return;
    }

}

void child()
{
    int err;
    printf("child unlocking locks\n");
    if ((err = pthread_mutex_unlock(&lock1)))
    {
        perror("can't unlock lock1 in child handler");
        return;
    }
    if ((err = pthread_mutex_unlock(&lock2)))
    {
        perror("can't lock lock2 in child handler");
        return;
    }
}

void *thr_fn(void *arg)
{
    printf("thread started...\n");
    pause();
    return nullptr;
}

int main()
{
    int err;
    pid_t pid;
    pthread_t tid;
    if ((err = pthread_atfork(prepare, parent, child)))
    {
        perror("pthread_atfork");
        return 1;
    }
    if ((err = pthread_create(&tid, nullptr, thr_fn, nullptr)))
    {
        perror("cannot create thread");
        return 1;
    }
    sleep(1);
    printf("parent about to fork\n");
    if ((pid = fork()) < 0)
    {
        perror("fork");
        return 1;
    }
    else if (pid == 0)
    {
        printf("child returned from fork\n");
    }
    else
    {
        printf("parent returned from fork\n");
    }
    return 0;
}
