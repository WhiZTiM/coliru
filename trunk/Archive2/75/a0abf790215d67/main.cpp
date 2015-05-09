#include <iostream>
#include <vector>
#include <string>

class A;

class T {
  private:
  
  struct TAllocator: std::allocator<T> {
    template< class U, class... Args >
    void construct( U* p, Args&&... args ) { // Override construct
        ::new((void *)p) U(std::forward<Args>(args)...);
    }
    // Provide this same allocator for any type
    template< class U > struct rebind { typedef TAllocator other; };
  };
  
  friend class A;
  
  T(std::string s) : str(s) {}
  
  std::string str;
};


class A {
  public:
  
  A() {
   
   vec.emplace_back("hello");
      
  }
  
  std::vector<T, T::TAllocator> vec;
    
};

int main() {

  A obj;

  return 0;
}