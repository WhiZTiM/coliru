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
      return pool.create( std::forward<Args>(args)... );
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
    unsigned char* memory = new unsigned char[max_objects_per_pool * sizeof(T)];
    size_t objects_count = 0;
    
    T* locate_object(size_t idx) { return reinterpret_cast<T*>( &memory[ idx*sizeof(T) ] ); }
    
    template< class... Args >
    T& create( Args&&... args )
    {
        if(objects_count == max_objects_per_pool)
           throw std::bad_alloc();
        
        const size_t new_idx = objects_count++;
        T* object = locate_object(new_idx);
        
        new(object) T{ std::forward<Args>(args)... };
        return *object;
    }
    
    ~Pool()
    {
        delete [] memory;
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
    auto& b = foo.create<A>( 1, "kikoolol" );
    std::cout<< "a.k = " << a.k << ", a.u = " << a.u << std::endl;
    std::cout<< "b.k = " << b.k << ", b.u = " << b.u << std::endl;
    auto& c = foo.create<A>();
    std::cout<< "a.k = " << a.k << ", a.u = " << a.u << std::endl;
    std::cout<< "b.k = " << b.k << ", b.u = " << b.u << std::endl;
    std::cout<< "c.k = " << c.k << ", c.u = " << c.u << std::endl;
    
    
}
