#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class MyError : public runtime_error
{
public:
    MyError(string mess = "");
    ~MyError(void);
};

MyError::MyError(string mess) : runtime_error(mess)
{
    cout << "MyError::MyError()\n";
}

MyError::~MyError(void)
{
    cout << "MyError::~MyError\n";
}

int main(void)
{
    try {
        throw MyError("hi");
    }
    catch (MyError& exc) {
        cout << exc.what() << endl;
    }

    cout << "goodbye\n";
    return 0;
}