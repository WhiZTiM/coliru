#include <future>
#include <functional>
#include <thread>
#include <utility>
#include <iostream>

    struct Ftor {
      int operator()()const{return 7;}
    };
    
    struct Solver
    {
      Solver(Ftor&& task)
      {
        std::thread thread(&Solver::thread_function, std::move(task));
      }
    
      void thread_function(Ftor&& task)
      {}
    };
    
    
    int main() {
      Ftor s;
      Solver solver(std::move(s));
    }
    
