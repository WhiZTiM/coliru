#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <istream>
#include <list>
#include <string>

namespace ba = boost::asio;
namespace bs = boost::system;
namespace b  = boost;

typedef ba::ip::tcp::acceptor acceptor_type;
typedef ba::ip::tcp::socket   socket_type;

const short PORT = 7373;

// A connection has its own io_service and socket
class Connection : public b::enable_shared_from_this<Connection>
{
public:
    typedef boost::shared_ptr<Connection> Ptr;
protected:
    socket_type    sock;
    ba::streambuf  stream_buffer; // for reading etc

    void AsyncReadString() {
        std::cout << __PRETTY_FUNCTION__ << "\n";

        ba::async_read_until(
            sock,
            stream_buffer,
            '\0',   // null-char is a delimiter
            b::bind(&Connection::ReadHandler, shared_from_this(),
                ba::placeholders::error,
                ba::placeholders::bytes_transferred));
    }
    void AsyncWriteString(const std::string &s) {
        std::cout << __PRETTY_FUNCTION__ << "\n";

        std::string newstr = s + '\0';  // add a null char
        ba::async_write(
            sock,
            ba::buffer(newstr.c_str(), newstr.size()),
            b::bind(&Connection::WriteHandler, shared_from_this(),
                ba::placeholders::error,
                ba::placeholders::bytes_transferred));
    }
    std::string ExtractString() {
        std::cout << __PRETTY_FUNCTION__ << "\n";

        std::istream is(&stream_buffer);
        std::string s;
        std::getline(is, s, '\0');
        return s;
    }
    void ReadHandler(
        const bs::error_code &ec,
        std::size_t bytes_transferred) 
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
    void WriteHandler(const bs::error_code &ec, std::size_t bytes_transferred) {
        std::cout << __PRETTY_FUNCTION__ << "\n";
    }
public:
    Connection(ba::io_service& svc) : sock(svc) { }

    virtual ~Connection() {
        std::cout << __PRETTY_FUNCTION__ << "\n";
    }

    socket_type& Socket() { return sock;          } 
    void Session()        { AsyncReadString();    } 
    void Stop()           { sock.cancel();        }
};

// a server also has its own io_service but it's only used for accepting
class Server {
public:
    std::list<boost::weak_ptr<Connection> > m_connections;
protected:
    ba::io_service _service;
    boost::optional<ba::io_service::work> _work;
    acceptor_type _acc;
    b::thread thread;

    void AcceptHandler(const bs::error_code &ec, Connection::Ptr accepted) {
        if (!ec) {
            m_connections.push_back(accepted);
            accepted->Session();
            DoAccept();
        }
        else {
            // do nothing the new session will be deleted automatically by the
            // destructor
        }
    }

    void DoAccept() {
        auto newaccept = boost::make_shared<Connection>(_service);

        _acc.async_accept(
            newaccept->Socket(),
            b::bind(&Server::AcceptHandler,
                this,
                ba::placeholders::error,
                newaccept
            ));
    }

public:
    Server():
        _service(),
        _work(ba::io_service::work(_service)),
        _acc(_service, ba::ip::tcp::endpoint(ba::ip::tcp::v4(), PORT)),
        thread(b::bind(&ba::io_service::run, &_service))
    {  }

    ~Server() {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        Stop();
        _work.reset();
        if (thread.joinable()) thread.join();
    }

    void Start() {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        DoAccept();
    }

    void Stop() {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        _acc.cancel();
    }

    void StopAllConnections() {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        for (auto c : m_connections) {
            if (auto p = c.lock())
                p->Stop();
        }
    }
};

int main() {
    try {
        Server s;
        s.Start();

        std::cerr << "Shutdown in 2 seconds...\n";
        b::this_thread::sleep_for(b::chrono::seconds(2));
        
        std::cerr << "Stop accepting...\n";
        s.Stop();

        std::cerr << "Shutdown...\n";
        s.StopAllConnections(); // interrupt ongoing connections
    } // destructor of Server will join the service thread
    catch (std::exception &e) {
        std::cerr << __FUNCTION__ << ":" << __LINE__ << "\n";
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    std::cerr << "Byebye\n";
}
