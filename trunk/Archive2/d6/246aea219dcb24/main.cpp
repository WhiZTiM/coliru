#include <iostream>
#include <type_traits>

using namespace std;

class MyClass
{};

template <typename Object>
class List
{
    
private:

template <bool B> class dispatcher {};
using ObjectPtr   = dispatcher<true>;
using ObjectValue = dispatcher<false>;

void M_insert(const Object &p, ObjectPtr) { /* Object is a pointer */ std::cout << "inserting pointer\n";  }
void M_insert(const Object &p, ObjectValue) { /* Object is not a pointer */ std::cout << "inserting non-pointer\n"; }

public:

    void insert(const Object & x)
    {
        M_insert(x, dispatcher<std::is_pointer<Object>::value> {});
    }

};

int main()
{
     List<MyClass*> l1;
     List<MyClass> l2;
     
     l1.insert( new MyClass{});
     l2.insert( MyClass{} );
    
}