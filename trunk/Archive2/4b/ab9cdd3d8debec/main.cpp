
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_start(void *p)
{
    fprintf(stderr, "static started: tid:%u\n", (int)pthread_self());
    return NULL;
}

class A
{
public:
    A() : tid(0)
    {
        fprintf(stderr, "launching static thread from tid:%u\n", (int)pthread_self());
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr,
                           &thread_start, NULL);
    }
private:
    pthread_t tid;
    pthread_attr_t attr;
};

static A a;

int main() {
    fprintf(stderr, "main started tid:%u\n", (int)pthread_self());
    sleep(2);
    return 0;
}
