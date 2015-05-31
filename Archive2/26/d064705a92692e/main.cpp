#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

boost::asio::io_service io_service;

void other_work()
{
  std::cout << "Other work" << std::endl;
}

void my_work(boost::asio::yield_context yield_context)
{
  // Add more work to the io_service.
  io_service.post(&other_work);
    
  // Wait on a timer within the coroutine.
  boost::asio::deadline_timer timer(io_service);
  timer.expires_from_now(boost::posix_time::seconds(1));
  std::cout << "Start wait" << std::endl;
  timer.async_wait(yield_context);
  std::cout << "Woke up" << std::endl;    
}

int main ()
{
  boost::asio::spawn(io_service, &my_work);
  io_service.run();
}