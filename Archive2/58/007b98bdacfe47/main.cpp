#include <memory>

template <typename RAContainer> struct shared_randomaccess_container
{
    template <typename... A> shared_randomaccess_container(A&&... args) 
        : _ptr(new RAContainer{ std::forward<A>(args)... })
    { }
    template <typename T> shared_randomaccess_container(std::initializer_list<T> init)
        : _ptr(std::make_shared<RAContainer>(init))
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

////////////////////////////////////////////////////
// demo intances
#include <vector>

template <typename... Ts> using shared_vector          = shared_randomaccess_container<std::vector<Ts...> >;

////////////////////////////////////////////////////
// demo test
#include <iostream>
template <typename With> void test()
{
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
}
