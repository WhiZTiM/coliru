#include <pthread.h>
#include <vector>
#include <iostream>
#include <chrono>
#include <sstream>
#include <ctime>
#include <thread>

std::vector<std::string>& getLog()
{
    static std::vector<std::string> v;
    return v;
}

void sleep(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void log(const std::string& str)
{
    std::stringstream ss;
    std::time_t ttp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    ss << "Function:" << str << "\tThread Id:" << pthread_self() << "\tTime:" << std::ctime(&ttp);
    getLog().push_back(ss.str());
}

void* thread_start(void *p)
{
    log(__FUNCTION__);
    sleep(4);
    log(__FUNCTION__);
    return NULL;
}

class StaticClass
{
public:
    StaticClass()
    {
        log(__FUNCTION__);
        
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        sleep(3);
        pthread_create(&_tid, &attr, &thread_start, nullptr);
        sleep(2);
        log(__FUNCTION__);
    }
    pthread_t tid() const
    {
        return _tid;
    }
private:
    pthread_t _tid;
};

static const StaticClass sc;

int main() {
    log(__FUNCTION__);
    pthread_join(sc.tid(), nullptr);
    for ( const auto &i : getLog() )
        std::cout << i;    
    return 0;
}
