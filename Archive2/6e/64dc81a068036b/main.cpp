#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>

#define NUM 3
#define TIME_TO_SLEEP 1

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


pthread_mutex_t GLOB_MUT = PTHREAD_MUTEX_INITIALIZER;

std::vector<int> some_resource {1};

void* function1(void*)
{
    std::cout << "Thread1 started" << std::endl;
    int i = 0;
    while (i < NUM)
    {
        ++i;
        pthread_mutex_lock(&GLOB_MUT);
        std::cout << "This is function1" << std::endl;
        some_resource.push_back(i*2);
        pthread_mutex_unlock(&GLOB_MUT);
        sleep(TIME_TO_SLEEP); // just to spice it up a little but don't do this ITW
    }
    pthread_exit(nullptr);
    return nullptr;
}

void* function2(void*)
{
    std::cout << "Thread2 started" << std::endl;
    int i = 0;
    while (i < NUM)
    {
        ++i;
        pthread_mutex_lock(&GLOB_MUT);
        std::cout << "This is function2" << std::endl;
        some_resource.push_back(i*7);
        pthread_mutex_unlock(&GLOB_MUT);
        sleep(TIME_TO_SLEEP); // just to spice it up a little but don't do this ITW
    }
    pthread_exit(nullptr);
    return nullptr;
}

int main()
{
    pthread_t t1,t2;

    pthread_create(&t1, NULL, &function1, NULL);
    pthread_create(&t2, NULL, &function2, NULL);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    std::cout << "Vec final " << some_resource << std::endl;
    pthread_exit(NULL);
    return 0;
}