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

    struct AnyTest {
        using Value = boost::variant<int, std::string>;
        using Wrap  = boost::variant<TestInt, TestString>;

        AnyTest(Wrap o) : wrap_(std::move(o)) { }

        Wrap wrap_;

        Value a() const {
            return boost::apply_visitor(a_f{}, wrap_);
        }

        void b(Value const& v) {
            boost::apply_visitor(b_f{}, wrap_, v);
        }
      private:
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
    };
}

#include <vector>

int main()
{
    using namespace mytypes;
    std::vector<AnyTest> list{AnyTest(TestInt()), AnyTest(TestString()), AnyTest(TestInt()), AnyTest(TestString())};

    for (auto it = list.begin(); it != list.end(); ++it)
        it->b(it->a());
}
