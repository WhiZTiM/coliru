#include <algorithm>
#include <iostream>

namespace mytypes {
    template <typename T>
    struct Test {
        T a() const;
        void b(T t) { std::cout << t << std::endl; } 
    };

    template <> int         Test<int>::a()         const { return 1;      }
    template <> std::string Test<std::string>::a() const { return "test"; }

    using TestInt    = Test<int>;
    using TestString = Test<std::string>;
}

#include <boost/variant.hpp>

namespace mytypes { 
    using Value = boost::variant<int, std::string>;

    namespace detail {
        struct a_f : boost::static_visitor<Value> {
            template <typename T>
            Value operator()(Test<T> const& o) const { return o.a(); }
        };
        struct b_f : boost::static_visitor<> {
            template <typename T>
            void operator()(Test<T>& o, T const& v) const { o.b(v); }

            template <typename T, typename V>
            void operator()(Test<T>&, V const&) const {
                throw std::runtime_error(std::string("type mismatch: ") + __PRETTY_FUNCTION__);
            }
        };
    }

    template <typename O>
    Value a(O const& obj) {
        return boost::apply_visitor(detail::a_f{}, obj);
    }

    template <typename O, typename V>
    void b(O& obj, V const& v) {
        boost::apply_visitor(detail::b_f{}, obj, v);
    }
}

#include <vector>

int main()
{
    using namespace mytypes;
    using AnyTest = boost::variant<TestInt, TestString>;

    std::vector<AnyTest> list{TestInt(), TestString(), TestInt(), TestString()};

    for (auto it = list.begin(); it != list.end(); ++it)
        b(*it, a(*it));
}
