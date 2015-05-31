#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

int main ()
{
  boost::asio::io_service io_service;

  boost::asio::spawn(io_service,
    [&io_service](boost::asio::yield_context yield_context) {
      boost::asio::deadline_timer timer(io_service);
      timer.expires_from_now(boost::posix_time::seconds(1));
      std::cout << "Start wait" << std::endl;
      timer.async_wait(yield_context);
      std::cout << "Woke up" << std::endl;
    });

  io_service.post([] {
    std::cout << "Other work" << std::endl;
  });

  io_service.run();
}