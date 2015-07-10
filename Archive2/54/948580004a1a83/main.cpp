
#include <iostream>


class className {
    public:
    className(int k) : m(k){}
    
    className operator+=(className other)
    {
        className k(m);
        k.m += other.m;
        return k;        
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