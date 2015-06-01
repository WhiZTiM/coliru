    #include <iostream>
    #include <tuple>
    #include <type_traits>
    #include <boost/mpl/find_if.hpp>
    #include <boost/mpl/deref.hpp>
    #include <boost/fusion/include/mpl.hpp>
    #include <boost/fusion/adapted/std_tuple.hpp>
    #include <boost/fusion/include/for_each.hpp>
    #include <functional>

    class A {

    public:

        void aFoo() {
            std::cout << "A" << std::endl;
        }
    };

    class B {

    public:

        void bFoo() {
            std::cout << "B" << std::endl;
        }
    };

    class C {

    public:

        void c1Foo() {
            std::cout << "C1" << std::endl;
        }

        void c2Foo() { }
    };

    // functor used by boost to iterate over the tuple
    template <class Tuple>
    struct functor {

        functor(Tuple t)
        : m_tuple(t) { }

        template <class X>
        void operator()(X& x) const {
            using namespace boost::mpl;
            using iter = typename find_if<Tuple, std::is_same < placeholders::_1, void (X::*)()> >::type;
            using type = typename deref<iter>::type;
            return (x.*std::get<type>(m_tuple))();
        }

    private:
        Tuple m_tuple;
    };

    template <class Tuple>
    functor<Tuple> make_functor(Tuple t) {
        return functor<Tuple>(t);
    }

    int main() {

        std::tuple<void (A::*)(), void (B::*)(), void (C::*)() > x(&A::aFoo, &B::bFoo, &C::c1Foo);
        std::tuple<A, B, C> y;
        boost::fusion::for_each(y, make_functor(x));
    }
