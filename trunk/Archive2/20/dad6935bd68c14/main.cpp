#include <memory>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

struct IoService
{
     boost::thread_group m_processor;
     boost::asio::io_service m_io_service;
     std::shared_ptr<boost::asio::io_service::work> m_work;

     boost::asio::io_service& get()
     {
        return m_io_service;
     }

     void stop()
     { 
        m_work.reset();
        m_io_service.stop();        
        m_processor.join_all();  // Client::disconnected call after this line has been executed !!
        m_io_service.reset();
     } 

     void startProcessor(std::uint32_t processorId)
     { 
       m_io_service.run(); 
       std::cout << "IoService::startProcessor() after run" << std::endl;
     }

    void start(std::uint32_t count)
    {   
        m_work = 
           std::make_shared<boost::asio::io_service::work>(m_io_service);

        for (std::size_t i = 0; i < count; ++i)
            m_processor.create_thread([this,i] { startProcessor(i); });
    } 
};


 struct Client:
   public std::enable_shared_from_this<Client>
 {
    Client(const std::shared_ptr<IoService>& ioservice)
       : m_ioservice(ioservice),
         m_strand(ioservice->get())
    {}

    void disconnect()
    {
      //never called ???
      std::cout << "Client::disconnect()" << std::endl;
    }

    void post()
    { 
        std::cout << "Client::post()" << std::endl;
        m_ioservice->get().post(m_strand.wrap(boost::bind(&Client::disconnect, shared_from_this())));
    }

    std::shared_ptr<IoService> m_ioservice;
    boost::asio::io_service::strand m_strand;
 };
 
int main() {
     auto&& ioservice = std::make_shared<IoService>();
     ioservice->start(1);
     auto&& client = std::make_shared<Client>(ioservice);
     client->post();
     sleep(5) ;
     ioservice->stop();
}
