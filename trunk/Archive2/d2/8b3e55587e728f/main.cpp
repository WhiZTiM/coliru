
#include <iostream>


class className {
    public:
    className(int k) : m(k){}
    
    void operator+=(className other)
    {
        m += other.m;
    }
    
    void show() { std::cerr << m << std::endl; }
    
    private:
    int m;
};


int main(int argc, char *argv[])
{
    className k(10),m(20);
    k += m;
    k.show();
}