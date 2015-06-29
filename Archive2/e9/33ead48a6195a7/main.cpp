#include <stdio.h>
#include <cstring>
#include <map>
#include <iostream>
#include <string>
#include <thread>
#include <functional>


class A {
  public:
    class B {
      public:
        void print() {
            std::cout << "hello world" << std::endl;
        }
    };
    
    A() {
        b = new B();
        t = new std::thread(&B::print, b);
    }
    
    ~A() {
        t->join();
    }
    
    std::thread* t;
    B* b;
};

int main()
{
    A a;
}