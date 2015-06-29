#include <atomic>
#include <memory>
#include <thread>
#include <iostream>

typedef std::atomic<int>  satomic;
#define FOR(I) for (size_t ix = 0 ; ix < I; ix++)

void dec(satomic& a)
{
    FOR(1000)
        a--;
}

void inc(satomic& a)
{
    FOR(1000)
        a++;
}

int main(int argc, char* argv[])
{
    std::thread inc_t_[1000], dec_t_[1000];
    satomic a(0);
    
    FOR(1000)
    {
        inc_t_[ix] = std::thread(&inc,std::ref(a));
        dec_t_[ix] = std::thread(&dec,std::ref(a));
    }
    
    FOR(1000)
    {
        inc_t_[ix].join();
        dec_t_[ix].join();
    }
    
    std::cerr << a.load() << std::endl;

    return 0;
}