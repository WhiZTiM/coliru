#include <chrono>
#include <iostream>
#include <stdio.h>
#include <functional>


using Milliseconds = std::chrono::duration<int, std::milli>;

class TimedTask {
  public:
    template<typename Fn, typename... Args>
    TimedTask(std::string name, Milliseconds sleep_duration, bool sleep_first, Fn& fn, Args&&... args) {
        std::cout << "Storing function " << name << std::endl;
        fn_ = std::bind(fn, std::forward<Args>(args)...);
    }
    
    template<typename Fn, typename... Args>
    TimedTask(std::string name, Milliseconds sleep_duration, Fn& fn, Args&&... args) {
        std::cout << "Storing function " << name << std::endl;
        fn_ = std::bind(fn, std::forward<Args>(args)...);
    }
    
    template<typename Fn, typename... Args>
    TimedTask(std::string name, Fn& fn, Args&&... args) {
        std::cout << "Storing function " << name << std::endl;
        fn_ = std::bind(fn, std::forward<Args>(args)...);
    }

    void Call() {
        fn_();
    }
    
  private:
    std::function<void(void)> fn_;
};

void print(std::string s) {
    std::cout << s << std::endl;
}

int main() {
    {
        auto task = TimedTask("Print Function", std::chrono::milliseconds(60000), false, print, "hello world");
        task.Call();
    }
    {
        auto task = TimedTask("Another Print Function", std::chrono::milliseconds(60000), print, "hi world");
        task.Call();
    }
    {
        auto task = TimedTask("Another Another Print Function", print, "hola world");
        task.Call();
    }
}