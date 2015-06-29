#include <stdio.h>
#include <cstring>
#include <map>
#include <iostream>
#include <string>
#include <thread>
#include <functional>


class Top {
  public:
    class Nested {
      public:
        void print() {
            std::cout << "hello world" << std::endl;
        }
    };
    
    Top() {
        nested_ = new Nested();
        t_ = new std::thread(&Nested::print, nested_);
    }
    
    ~Top() {
        t_->join();
    }
    
  private:
    std::thread* t_;
    Nested* nested_;
};

int main()
{
    Top top;
}