#include <iostream>

using namespace std;

//baseExecutor.h
class baseExecutor
{
    public:
    virtual bool execA() const = 0;

    private:
    virtual void execB() =0;
    virtual void execC()=0;
};

//Executor.h
class Executor : public baseExecutor
{
    public:
    virtual bool execA() const;
    virtual void execB(){std::cout << "B" << std::endl;}
    virtual void execC();
};

//Executor.cpp
bool Executor::execA() const
{
    return true;
}
void Executor::execC()
{
    std::cout << "C" << std::endl;
}

int main()
{
    return 0;
}