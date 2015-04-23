#include <memory>
#include <type_traits>

template <typename RAContainer, bool Aggregate = std::is_pod<RAContainer>::value> struct shared_randomaccess_container;

template <typename RAContainer> struct shared_randomaccess_container<RAContainer, true>
{
    template <typename... A> shared_randomaccess_container(A&&... args) 
        : _ptr(new RAContainer{ std::forward<A>(args)... })
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

  protected:
    using Ptr = std::shared_ptr<RAContainer>;
    Ptr _ptr;
};

template <typename RAContainer> struct shared_randomaccess_container<RAContainer, false>
    : shared_randomaccess_container<RAContainer, true>
{
    using base_type = shared_randomaccess_container<RAContainer, true>;
    using base_type::shared_randomaccess_container;

    template <typename T> shared_randomaccess_container(std::initializer_list<T> init) { 
        base_type::_ptr = std::make_shared<RAContainer>(init);
    }
};

////////////////////////////////////////////////////
// demo intances
#include <array>
#include <vector>

template <typename... Ts> using shared_vector          = shared_randomaccess_container<std::vector<Ts...> >;
template <typename T, size_t N> using shared_std_array = shared_randomaccess_container<std::array<T, N> >;

////////////////////////////////////////////////////
// demo test
#include <iostream>
template <typename With> void test() {
    std::cout << "\n\n" << __PRETTY_FUNCTION__ << "\n";
    With sv {1,2,3};

    std::cout << "Before: ";
    for (auto i : sv) std::cout << i << " ";

    sv[1] = 42;
    std::cout << "\nAfter:  ";
    for (auto i : sv) std::cout << i << " ";
}

int main() {
    test<std::vector<int> >();
    test<std::array<int, 3> >();

    // using shared_randomaccess_container<>
    test<shared_vector<int> >();
    test<shared_std_array<int, 3> >();
}
