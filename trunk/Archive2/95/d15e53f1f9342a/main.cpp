#include <iostream>
#include <string>

struct x
{
    int a;
    std::string b;
};

void SomeFunc(x& x_by_ref)
{
    std::cout << x_by_ref.b << std::endl;   
}

void StartFunc(x& x_by_ref)
{
    // Capture by value
    auto fails_to_capture = [x_by_ref]()
    {
        SomeFunc(x_by_ref);  
    };
    fails_to_capture();
}

int main()
{
    x hello {1, "123"};
    StartFunc(hello);
}
