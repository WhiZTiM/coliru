
#include <iostream>
#include <vector>
#include <algorithm>


alloc:      reinterpret_cast<pointer>(::operator new () (cnt * sizeof (T)))
free:      ::operator delete(p)
maxSize:    std::numeric_limits<size_type>::max() / sizeof(T)

template <class T>
class MemoryPoolAllocator {
    public:
        typedef T value_type;
        typedef value_type * pointer;
        typedef value_type const * const_pointer;
        typedef value_type & reference;
        typedef value_type const & const_reference;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

//    convert an allocator<T> to allocator<U>
        template <class U>
        struct rebind { typedef MemoryPoolAllocator<U> other; };

        explicit MemoryPoolAllocator() : pool_(sizeof(T)) {}
//        inline explicit MemoryPoolAllocator(MemoryPoolAllocator const &) {}
        template <class U>
        explicit MemoryPoolAllocator(MemoryPoolAllocator<U> const &) : pool_(sizeof(T)) {}
        ~MemoryPoolAllocator() {}
    
//        inline pointer address(reference r) { return &r; }
//        inline const_pointer address(const_reference r) { return &r; }
    
        pointer allocate(size_type count, typename std::allocator<void>::const_pointer hint = 0) {
            return static_cast<pointer>(pool_.alloc(count));
        }
        void deallocate(pointer p, size_type count) {
            pool_.free(reinterpret_cast<typename std::allocator<void>::const_pointer>(p), count);
            return;
        }
    
        void construct(pointer p, const_reference t) { new (p) T(t); }
        void destroy(pointer p) { p->~T(); }
        
        size_type max_size() const {
            return pool_.maxSize();
        }
    
        friend template <class T>
        bool operator==(MemoryPoolAllocator<T> const &lhs, MemoryPoolAllocator<T> const &rhs);
        friend template <class T>
        bool operator!=(MemoryPoolAllocator<T> const &lhs, MemoryPoolAllocator<T> const &rhs);
    
    private:
        MemoryPool pool_;
};

template <class T>
bool operator==(MemoryPoolAllocator<T> const &lhs, MemoryPoolAllocator<T> const &rhs) {
    return lhs.pool_ == rhs.pool_;
}

template <class T>
bool operator!=(MemoryPoolAllocator<T> const &lhs, MemoryPoolAllocator<T> const &rhs) {
    return !(lhs == rhs);
}

class SignalDefinition {
    public:
        SignalDefinition(int value) :
            value_(value)
        { }
        
        friend bool operator==(SignalDefinition const &lhs, SignalDefinition const &rhs);
        
    private:
        int value_;
};

bool operator==(SignalDefinition const &lhs, SignalDefinition const &rhs) {
    return lhs.value_ == rhs.value_;
}

class SignalMonitoringServer {
    public:
        unsigned int signalCount() const {
            return signal_definitions_.size();
        }
        
        void Monitor(SignalDefinition const &definition) {
            signal_definitions_.push_back(definition);
        }
        
        void Unmonitor(SignalDefinition const &definition) {
            signal_definitions_.erase(
                std::remove(
                    signal_definitions_.begin(), 
                    signal_definitions_.end(), 
                    definition
                ), 
                signal_definitions_.end()
            );
        }
        
        void UnmonitorAll() {
            signal_definitions_.clear();
        }
        
        // void ForEachSignal(boost::function<void (SignalDefinition const &)> iterate);
        
    private:
        std::vector< SignalDefinition, Allocator<SignalDefinition> > signal_definitions_;
            // This reliance on the STL could be really awesome.
            //  If you can successfully put STL containers into
            //  reflective memory, you'll have a powerful tool
            //  at your disposal for shared-memory IPC.  This
            //  will involve custom allocators and less control
            //  over the exact amount of space that gets used.
            //  You want this to work out because you'll learn
            //  a lot about C++ in the process and allow you
            //  access to this powerful tool in any RM situation.
            //  Keep this encapsulated, so that if it proves to 
            //  be too ambitious and causes issues down the line, 
            //  you can replace it with something else.  At that
            //  point you will probably have to take a page out of
            //  EASTL's book and roll your own fixed_vector class.
            //  This upholds a similar abstraction as a vector
            //  (a container that grows and shrinks and allows
            //  insert(), erase(), clear(), push_back(), functions
            //  and <algorithm> and iterator compatibility), but
            //  is limited in how far it grows.  It will likely
            //  depend on a std::array internally, allocating the
            //  maximum amount of space statically and providing
            //  the additional behaviors of a vector that an array
            //  does not support.
};

int main() {
    SignalMonitoringServer sigmon_server;
    
    SignalDefinition sig0(0);
    SignalDefinition sig1(1);
    SignalDefinition sig2(2);
    
    sigmon_server.Monitor(sig0);
    sigmon_server.Monitor(sig1);
    sigmon_server.Monitor(sig2);
    
    std::cout << "Signal count = " << sigmon_server.signalCount() << std::endl;
    
    sigmon_server.Unmonitor(sig1);
    
    std::cout << "Signal count = " << sigmon_server.signalCount() << std::endl;
}