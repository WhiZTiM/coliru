#include <boost/asio.hpp>
#include <iostream>

static boost::asio::ip::tcp::no_delay const no_delay_option (true);

int main() {
    using boost::asio::ip::tcp;

    tcp::iostream socketStream;


    boost::asio::io_service io_service;

    tcp::endpoint endpoint (tcp::v4(), 6666);
    tcp::acceptor acceptor (io_service, endpoint);

    std::cout << "Waiting for connection.." << std::endl;
    acceptor.accept (*socketStream.rdbuf ());
    socketStream.rdbuf()->set_option(no_delay_option);

    std::cout << "Connected!" << std::endl;
    std::cout << socketStream.rdbuf() << "\n";
}
