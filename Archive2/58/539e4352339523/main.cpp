#include <boost/icl/interval_map.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <iostream>
#include <vector>
#include <set>

namespace bip = boost::interprocess;
namespace icl = boost::icl;

namespace shared {
    using segment = bip::managed_mapped_file;
    using smgr    = segment::segment_manager;
}

namespace {

    static bip::managed_mapped_file global_mm(bip::open_or_create, "./demo.bin", 1ul<<20);
    static bip::allocator<void, shared::smgr> global_alloc(global_mm.get_segment_manager());

    template <class T> struct SimpleAllocator : std::allocator<T> { // inheriting the nested typedefs only
        typedef T value_type;

        SimpleAllocator() : _alloc(global_alloc) {}
        template <class U> 
            SimpleAllocator(const SimpleAllocator<U> &other) : _alloc(other._alloc) {}

        T* allocate(std::size_t n)           { return std::addressof(*_alloc.allocate(n)); }
        void deallocate(T *p, std::size_t n) { _alloc.deallocate(p, n); }
         
        // optionals
        template <typename Other> struct rebind { typedef SimpleAllocator<Other> other; }; 
        bip::allocator<T, shared::smgr> _alloc;
    };

    template <class T, class U> bool operator==(const SimpleAllocator<T> &, const SimpleAllocator<U> &) { return true;  }
    template <class T, class U> bool operator!=(const SimpleAllocator<T> &, const SimpleAllocator<U> &) { return false; }
}

namespace shared {

    template <typename T> using allocator = SimpleAllocator<T>;
    template<typename T>  using set       = std::set<T, std::less<T>, allocator<T> >;

    template <typename Domain, typename Codomain>
    using basic_map = icl::interval_map<Domain, Codomain,
            icl::partial_absorber, std::less, icl::inplace_plus, icl::inter_section, icl::discrete_interval<int, std::less>,
            allocator
        >;

    using map      = basic_map<int, set<int> >;
    using interval = map::interval_type;
}

#include <iostream>

int main() {

    shared::map demo;
    for (auto&& element : {
            shared::map::value_type { shared::interval::right_open(4, 5), { 1, 7, } },
            shared::map::value_type { shared::interval::right_open(2, 6), { 1, 2, 3, } },
        })
    {
        demo.add(element);
        std::cout << "adding: " << element.first << ", result: " << demo << "\n";
    }
}
