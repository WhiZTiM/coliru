#include <iostream>


class a_class{
    public:
    
    a_class(){
      
    }
    
    ~a_class(){
        std::cout << "a_class destructor" << std::endl; // this is being called
    }
    
    
};

class b_class: public a_class{
  public:
  
  b_class(){
      
  }
  
  ~b_class(){
      std::cout << "b_class destructor" << std::endl; // this is not being called
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
    
    a_class* a_object = static_cast<a_class*>(b_object);
    delete a_object;
            
    return 0;
}
