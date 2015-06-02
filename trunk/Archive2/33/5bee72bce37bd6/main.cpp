#include<iostream>
#include<limits>

namespace shm
{

    template <class T>
    class ShmAllocator
    {
        public:
            // type definitions
            typedef T        value_type;
            typedef T*       pointer;
            typedef const T* const_pointer;
            typedef T&       reference;
            typedef const T& const_reference;
            typedef std::size_t    size_type;
            typedef std::ptrdiff_t difference_type;

            // rebind allocator to type U
            template <class U>
            struct rebind
            {
                typedef ShmAllocator<U> other;
            };

            // return address of values
            pointer address (reference value) const
            {
                return &value;
            }

            const_pointer address (const_reference value) const
            {
                return &value;
            }


            /* constructors and destructor
             * - nothing to do because the allocator has no state
             */
            ShmAllocator() throw() {}

            ShmAllocator(const ShmAllocator&) throw() {}

            template <class U>
                ShmAllocator (const ShmAllocator<U>&) throw() {}

            ~ShmAllocator() throw() {}

            // return maximum number of elements that can be allocated
            size_type max_size () const throw()
            {
                return std::numeric_limits<std::size_t>::max() / sizeof(T);
            }

            // allocate but don't initialize num elements of type T
            pointer allocate (size_type num, const void* = 0)
            {
                // print message and allocate memory with global new
                std::cerr << "allocate " << num << " element(s)"
                            << " of size " << sizeof(T) << std::endl;
                pointer ret = (pointer)(::operator new(num*sizeof(T)));
                std::cerr << " allocated at: " << (void*)ret << std::endl;
                return ret;
            }

            // initialize elements of allocated storage p with value value
            void construct (pointer p, const T& value)
            {
                // initialize memory with placement new
                new((void*)p)T(value);
            }

            // destroy elements of initialized storage p
            void destroy (pointer p)
            {
                // destroy objects by calling their destructor
                p->~T();
            }

            // deallocate storage p of deleted elements
            void deallocate (pointer p, size_type num)
            {
                // print message and deallocate memory with global delete
                std::cerr << "deallocate " << num << " element(s)"
                          << " of size " << sizeof(T)
                          << " at: " << (void*)p << std::endl;
                ::operator delete((void*)p);
            }
        protected:
        private:
    };
      // return that all specializations of this allocator are interchangeable
    template <class T1, class T2>
    bool operator== (const ShmAllocator<T1>&,
                        const ShmAllocator<T2>&) throw()
    {
        return true;
    }
    template <class T1, class T2>
    bool operator!= (const ShmAllocator<T1>&,
                        const ShmAllocator<T2>&) throw()
    {
        return false;
    }
}

#include<vector>
#include<deque>
#include<forward_list>
#include<list>
#include<stack>
#include<queue>
namespace shm
{
    template <class T>
    using vector = std::vector<T, ShmAllocator<T> >;

    template <class T>
    using deque = std::deque  <T, ShmAllocator<T> >;

    template <class T>
    using forward_list = std::forward_list<T, ShmAllocator<T> >;

    template <class T>
    using list = std::list<T, ShmAllocator<T> >;

    template <class T1, class T2 = deque<T1> >
    using stack = std::stack<T1, T2>;

    template <class T1, class T2 = deque<T1> >
    using queue = std::queue<T1, T2>;

    /*...*/
}