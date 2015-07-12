#include <iostream>
#include <boost/asio.hpp>
using namespace boost::asio;

int main() {
    io_service service;
    std::string str = "HTTP/1.1 200 OK\r\n ......";

    ip::tcp::acceptor my_acceptor{ service, ip::tcp::endpoint(ip::tcp::v4(), 6767) };
    ip::tcp::socket my_socket{ service };
    boost::system::error_code ec;
    my_acceptor.accept(my_socket, ec);
    if (!ec) {
        std::cout << "connected " << std::endl;

        size_t bytesTransferred = write(my_socket, buffer(str), ec);
        if (!ec)
            std::cout << "Data written (" << bytesTransferred << ")\n";
    };
}
