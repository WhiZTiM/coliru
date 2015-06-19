#include <iostream>
#include <boost/thread.hpp>

int main()
{
  boost::thread thread(
                []() {
                    std::cout<<"hello\n";
                }
            );
    thread.join();
}
