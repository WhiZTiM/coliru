#include <iostream>
#include <unistd.h>
#include <sys/time.h>

class timer
{ 
private:
    double startTime;
    
    double getTime()
    {
       timeval tv;
       gettimeofday(&tv, 0);
       return tv.tv_sec + tv.tv_usec/1e9;
    }
    
public:
    void start()
    {
        startTime = getTime(); 
    }

    double elapsedTime()
    { 
        return getTime() - startTime;
    }
    
    bool isTimeout(double seconds) {
        return seconds >= elapsedTime();
    }
};

int main()
{
    timer t;
    t.start();
    
    sleep(5);
    
    std::cout << t.elapsedTime() << '\n';
}
