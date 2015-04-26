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
  std::thread([socket]() {
    return Func(std::move(*socket));
  }).detach();
  socket.reset();
}
