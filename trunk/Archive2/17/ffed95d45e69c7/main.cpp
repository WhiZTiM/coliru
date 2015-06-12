#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

using boost::asio::ip::tcp;

class AsyncHttpConnection : public boost::enable_shared_from_this<AsyncHttpConnection> {
  public:
    AsyncHttpConnection(boost::asio::io_service& io_service, std::string host, std::string path)
        : resolver_(io_service), socket_(io_service), host_(host), path_(path)
    {
        // cannot use shared_from_this in constructor!
    }

    void start() {
        tcp::resolver::query query(host_, "http");

        resolver_.async_resolve(query, 
                boost::bind(&AsyncHttpConnection::handle_resolve, 
                    shared_from_this(), boost::asio::placeholders::error,
                    boost::asio::placeholders::iterator));
    }

    ~AsyncHttpConnection() {
        std::cout << "Destructor for AsyncHttpConnection\n";
    }

  private:
    tcp::resolver resolver_;
    tcp::socket socket_;
    std::string host_;
    std::string path_;
    boost::asio::streambuf request_;
    boost::asio::streambuf response_;

    void handle_resolve(const boost::system::error_code& err, tcp::resolver::iterator /*endpoint_iterator*/)
    {
        if (!err) {
            // code here
        } else {
            std::cout << err.message() << std::endl; // GOT "Operation Canceled" here
        }
    }
};

class AsyncHttpClient {
  public:
    AsyncHttpClient(boost::asio::io_service& io_service, std::string host) : host_(host)
    {
        io_service_ = &io_service; // store address of io_service
    }

    void async_call(std::string path) {
        boost::make_shared<AsyncHttpConnection>(*io_service_, host_, path)->start();
    }

  private:
    std::string host_;
    boost::asio::io_service* io_service_; // pointer, because io_service is uncopyable;
};

int main()
{
    boost::asio::io_service io_service;
    AsyncHttpClient client(io_service, "www.boost.org");
    client.async_call("/doc/libs/1_51_0/doc/html/boost_asio/example/http/client/async_client.cpp");
    io_service.run();
}
