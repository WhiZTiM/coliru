#include <stdio.h>
#include <cstring>
#include <map>
#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include <memory>


class Top {
  public:
    class Nested {
      public:
        void print() {
            std::cout << "hello world" << std::endl;
        }
    };
    
    Top() {
        nested_ = std::unique_ptr<Nested>(new Nested());
        t_ = new std::thread(&Nested::print, nested_.get());
    }
    
    ~Top() {
        t_->join();
    }
    
  private:
    std::thread* t_;
    std::unique_ptr<Nested> nested_;
};

int main()
{
    Top top;
}