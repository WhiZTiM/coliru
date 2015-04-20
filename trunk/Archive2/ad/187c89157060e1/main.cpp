#include <iostream>
#include <type_traits>

class MyClass {
private:
    int i;
public:
    MyClass(const MyClass& src) = delete;
    MyClass& operator=(const MyClass& rhs) = delete;    
    int getI() {
        return i;
    }
    MyClass(int _i) : i(_i){}
};

int main()
{
    std::cout << std::boolalpha << std::is_trivially_copyable< MyClass>::value << std::endl;

}