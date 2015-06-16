#include <iostream>
#include <new>
#include <scoped_allocator>
#include <typeinfo>
#include <utility>
#include <vector>

template <typename Ty>
struct custom_allocator {
  typedef size_t size_type;
  typedef decltype((Ty *)0 - (Ty *)0) difference_type;
  typedef Ty *pointer;
  typedef const Ty *const_pointer;
  typedef Ty &reference;
  typedef const Ty &const_reference;
  typedef Ty value_type;
  
  template <typename Uy>
  struct rebind {
    typedef custom_allocator<Uy> other;
  };
  
  typedef std::true_type propagate_on_container_move_assignment; 
  
  custom_allocator() = default;
  custom_allocator(const custom_allocator &) = default;
  
  template <typename Uy>
  custom_allocator(const custom_allocator<Uy> &) {}
  
  pointer address(reference r) const noexcept { return std::allocator<Ty>().address(r); }
  const_pointer address(const_reference r) const noexcept { return std::allocator<Ty>().address(r); }
  
  pointer allocate(size_type s, const_pointer hint = nullptr) {
    std::cout << "custom_allocator::allocate" << std::endl;
    return std::allocator<Ty>().allocate(s, hint);
  }
  
  void deallocate(pointer p, size_type s) {
    std::cout << "custom_allocator::deallocate" << std::endl;
    return std::allocator<Ty>().deallocate(p, s);
  }
  
  size_type max_size() const noexcept {
    return std::allocator<Ty>().max_size();
  }
  
  template <typename U, typename... Args>
  void construct(U *p, Args&&... A) {
    std::cout << "custom_allocator::construct" << std::endl;
    std::allocator<Ty>().construct(p, std::forward<Args>(A)...);
  }
  
  template <typename U>
  void destroy(U *p) {
    std::cout << "custom_allocator::destroy" << std::endl;      
    std::allocator<Ty>().destroy(p);
  }
  
  template <typename Uy>
  friend bool operator==(const custom_allocator<Ty> &, const custom_allocator<Uy> &) { return true; }
  
  template <typename Uy>
  friend bool operator!=(const custom_allocator<Ty> &, const custom_allocator<Uy> &) { return false; }
};

template <typename Alloc = std::allocator<const char *>>
struct MyType {
  typedef Alloc allocator_type;
  
  static_assert(std::is_same<const char *, typename allocator_type::value_type>::value, "Must use the same type in the allocator");
  
  MyType(const char *V, const allocator_type &A) {
    std::cout << "MyType with Alloc: " << V << std::endl;
  }
  
  MyType(const char *V) {
    std::cout << "MyType without Alloc: " << V << std::endl;
  }
  
  MyType() {
    std::cout << "MyType default constructor without Alloc" << std::endl;
  }
  
  MyType(const allocator_type &A) {
    std::cout << "MyType default constructor with Alloc" << std::endl;   
  }
  
  MyType(const MyType &O, const allocator_type &A) {
    std::cout << "MyType copy constructor with Alloc" << std::endl;   
  }
  
  MyType(const MyType &O) {
    std::cout << "MyType copy constructor without Alloc" << std::endl;   
  }
};


template <typename Ty> using Allocator = custom_allocator<Ty>;

int main() {
  //using String = std::basic_string<char, std::char_traits<char>, Allocator<char>>;
  using String = MyType<Allocator<const char *>>;
  using Vector = std::vector<String, std::scoped_allocator_adaptor<Allocator<String>>>;
  
  std::cout << std::boolalpha << std::uses_allocator<String, Allocator<const char *>>::value << std::endl;
  std::cout << std::boolalpha << std::uses_allocator<String, std::scoped_allocator_adaptor<Allocator<String>>::inner_allocator_type>::value << std::endl;
  
//  std::cout << typeid(std::scoped_allocator_adaptor<Allocator<String>>::inner_allocator_type).name() << std::endl;
  
  Allocator<String> as;
  Vector v(as);
  
  v.push_back("testing");
  v.push_back("another test");
}
