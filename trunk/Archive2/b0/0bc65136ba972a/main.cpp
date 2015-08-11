#include <array>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

// This example is not interested in the handlers, so provide a noop function
// that will be passed to bind to meet the handler concept requirements.
void noop() {}

void print_status(
  const boost::system::error_code& error,
  std::size_t bytes_transferred)
{
  std::cout << "error = (" << error << ") " << error.message() << "; "
               "bytes_transferred = " << bytes_transferred
            << std::endl;
}

int main()
{
  using boost::asio::ip::tcp;

  // Create all I/O objects.
  boost::asio::io_service io_service;
  tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 0));
  tcp::socket socket1(io_service);
  tcp::socket socket2(io_service);

  // Connect the sockets.
  acceptor.async_accept(socket1, boost::bind(&noop));
  socket2.async_connect(acceptor.local_endpoint(), boost::bind(&noop));
  io_service.run();
  io_service.reset();

  std::array<char, 512> buffer;

  // Scenario: async_receive when socket has no data.
  //   Within the intiating asynchronous read function, an attempt to read
  //   data will be made.  If it fails, it will be added to the reactor,
  //   for monitoring where it can be cancelled.
  {
    std::cout << "Scenario: async_receive when socket has no data" 
              << std::endl;
    socket1.async_receive(boost::asio::buffer(buffer), &print_status);
    socket1.cancel();
    io_service.run();
    io_service.reset();
  }

  // Scenario: async_receive when socket has data.
  //   The operation will complete within the initiating function, and is
  //   not available for cancellation.
  {
    std::cout << "Scenario: async_receive when socket has data" << std::endl;
    boost::asio::write(socket2, boost::asio::buffer("hello"));
    socket1.async_receive(boost::asio::buffer(buffer), &print_status);
    socket1.cancel();
    io_service.run();
  }
  // One can also get the same behavior with synchronous operations by
  // enabling non_blocking mode.
  boost::system::error_code error;
  std::size_t bytes_transferred = 0;
  socket1.non_blocking(true);

  // Scenario: non-blocking synchronous read when socket has no data.
  {
    std::cout << "Scenario:  non-blocking synchronous read when socket"
                 " has no data." << std::endl;
    bytes_transferred = socket1.receive(
        boost::asio::buffer(buffer), 0 /* flags */, error);
    assert(error == boost::asio::error::would_block);
    print_status(error, bytes_transferred);
  }

  // Scenario: non-blocking synchronous read when socket has data.
  {
    std::cout << "Scenario:  non-blocking synchronous read when socket"
                 " has no data." << std::endl;
    boost::asio::write(socket2, boost::asio::buffer("hello"));
    bytes_transferred = socket1.receive(
        boost::asio::buffer(buffer), 0 /* flags */, error);
    print_status(error, bytes_transferred);
  }
}