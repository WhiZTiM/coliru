#include <iostream>

#include <unistd.h>

#include <iostream>

#include <mutex> 

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

class server{
    public:
    server(){
            
      try
      {
        boost::asio::io_service io_service;
    
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
    
        for (;;)
        {
          tcp::socket socket(io_service);
          acceptor.accept(socket);
    
          std::string message = make_daytime_string();
    
          boost::system::error_code ignored_error;
          boost::asio::write(socket, boost::asio::buffer(message),
              boost::asio::transfer_all(), ignored_error);
        }
      }
      catch (std::exception& e)
      {
        std::cerr << e.what() << std::endl;
      }
    }

};

class a_class{
    public:
    
    a_class(){
      
    }
    
    ~a_class(){
        //std::cout << "a_class destructor" << std::endl; // this is being called
        
    }
    
    
};

std::string getcwd_string( void ) {
   char buff[256];
   getcwd( buff, 256 );
   std::string cwd( buff );
   return cwd;
}

class standard_class{
    public:
    
    standard_class(){
        init_systems();
    }
    
    void init_systems(){
        std::cout << "fine" << std::endl;   
        std::cout << "cwd" << getcwd_string() << std::endl;
        auto cwd = getcwd_string();
        cwd += "..";
        chdir("/");
        std::cout << "cwd" << getcwd_string() << std::endl;
        //server net_server;
        delete reinterpret_cast<a_class*>(this);
               
    }
    
    ~standard_class(){
       
    }
};

class b_class: public a_class{
  public:
  
  b_class(){
      data = new int(25);
  }
  
  void kill(){
      delete data;
      std::cout << "b_class kill method" << std::endl; // this being called
      
      entry_point = new standard_class();   
  }
  
  ~b_class(){
      kill();
      std::cout << "b_class destructor" << std::endl; // this is not being called
  }
  
  int* data;
  standard_class* entry_point;
};


class c_class{
  public:
  c_class(){
      
  }
  
  void free_mem(b_class* b_object){
        b_object->kill();   
        memcpy (this, new b_class, sizeof(b_class) );
        
  }
  
  ~c_class(){
      std::cout << "c_class destructor" << std::endl; // this is being called
  }
};

// memory should look like this:

///////////////////////////// 
//               A         //
//                         //
//                         //
/////////////////////////////
/////////////////////////////
//               B         //
/////////////////////////////

// after delete

/////////////////////////////
//               B         //
/////////////////////////////

// what does happen with B?


int main() {
    chdir("/");
    system ("ls");
    
/*    
    b_class* b_object = new b_class();
   */ 
//    a_class* a_object = static_cast<a_class*>(b_object);
//    delete a_object;

/*    std::cout << "OK\n";
    std::cin.get();
    
    c_class* c_object = reinterpret_cast<c_class*>(b_object);
    c_object->free_mem(b_object);
    delete c_object;
   */
    
    //delete b_chunk;
            
    return 0;
}
