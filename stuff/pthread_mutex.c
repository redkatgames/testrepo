#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];
static pthread_mutex_t lock;

void* doSomeThing(void *arg)
{
    pthread_mutex_lock(&lock);

    unsigned long i = 0;
    printf("\n Job started\n");

    for(i=0; i<(0xFFFFFF);i++);

    printf("\n Job finished\n");

    pthread_mutex_unlock(&lock);

    return NULL;
}


void* doSomeThing2(void *arg)
{
    pthread_mutex_lock(&lock);

    unsigned long i = 0;
    printf("\n Job something2 started\n");

    for(i=0; i<(0xFFFFFF);i++);

    printf("\n Job something2 finished\n");

    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void)
{
    int i = 0;
    int err;

    //if (pthread_mutex_init(&lock, NULL) != 0)
    //{
    //    printf("\n mutex init failed\n");
    //    return 1;
    //}

        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));


        err = pthread_create(&(tid[i]), NULL, &doSomeThing2, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);

    return 0;
}
