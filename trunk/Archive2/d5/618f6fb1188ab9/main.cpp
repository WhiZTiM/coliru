#include <iostream>
#include <string>
#include <vector>

#include <iostream>
#include <system_error>

#include <boost/thread.hpp>

#include <thread>

void wait(int seconds)
{
  boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
}

void thread()
{
  for (int i = 0; i < 5; ++i)
  {
    wait(1);
    std::cout << i << '\n';
  }
}

int main()
{
  boost::thread t; //{thread};
  std::cout << "Thread created.\n";
  std::cout << "Thread is joinable: " << t.joinable() << "\n";
  //std::cout << "Thread ID: " << t.joinable() << "\n";
  
  //t.interrupt();
  
  try
  {
      //t.detach();
      t.join();
      std::cout << "Join OK.\n";
  }
  catch ( const std::system_error e )
  {
      std::cout << "Exception caught: " << e.what();
  }
}
