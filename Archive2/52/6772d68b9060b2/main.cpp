#include <iostream>


struct Integer
{
    static Integer& getInstance() // there is only one Integer
    {
        static Integer fLogger;
        return fLogger;
    }
    
    operator int&() const
    {
        return *n;
    }
    
private:
    Integer() : n(new int()) { }
    Integer(const Integer&) = delete;
    Integer& operator=(const Integer&) = delete;
    ~Integer() { delete n; n = nullptr; }
    int* n;
};



struct Foo
{    
    ~Foo()
    {
        std::cout << Integer::getInstance()++ << std::endl;
    }
};


Foo foo;


int main()
{
    // program crashes if I uncomment this line: 
    //std::cout << Integer::getInstance()++ << std::endl;
}

