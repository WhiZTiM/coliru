#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <iterator>

template<typename Iterator,
         typename Address = decltype(std::addressof(**std::declval<Iterator>()))
         >
class address_iterator : public std::iterator<std::input_iterator_tag, Address>
{
public:
    address_iterator(Iterator i) : i_{std::move(i)} {};

    Address operator*() const {
        return std::addressof(**i_);
    };

    Address operator->() const {
        return operator*();
    }
    
    address_iterator& operator++() {
        ++i_;
        return *this;
    };
    
    address_iterator operator++(int) {
        auto old = *this;
        operator++();
        return old;
    }
    
    bool operator==(address_iterator const& other) const {
        return i_ == other.i_;
    }
    
private:
    Iterator i_;
};

template<typename I, typename A>
bool operator!=(address_iterator<I, A> const& lhs, address_iterator<I, A> const& rhs) {
    return !(lhs == rhs);
}

template<typename Iterator>
address_iterator<Iterator> make_address_iterator(Iterator i) {
    return i;
}

// Element Class
struct Foo { };

// Take a range of elements, sort them internally by their addresses and print them in order    
template <typename FooIterator>
void print_sorted_addresses(FooIterator beginFoos, FooIterator endFoos) {
    std::vector<const Foo*> elements(make_address_iterator(beginFoos), make_address_iterator(endFoos));
    std::sort(elements.begin(), elements.end());
    for(const Foo* e : elements)
        std::cout << e << std::endl;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, std::unique_ptr<T> const& ptr) {
    return os << ptr.get();
}

int main() {
#ifdef UNIQUE
    std::vector<std::unique_ptr<Foo>> foos;
#else
    std::vector<Foo*> foos;
#endif

    for (int i = 0; i < 10; ++i) {
        foos.emplace_back(new Foo());
    }
    
    std::random_shuffle(foos.begin(), foos.end());
    
    std::cout << "before sort:\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << foos[i] << '\n';
    }
    std::cout << '\n';

#ifdef UNIQUE
    std::cout << "after sort (unique_foos):\n";
#else
    std::cout << "after sort (raw_foos):\n";
#endif

    print_sorted_addresses(foos.cbegin(), foos.cend());

    return 0;
}
