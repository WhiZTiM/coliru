#define BOOST_ASIO_ENABLE_HANDLER_TRACKING

#include <iostream>
#include <thread>

#include <boost/asio.hpp>

int main()
{
  namespace asio = boost::asio;

  asio::io_service ios;

  asio::ip::udp::endpoint ep(boost::asio::ip::udp::v4(), 9876);
  auto socket = new asio::ip::udp::socket(ios, ep);
  std::thread th([&]
  {
      ios.dispatch([]{ std::cout << "before run()" << std::endl;});
      ios.run();
      std::cout << "after run()" << std::endl;
  });

  std::this_thread::sleep_for(std::chrono::seconds(5)); // wait for io_service to launch

  socket->cancel();
  socket->close();
  delete socket; // just in case

  std::cout << "socket is closed" << std::endl;

  th.join(); // hangs here

  std::cout << "exiting..." << std::endl;
}
