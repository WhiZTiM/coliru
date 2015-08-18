#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <chrono>
#include <sstream>
#include <ctime>

std::vector<std::string>& getArray()
{
    static std::vector<std::string> v;
    return v;
}

void putStr(const std::string& str)
{
    std::stringstream ss;
    std::time_t ttp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    ss << str << "," << std::ctime(&ttp);
    getArray().push_back(ss.str());
}

void* thread_start(void *p)
{
    putStr(__FUNCTION__);
    sleep(4);
    return NULL;
}

struct StaticClass
{
    StaticClass()
    {
        putStr(__FUNCTION__);
        
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_t tid;

        sleep(3);
        pthread_create(&tid, &attr, &thread_start, nullptr);
        sleep(2);
    }
};

static StaticClass sc;

int main() {
    putStr(__FUNCTION__);
    const auto &bla = getArray();
    for ( const auto &i : bla )
        std::cout << i;
    return 0;
}
