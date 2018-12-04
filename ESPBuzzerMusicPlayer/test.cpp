#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void* f(void*);

int ourcounter = 0;

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, nullptr, &f, (void*)"Thread 1");
    pthread_create(&t2, nullptr, &f, (void*)"Thread 2");

    while(true)
    {
        printf("Main process(%d)\n", ourcounter);
        ourcounter++;
        sleep(1);
    }

    return 0;
}



void* f(void* str)
{   
    int mycounter = 0;

    while(true)
    {
        printf("%s(%d)\n", (char*)str, mycounter++);
        ourcounter++;
        sleep(1);
    }
}