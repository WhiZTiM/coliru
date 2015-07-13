#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <typeindex>

struct Foo
{
public:

  template< class T, class ...Args >
  T& create(Args&&... args)
  {
      auto& pool = find_or_make_pool<T>();
      return pool.construct( std::forward<Args>(args)... );
  }

private:
 struct IPool
 {
    virtual ~IPool() = default;
 };
 
 static constexpr size_t max_objects_per_pool = 42;
 
 template< class T>
 struct Pool : public IPool
 {
    T* objects = new T[max_objects_per_pool];
    size_t objects_count = 0;
    template< class... Args >
    T& construct( Args&&... args )
    {
        if(objects_count == max_objects_per_pool)
           throw std::bad_alloc();
        new(&objects[objects_count++]) T{ std::forward<Args>(args)... };
        return objects[objects_count - 1];
    }
    
    ~Pool()
    {
        delete [] objects;
    }
 };
 
 template< class T >
 Pool<T>& find_or_make_pool()
 {
    auto& pool = m_pool_index[typeid(T)];
    if(!pool)
    {
        pool = std::make_unique<Pool<T>>();
    }
    return static_cast<Pool<T>&>(*pool.get());
 }
 
 std::map<std::type_index, std::unique_ptr<IPool>> m_pool_index;
 
};

struct A
{
    int k = 0;
    std::string u = "lol";
};

int main()
{
    Foo foo;
    auto& a = foo.create<A>( 42, "wow" );
    std::cout<< "k = " << a.k << ", u = " << a.u << std::endl;
}
