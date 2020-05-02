#include "../include/myapue.h"

#define MAXCOUNT 256
#define MAXSIZE  2048
#define AVG      10
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

volatile int32_t round_flag = 1;
volatile int32_t profit_point = 1;
volatile int32_t profit = 0;
volatile int32_t write_cost = 0;
volatile int32_t writev_cost = 0;

struct iovec buf[MAXCOUNT];
int trash_fd;

int time_diff(struct timeval &begin, struct timeval &end)
{
    int secs = end.tv_sec - begin.tv_sec;
    int usecs = end.tv_usec - begin.tv_usec;
    return secs * 1000000 + usecs;
}

void *thr_fn1_write(void *arg)
{
    struct timeval begin;
    struct timeval end;
    while (profit_point <= MAXCOUNT)
    {
        int32_t size = profit_point * MAXSIZE;
        gettimeofday(&begin, nullptr);
        char *tmp_buf = new char [size];
        for (int i = 0;i < profit_point;++i)
        {
            memcpy(&tmp_buf[i * MAXSIZE], buf[i].iov_base, MAXSIZE);
        }
        if (write(trash_fd, tmp_buf, size) != size)
        {
            printf("write error\n");
            exit(1);
        }
        gettimeofday(&end, nullptr);
        //For fair competition, do not count the time of memory delete.
        //because the buffer of writev has been allocated before test
        delete [] tmp_buf;
        write_cost = time_diff(begin, end);
        printf("write\t%d\t%d\t%d\n", MAXSIZE, profit_point, write_cost);

        pthread_mutex_lock(&mtx);
        while (round_flag == 1 && profit_point <= MAXCOUNT)
        {
            pthread_cond_wait(&cond, &mtx);
        }
        round_flag = 2;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);
    }
    return nullptr;
}

void *thr_fn2_writev(void *arg)
{
    struct timeval begin;
    struct timeval end;
    while (profit_point <= MAXCOUNT)
    {
        int32_t size = profit_point * MAXSIZE;
        gettimeofday(&begin, nullptr);
        char *tmp_buf = new char [size];
        for (int i = 0;i < profit_point;++i)
        {
            memcpy(&tmp_buf[i * MAXSIZE], buf[i].iov_base, MAXSIZE);
        }
        for (int i = 0;i < AVG;++i)
        {
            if (write(trash_fd, tmp_buf, size) != size)
            {
                printf("write error\n");
                exit(1);
            }
        }
        gettimeofday(&end, nullptr);
        //For fair competition, do not count the time of memory delete.
        //because the buffer of writev has been allocated before test
        delete [] tmp_buf;
        write_cost = time_diff(begin, end) / AVG;
        printf("write\t%d\t\t%d\t%d\n", MAXSIZE, profit_point, write_cost);

        gettimeofday(&begin, nullptr);
        for (int i = 0; i < AVG;++i)
        {
            if (writev(trash_fd, buf, profit_point) != profit_point * MAXSIZE)
            {
                printf("write error\n");
                exit(1);
            }
        }
        gettimeofday(&end, nullptr);
        writev_cost = time_diff(begin, end) / AVG;
        
        profit = write_cost - writev_cost;
        printf("writev\t%d\t\t%d\t%d\n", MAXSIZE, profit_point, writev_cost);
        pthread_mutex_lock(&mtx);
        while (round_flag == 2 && profit <= MAXCOUNT)
        {
            pthread_cond_wait(&cond, &mtx);
        }
        round_flag = 1;
        ++profit_point;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);
    }
    return nullptr;
}

int main()
{
    pthread_t th1;
    pthread_t th2;
    
    if ((trash_fd = open("out.txt", O_RDWR | O_CREAT | O_EXCL, 0644)) < 0)
    {
        perror("open /dev/null");
        return 1;
    }
    unlink("out.txt");
    for(int i = 0;i < MAXCOUNT;++i)
    {
        buf[i].iov_len = MAXSIZE;
        buf[i].iov_base = new char [MAXSIZE];
        memset(buf[i].iov_base, 'a', MAXSIZE);
    }
    printf("Method\tBUFSIZ(B)\tCount\tTime(us)\n");
    // thr_fn2_writev(nullptr);
    if (pthread_create(&th1, nullptr, &thr_fn1_write, nullptr))
    {
        perror("pthread_create");
        return 1;
    }
    if (pthread_create(&th2, nullptr, &thr_fn2_writev, nullptr))
    {
        perror("pthread_create");
        return 1;
    }
    
    pthread_join(th1, nullptr);
    pthread_join(th2, nullptr);
    for(int i = 0;i < MAXCOUNT;++i)
    {
        delete [] reinterpret_cast<char*>(buf[i].iov_base);
    }
    return 0;
}
