#include <memory>
#include <vector>
#include <list>

template <typename RAContainer> struct shared_randomaccess_container 
{
    template <typename T> shared_randomaccess_container(std::initializer_list<T> init) 
        : _ptr(std::make_shared<RAContainer>(init))
    { }
    template <typename... A> shared_randomaccess_container(A&&... args) 
        : _ptr(std::make_shared<RAContainer>(std::forward<A>(args)...))
    { }

    auto begin() const -> typename RAContainer::const_iterator { return _ptr->begin(); }
    auto end  () const -> typename RAContainer::const_iterator { return _ptr->end  (); }
    auto begin()       -> typename RAContainer::iterator       { return _ptr->begin(); }
    auto end  ()       -> typename RAContainer::iterator       { return _ptr->end  (); }

    template <typename Idx>
    typename RAContainer::value_type const& operator[](Idx i) const { return (*_ptr)[i]; }
    template <typename Idx>
    typename RAContainer::value_type& operator[](Idx i) { return (*_ptr)[i]; }

    template <typename Idx>
    typename RAContainer::value_type const& at(Idx i) const { return _ptr->at(i); }
    template <typename Idx>
    typename RAContainer::value_type& at(Idx i) { return _ptr->at(i); }

  private:
    using Ptr = std::shared_ptr<RAContainer>;
    Ptr _ptr;
};

template <typename... Ts> using shared_vector    = shared_randomaccess_container<std::vector<Ts...> >;
template <typename... Ts> using shared_std_array = shared_randomaccess_container<std::array<Ts...> >;

#include <iostream>
int main() {
    shared_vector<int> sv { 1,2,3 };

    std::cout << "Before: ";
    for (auto i : sv) std::cout << i << " ";

    sv[1] = 42;
    std::cout << "\nAfter:  ";
    for (auto i : sv) std::cout << i << " ";
}
