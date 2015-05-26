#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

#include <boost/thread.hpp>

static boost::mutex global_stream_lock;

class RPC {
    char recv_buffer[56];
  public:

    void data_recv() {
        socket.async_read_some(boost::asio::buffer(recv_buffer),
                               boost::bind(&RPC::on_data_recv, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

        boost::lock_guard<boost::mutex> lk(global_stream_lock);
        std::cout << "[" << boost::this_thread::get_id() << "] data recvd" << std::endl;
        global_stream_lock.unlock();
    }

    void on_data_recv(boost::system::error_code/* ec */, size_t /*bytes_transferred*/) {
        {
            boost::lock_guard<boost::mutex> lk(global_stream_lock);
            std::cout << "[" << boost::this_thread::get_id() << "] bytes rcvd: " << std::endl;
        }

        data_recv(); // call function that waits for more data
    }

    boost::asio::io_service service;
    boost::asio::ip::tcp::socket socket{service};
}; // RPC class def

int main() {}
