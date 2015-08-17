#include <boost/serialization/map.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <map>
#include <iostream>
#include <functional>
#include <sstream>

struct C {
    explicit C(int) { std::cerr << "create compare\n"; }
    C(const C&) { std::cerr << "copy construct compare\n"; }
    C(C&&) { std::cerr << "move construct compare\n"; }
    C& operator=(const C&) { std::cerr << "copy assign compare\n"; return *this; }
    C& operator=(C&&) { std::cerr << "move assign compare\n"; return *this; }
    
    template<typename T>
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs < rhs;
    }
    
    template <typename Archive>
    void serialize(Archive&, const unsigned int) {}
};

template <typename Archive>
void save_construct_data(Archive& ar, const C*, const unsigned int /*version*/)
{
    std::cerr << "Save construct compare\n";
}

template <typename Archive>
void load_construct_data(Archive& ar, C* compare, const unsigned int /*version*/)
{
    std::cerr << "Load construct compare\n";
    ::new(compare)C{0};
}

template<typename Compare>
struct A {
    Compare compare;
    std::map<int, int, std::reference_wrapper<Compare>> m;
    
    A(Compare a): compare(std::move(a)), m(std::ref(compare)) {}
    
    template<typename Archive>
    void load(Archive& ar, const unsigned int) {
        std::cerr << "load A\n";
        ar & m;
    }
    
    template<typename Archive>
    void save(Archive& ar, const unsigned int) const {
        std::cerr << "save A\n";
        ar & m;
    }
    
    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

template <typename Archive, typename Compare>
void save_construct_data(Archive& ar, const A<Compare>* a, const unsigned int /*version*/)
{
    std::cerr << "Save construct A\n";
    auto compare = std::make_unique<Compare>(a->compare);
    ar << compare;
}

template <typename Archive, typename Compare>
void load_construct_data(Archive& ar, A<Compare>* queue, const unsigned int /*version*/)
{
    std::cerr << "Load construct A\n";
    std::unique_ptr<Compare> compare;
    ar >> compare;
    ::new(queue)A<Compare>{std::move(*compare)};
}

int main() {
    auto a1 = std::make_unique<A<C>>(C(0));
    std::stringstream ss;
    boost::archive::text_oarchive out(ss);
    out << a1;
    
    std::cerr << "----\n";
    std::unique_ptr<A<C>> a2;
    boost::archive::text_iarchive in(ss);
    in >> a2;
}