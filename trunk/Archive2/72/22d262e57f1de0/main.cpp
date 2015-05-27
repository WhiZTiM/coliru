#include <iostream>
#include <string>
#include <vector>
#include <new>
#include <cstdlib>
#include <list>


// simple mallocator borrowed from Stephan T. Lavavej's CppCon 2014 talk "STL Features and Implementation Techniques"

template<class T> struct mallocator
{
    using value_type = T;
    mallocator() = default;
    
    template<class U>
    mallocator(const mallocator<U>&) noexcept {}
    
    template<class U>
    bool operator ==( const mallocator<U>&) const noexcept { return true; }
    
    template<class U>
    bool operator !=( const mallocator<U>&) const noexcept {return false; }
    
    T* allocate (const std::size_t n) const
    {
        if(n == 0)
        {
            return nullptr;
        }
        
        if(n > static_cast<size_t>(-1) / sizeof(T))
        {
            throw std::bad_array_new_length();
        }
        
        void* const pv = std::malloc(n * sizeof(T));
        if(!pv)
        {
            throw std::bad_alloc();
        }
        
        std::cout << "Using mallocator!\n";
        return static_cast<T*>(pv);
            
    }
    
    void deallocate(T* const p, size_t) const noexcept
    {
        std::free(p);
    }

};


// both gcc and clang fail to compile the following code when used with std::list as opposed to std::vector
// for illustration, I've used std::vector instead

template<typename T>
using my_vector = std::vector<T,mallocator<T>>;

int main()
{
   
   // if I want to use std::vector with the custom mallocator, I can simply use my_vector instead of having to explicitly
   // state my allocator every time with std::vector
   
   my_vector<int>   vec1;                 // uses T = int and Allocator = mallocator<int>
   std::vector<int> vec2;                 // uses T = int and Allocator = std::allocator<int>
   std::vector<int,mallocator<int>> vec3; // uses T = int and Allocator = mallocator<int>
   
   // notice how vec3 and vec1 are the same type ( same template T and same allocator)
   
   vec1.push_back(10);
   vec1.push_back(20);
   
   vec2.push_back(10);
   vec2.push_back(20);
   
   vec3.push_back(10);
   vec3.push_back(20);
   
   // should print out "Using mallocator!" 4 times
   
   
   
   
   
   
   
}
