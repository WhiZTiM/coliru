#include <future>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/asio/use_future.hpp>
#include <boost/optional.hpp>
#include <boost/utility/in_place_factory.hpp>

int main()
{
  using boost::asio::ip::tcp;

  // Setup server thread.
  boost::asio::io_service server_io_service;
  std::promise<tcp::endpoint> server_promise;
  auto server_future = server_promise.get_future();

  // Start server thread.
  std::thread server_thread(
    [&server_io_service, &server_promise]
    {
      tcp::acceptor acceptor(server_io_service);
      acceptor.open(tcp::v4());
      acceptor.set_option(
        boost::asio::socket_base::enable_connection_aborted(true));
      acceptor.bind(tcp::endpoint(tcp::v4(), 0));
      acceptor.listen();

      // Handlers will not chain work, so control the io_service with a work
      // object.
      boost::optional<boost::asio::io_service::work> work(
        boost::in_place(std::ref(server_io_service)));

      // Accept a connection.
      tcp::socket server_socket(server_io_service);
      auto on_accept = acceptor.async_accept(server_socket,
                                             boost::asio::use_future);

      // Server has started, so notify caller.
      server_promise.set_value(acceptor.local_endpoint());

      // Wait for connection or error.
      boost::system::system_error error =
        make_error_code(boost::system::errc::success);
      try
      {
        on_accept.get();
      }
      catch (const boost::system::system_error& e)
      {
        error = e;
      }
      std::cout << "Server got a connection " << error.code() << std::endl;

      // Read from connection.
      boost::asio::streambuf buffer;
      auto on_read = boost::asio::async_read_until(
          server_socket, buffer, '\n', boost::asio::use_future);

      // The async_read operation is work, so destroy the work object allowing
      // run() to exit.
      work = boost::none;

      // Timeout the async read operation.
      if (on_read.wait_for(std::chrono::seconds(1)) ==
            std::future_status::timeout)
      {
        std::cout << "Server read timed out -- cancelling socket jobs"
                  << std::endl;
        server_socket.close();
      }
      else
      {
        error = make_error_code(boost::system::errc::success);
        std::size_t bytes_transferred = 0;
        try
        {
          bytes_transferred = on_read.get();
        }
        catch (const boost::system::system_error& e)
        {
          error = e;
        }
        std::cout << "Got " << bytes_transferred << ", " 
                  << error.code() << std::endl;
      }
      std::cout << "Exiting server thread" << std::endl;
    });

  // Wait for server to start accepting connections.
  auto server_endpoint = server_future.get();
  std::cout << "Server set up" << std::endl;

  // Client thread.
  std::promise<void> promise;
  auto future = promise.get_future();
  std::thread client_thread(
    [&server_endpoint, &promise]
    {
      boost::asio::io_service io_service;
      tcp::socket client_socket(io_service);
      boost::system::error_code error;
      client_socket.connect(server_endpoint, error);
      std::cout << "Connected " << error << std::endl;
      promise.set_value();
      // Keep client socket alive, allowing server to timeout.
      std::this_thread::sleep_for(std::chrono::seconds(2));
      std::cout << "Exiting client thread" << std::endl;
    });
  // Wait for client to connect.
  future.get();
  std::cout << "Client set up" << std::endl;

  // Reset generic promise and future.
  promise = std::promise<void>();
  future = promise.get_future();

  // Run server's io_service.
  std::thread server_io_thread(
    [&server_io_service, &promise]
    {
      std::cout << "About to service server IO requests" << std::endl;
      try
      {
        server_io_service.run();
      }
      catch (const std::exception& e)
      {
        std::cout << "Exception caught: " << e.what() << std::endl;
      }
      std::cout << "Service jobs all run" << std::endl;
      promise.set_value();
    });

  if (future.wait_for(std::chrono::seconds(3)) ==
        std::future_status::timeout)
  {
    std::cout << "IO thread timed out servicing requests -- stopping it" 
              << std::endl;
    server_io_service.stop();
  }

  // Join all threads.
  server_io_thread.join();
  server_thread.join();
  client_thread.join();
}