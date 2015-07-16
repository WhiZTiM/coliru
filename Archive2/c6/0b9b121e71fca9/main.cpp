#include <boost/asio.hpp>

// Derive from boost::asio::streambuf.
class derived_streambuf
  : public boost::asio::streambuf
{};

// Helper function to force type.
template <typename Allocator>
boost::asio::basic_streambuf<Allocator>&
as_streambuf(boost::asio::basic_streambuf<Allocator>& streambuf)
{
  return streambuf;
}

int main()
{
  boost::asio::io_service io_service;
  boost::asio::ip::tcp::socket socket(io_service);
  derived_streambuf streambuf;
  boost::asio::write(socket, static_cast<boost::asio::streambuf&>(streambuf));
  boost::asio::write(socket, as_streambuf(streambuf));
}