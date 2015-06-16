#include <iostream>

#include <unistd.h>

class a_class{
    public:
    
    a_class(){
      
    }
    
    ~a_class(){
        std::cout << "a_class destructor" << std::endl; // this is being called
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
    
    b_class* b_object = new b_class();
    
//    a_class* a_object = static_cast<a_class*>(b_object);
//    delete a_object;
    
    c_class* c_object = reinterpret_cast<c_class*>(b_object);
    c_object->free_mem(b_object);
    delete c_object;
    
    
    //delete b_chunk;
            
    return 0;
}
