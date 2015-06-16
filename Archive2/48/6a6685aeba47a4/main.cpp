#include <iostream>


class a_class{
    public:
    
    a_class(){
      
    }
    
    ~a_class(){
        std::cout << "a_class destructor" << std::endl;
    }
    
    
};

class b_class: public a_class{
  public:
  
  b_class(){
      
  }
  
  ~b_class(){
      std::cout << "b_class destructor" << std::endl;
  }
};

int main() {
    
    b_class* b_object = new b_class();
    
    a_class* a_object = static_cast<a_class*>(b_object);
    delete a_object;
    
    std::cout << "pre return" << std::endl;
    
    return 0;
}
