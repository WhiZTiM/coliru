#include <boost/any.hpp>
#include <boost/variant.hpp>
#include <boost/mpl/vector.hpp>
#include <string>

using namespace boost;

template <typename T>
struct Tag {
    T value;
};

using Types   = mpl::vector<std::string, double, int>;
using Tags    = mpl::transform<Types, Tag<mpl::_1> >::type;

using Variant = make_variant_over<Types>::type;
using AnyTag  = make_variant_over<Tags>::type;

namespace mydetail {
    struct assign_to : boost::static_visitor<bool> {
        template <typename V> bool operator()(Tag<V>& tagged, V const& value) const {
            tagged.value = value;
            return true;
        }

        template <typename T, typename V> bool operator()(T&&, V&&) const {
            return false;
        }
    };
}

bool setValue(AnyTag &tag, Variant const& val) {
    return boost::apply_visitor(mydetail::assign_to(), tag, val);
}

int main() {
    AnyTag t;

    t = Tag<std::string>();

    // corresponding type assigns and returns true:
    assert(setValue(t, "yes works"));

    // mismatch: no effect and returns false:
    assert(!setValue(t, 42));
    assert(!setValue(t, 3.1415926));
}
