#include <iostream>

class MyClass
{

public:

    int getI()
    {
        std::cout << "non-const getter" << std::endl;
        return privateGetI<MyClass, int>(*this);
    }
    
    const int getI() const
    {
        std::cout << "const getter" << std::endl;
        return privateGetI<const MyClass,const int>(*this);
    }
    
private:

    template <class C, typename T>
    static T privateGetI(C c)
    {
        //do my stuff
        return c._i;
    }

    int _i;
};

int main()
{
    const MyClass myConstClass = MyClass();
    myConstClass.getI();
    
    MyClass myNonConstClass;
    myNonConstClass.getI();
    
    return 0;
}