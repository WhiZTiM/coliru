#include <memory>
#include <thread>
#include <boost/asio.hpp>

void Func(boost::asio::ip::tcp::socket) {}

int main()
{
  boost::asio::io_service io_service;
  auto socket = std::make_shared<boost::asio::ip::tcp::socket>(
      std::ref(io_service));

  // Use a shim to move the socket to Func.
  std::thread func_thread([socket]() {
    return Func(std::move(*socket));
  });
  socket.reset();
  
  // Guarantee the io_service remains alive until after
  // its I/O objects have been destroyed.
  func_thread.join();
}
