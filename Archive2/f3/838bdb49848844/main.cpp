#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <iostream>
#include <sstream>

template <typename T>
struct StateFullCmp {
    bool invert_;
    StateFullCmp(bool invert) : invert_(invert) {}

    bool operator()(T const&a, T const& b) const {
        return invert_? (b<a) : (a<b);
    }
};

namespace boost { namespace serialization {
    template <typename Ar, typename T>
        void serialize(Ar& ar, StateFullCmp<T>& cmp, unsigned) {
            ar & cmp.invert_;
        }
} }

int main() {
    using MyMap = std::map<int, std::string, StateFullCmp<int> >;
    std::stringstream ss;

    {
        MyMap const m {
            { { 1, "one" }, { 2, "two" }, { 3, "three" } },
            StateFullCmp<int> { true } // inverted order
        };

        std::cout << "====== original order\n";
        for (auto& e : m)
            std::cout << e.first << " -> " << e.second << "\n";

        boost::archive::text_oarchive oa(ss);
        auto cmp_copy = m.key_comp();
        oa << cmp_copy << m; 
    }

    {
        boost::archive::text_iarchive ia(ss);

        MyMap::key_compare cmp_state { false }; // default initialization
        ia >> cmp_state;

        MyMap deserialized(cmp_state);
        ia >> deserialized; 

        std::cout << "====== deserialized order\n";
        for (auto& e : deserialized)
            std::cout << e.first << " -> " << e.second << "\n";
    }
}

