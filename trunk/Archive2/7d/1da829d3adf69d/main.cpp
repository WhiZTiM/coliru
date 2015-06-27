#include <iostream>
#include <boost/thread.hpp>
#include <boost/asio.hpp>


int main() {
    boost::asio::io_service service;
    boost::asio::io_service::strand strand1(service);
    boost::asio::io_service::strand strand2(service);
    boost::thread_group threads;
    int threads_num = boost::thread::hardware_concurrency() * 7;
    service.post(strand1.wrap([](){std::cout << "Handler 1-1" << std::endl;}));
    service.post(strand1.wrap([](){std::cout << "Handler 1-2" << std::endl;}));
    service.post(strand2.wrap([](){std::cout << "Handler 2-1" << std::endl;}));
    service.post(strand2.wrap([](){std::cout << "Handler 2-2" << std::endl;}));
    service.post([](){std::cout << "Handler 3-1" << std::endl;});
    service.post([](){std::cout << "Handler 3-2" << std::endl;});
    for (int i=0;i < threads_num;++i) {
        threads.create_thread([&service](){service.run();});
    }
    threads.join_all();
    return 0;
}