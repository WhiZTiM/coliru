#include <iostream>
 
class Widget {
public:
    Widget() { std::cout << "constructor\n"; }    
};

int main() {
    Widget w(); // No object is created, because it is a function declaration
}