#include <iterator>
#include <algorithm>
#include <iostream>
#include <vector>

namespace stable {

template <class T, class Dist=std::ptrdiff_t, class Ptr = T*, class Ref = T&>
class iterator : public std::iterator<std::random_access_iterator_tag, T, Dist, Ptr, Ref>
{
    T &container_;
    size_t index_;
public:
    iterator(T &container, size_t index) : container_(container), index_(index) {}

    iterator operator++() { ++index_; return *this; }
    iterator operator++(int) { iterator temp(*this); ++index_; return temp; }
    iterator operator--() { --index_; return *this; }
    iterator operator--(int) { iterator temp(*this); --index_; return temp; }
    iterator operator+(Dist offset) const { return iterator(container_, index_ + offset); }
    iterator operator-(Dist offset) const { return iterator(container_, index_ - offset); }
    Dist operator-(iterator const &other) const { return index_ - other.index_; }
    
    bool operator!=(iterator const &other) const { return index_ != other.index_; }
    bool operator==(iterator const &other) const { return index_ == other.index_; }
    bool operator<(iterator const &other) const { return index_ < other.index_; }
    bool operator>(iterator const &other) const { return index_ > other.index_; }
    
    typename T::value_type &operator *() { return container_[index_]; }
    typename T::value_type &operator[](size_t index) { return container_[index_ + index]; }
};

template <class T>
iterator<T> begin(T &container) { return iterator<T>(container, 0); }

template <class T>
iterator<T> end(T &container) { return iterator<T>(container, container.size()); }
    
}

#ifdef TEST
int main() { 

    std::vector<int> data;
    
    for (int i=0; i<10; i++)
        data.push_back(i);
        
    stable::iterator<std::vector<int> > b = stable::begin(data);
    stable::iterator<std::vector<int> > e = stable::end(data);
    
    for (int i=10; i<10000; i++)
        data.push_back(i);
        
    std::copy(b, e, std::ostream_iterator<int>(std::cout, "\n"));

    std::cout << *(b+125) << "\n";
    std::cout << b[150] << "\n";

    return 0;
}
#endif
