#include <boost/array.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <istream>
#include <list>
#include <string>

namespace bs  = boost::system;
namespace ba  = boost::asio;
namespace bas = ba::ssl;

using ba::ip::tcp;
using SslContext = boost::shared_ptr<bas::context>;

typedef ba::ip::tcp::acceptor    acceptor_type;
typedef bas::stream<tcp::socket> stream_type;

const short PORT = 26767;

class Session : public boost::enable_shared_from_this<Session>
{
public:
    typedef boost::shared_ptr<Session> Ptr;

    Session(ba::io_service& svc, SslContext ctx) : strand_(svc), ctx_(ctx), stream(svc, *ctx) { }

    virtual ~Session() {
        std::cout << __PRETTY_FUNCTION__ << "\n";
    }

    stream_type::lowest_layer_type& socket() { return stream.lowest_layer(); } 
    void start()                             { AsyncReadString();          } 
    void Stop()                              { stream.shutdown();            } 

protected:
    ba::io_service::strand strand_;
    SslContext             ctx_;
    stream_type            stream;
    ba::streambuf          stream_buffer;
    std::string            message;

    void AsyncReadString() {
        std::cout << __PRETTY_FUNCTION__ << "\n";

        ba::async_read_until(
            stream,
            stream_buffer,
            '\0', // null-char is a delimiter
            strand_.wrap(
                boost::bind(&Session::ReadHandler, shared_from_this(),
                    ba::placeholders::error,
                    ba::placeholders::bytes_transferred)));
    }
    void AsyncWriteString(const std::string &s) {
        std::cout << __PRETTY_FUNCTION__ << "\n";

        message = s;

        ba::async_write(
            stream,
            ba::buffer(message.c_str(), message.size()+1),
            strand_.wrap(
                boost::bind(&Session::WriteHandler, shared_from_this(),
                         ba::placeholders::error,
                         ba::placeholders::bytes_transferred)));
    }

    std::string ExtractString() {
        std::cout << __PRETTY_FUNCTION__ << "\n";

        std::istream is(&stream_buffer);
        std::string s;
        std::getline(is, s, '\0');
        return s;
    }

    void ReadHandler(const bs::error_code &ec, std::size_t /*bytes_transferred*/) 
    {
        std::cout << __PRETTY_FUNCTION__ << "\n";

        if (!ec) {
            std::cout << (ExtractString() + "\n");
            std::cout.flush();
            AsyncReadString();  // read again
        }
        else {
            // do nothing, "this" will be deleted later
        }
    }

    void WriteHandler(const bs::error_code &/*ec*/, std::size_t /*bytes_transferred*/) {
        std::cout << __PRETTY_FUNCTION__ << "\n";
    }
};

class Server : public boost::enable_shared_from_this<Server>
{
  public:
    Server(ba::io_service& io_service, unsigned short port) :
        strand_  (io_service),
        acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
        context_ (boost::make_shared<bas::context>(io_service, bas::context::sslv23))
    {
        //
    }

    void start_accept() {
        auto new_session = boost::make_shared<Session>(strand_.get_io_service(), context_);

        acceptor_.async_accept(new_session->socket(),
                strand_.wrap(boost::bind(&Server::handle_accept, this, new_session, ba::placeholders::error)));
    }

    void stop_accept() {
        auto keep = shared_from_this();
        strand_.post([keep] { keep->acceptor_.close(); });
    }

    void handle_accept(Session::Ptr new_session, const bs::error_code& error)
    {
        if (!error) {
            new_session->start();
            start_accept(); // uses `acceptor_` safely because of the strand_
        }
    }

    ~Server() {
        std::cout << __PRETTY_FUNCTION__ << "\n";
    }

  private:
    ba::io_service::strand strand_;
    tcp::acceptor          acceptor_;
    SslContext             context_;
};

int main() {
    ba::io_service svc;
    boost::thread_group pool;

    {
        auto s = boost::make_shared<Server>(svc, PORT);
        s->start_accept();

        for (auto i = 0u; i<boost::thread::hardware_concurrency(); ++i)
            pool.create_thread([&]{svc.run();});

        std::cerr << "Shutdown in 10 seconds...\n";
        boost::this_thread::sleep_for(boost::chrono::seconds(10)); // auto-shutdown in 10s

        std::cerr << "Shutdown...\n";
    } // destructor of Server // TODO thread-safe

    pool.join_all();
}
