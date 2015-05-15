// DRAFT Live Demo
// Refer https://bartoszmilewski.com/2015/05/11/using-monads-in-c-to-solve-constraints-1-the-list-monad/
//       https://github.com/BartoszMilewski/MoreMoney/
//       https://github.com/panaseleus/monad_do
// GOTO line 378

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/cat.hpp>

template<class Monad>
struct MonadUnit // customization point
{
    //template<typename T> auto operator()(T x) const
};

// TODO: MonadZero, MonadPlus, etc

template<class Monad>
struct MonadGuard // customization point
{
    //auto operator()(bool x) const
};

// DO-macro implementation:

#define SEQ_LAST(SEQ) BOOST_PP_SEQ_ELEM( BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(SEQ)), SEQ)

#define STMT_TAIL(r, data, elem) };

#define LAST_STMT(var, code) unit( var );

#define STMT_HEAD_AUX(var, code) code >>= [=](auto var) { return
#define STMT_HEAD(r, data, elem) STMT_HEAD_AUX elem

#define DO_AUX(SEQ) \
    BOOST_PP_SEQ_FOR_EACH(STMT_HEAD, _, SEQ) \
    BOOST_PP_EXPAND(LAST_STMT SEQ_LAST(SEQ)) \
    BOOST_PP_SEQ_FOR_EACH(STMT_TAIL, _, SEQ) \
/**/

#define DO(MONAD, SEQ) \
    ([=] \
    { \
        const auto unit = MonadUnit<MONAD>{}; \
        const auto guard = MonadGuard<MONAD>{}; \
        return \
            DO_AUX( BOOST_PP_SEQ_TAIL(BOOST_PP_CAT(BOOST_FUSION_ADAPT_STRUCT_FILLER_0(0,0)SEQ, _END)) ) \
    })() \
/**/

/******************************************************************************/
#if ! defined(LIST_H)
#define LIST_H

#include <cassert>
#include <memory>
#include <functional>
#include <initializer_list>
#include <iostream> // print

template<class T> class FwdListIter;

template<class T>
class List
{
    struct Item
    {
        Item(T v, std::shared_ptr<const Item> tail)
        : _val(v), _next(std::move(tail))
        {}
        // singleton
        explicit Item(T v) : _val(v) {}
        T _val;
        std::shared_ptr<const Item> _next;
    };
    friend Item;
    explicit List(std::shared_ptr<const Item> items)
        : _head(std::move(items)) {}
public:
    // Empty list
    List() {}
    // Cons
    List(T v, List const & tail)
        : _head(std::make_shared<Item>(v, tail._head)) {}
    // Singleton
    explicit List(T v) : _head(std::make_shared<Item>(v)) {}
    // From initializer list
    List(std::initializer_list<T> init)
    {
        for (auto it = std::rbegin(init); it != std::rend(init); ++it)
        {
            _head = std::make_shared<Item>(*it, _head);
        }
    }

    bool isEmpty() const { return !_head; }
    T front() const
    {
        assert(!isEmpty());
        return _head->_val;
    }
    List popped_front() const
    {
        assert(!isEmpty());
        return List(_head->_next);
    }
    // Additional utilities
    List pushed_front(T v) const
    {
        return List(v, *this);
    }
    List take(int n)
    {
        if (n <= 0 || isEmpty()) return List();
        return popped_front().take(n - 1).pushed_front(front());
    }
private:
    std::shared_ptr<const Item> _head;
};

template<class T, class F>
auto fmap(F f, List<T> lst) -> List<decltype(f(lst.front()))>
{
    using U = decltype(f(lst.front()));
    static_assert(std::is_convertible<F, std::function<U(T)>>::value,
        "fmap requires a function type U(T)");
    List<U> result;
    forEach(lst, [&](T x) {
        result = result.pushed_front(f(x));
    });
    return result;
}

template<class T>
List<T> concat(List<T> const & a, List<T> const & b)
{
    if (a.isEmpty())
        return b;
    return List<T>(a.front(), concat(a.popped_front(), b));
}

template<class T>
List<T> concatAll(List<List<T>> const & xss)
{
    List<T> result;
    forEach(xss, [&](List<T> const & xs){
        forEach(xs, [&](T const & e) {
            result = result.pushed_front(e);
        });
    });
    return result;
}

// List monad

template<class A, class F>
auto for_each(List<A> lst, F k) -> decltype(k(lst.front()))
{
    using B = decltype(k(lst.front()).front());
    static_assert(std::is_convertible<
        F, std::function<List<B>(A) >> ::value,
        "for_each requires a function type List<B>(A)");

    List<List<B>> lstLst = fmap(k, lst);
    return concatAll(lstLst);
}

template<class A>
List<A> yield(A a)
{
    return List<A>(a);
}

// consumes the list when called: 
// forEach(std::move(lst), f);

template<class T, class F>
void forEach(List<T> lst, F f)
{
    static_assert(std::is_convertible<F, std::function<void(T)>>::value,
        "forEach requires a function type void(T)");
    while (!lst.isEmpty()) {
        f(lst.front());
        lst = lst.popped_front();
    }
}


#endif
/*********************************************************************/
//#include "List.h"
#include <functional>
#include <tuple>

using namespace std;

// newtype StateL s a = StateL (s -> [(a, s)])
template<class State, class A>
using PList = List<pair<A, State>>;

template<class State, class A>
using StateL = function<PList<State, A>(State)>;

// runStateL :: StateL s a -> s -> [(a, s)]
// runStateL(StateL g) s = g s

template<class State, class A>
PList<State, A> runStateL(StateL<State, A> st, State s)
{
    return st(s);
}

// evalStateL::StateL s a->s ->[a]
// evalStateL(StateL g) s = fmap fst(g s)
template<class State, class A>
List<A> evalStateL(StateL<State, A> st, State s)
{
    return fmap([](pair<A, State> const & p)->A {
        return p.first;
    }, st(s));
}

// return x = StateL(\s ->[(x, s)])
template<class State, class A>
StateL<State, A> mreturn(A a)
{
    return [a](State s) { return PList<State, A>(make_pair(a, s)); };
}

// (StateL g) >>= k = StateL(\s->concat $ fmap(\(a, s') -> runStateL (k a) s') (g s))

// k is a function<StateL<S, B>(A)>
// mbind returns StateL<S, B> 

template<class State, class A, class F>
auto mbind(StateL<State, A> g, F k) -> decltype(k(g(State()).front().first))
{
    return [g, k](State s) {
        PList<State, A> plst = g(s);
        //List<PList<B>> 
        auto lst2 = fmap([k](pair<A, State> const & p) {
            A a = p.first;
            State s1 = p.second;
            auto ka = k(a);
            auto result = runStateL(ka, s1);
            return result;
        }, plst);
        return concatAll(lst2);
    };
}

// mzero = StateL(\s ->[])
template<class State, class A>
StateL<State, A> mzero()
{
    return[](State s) {
        return PList<State, A>();
    };
}

struct Empty {};

template<class State>
auto mguard(bool b)
{
    return b ? mreturn<State>(Empty{}) : mzero<State, Empty>();
}

template<class S, class A>
std::ostream& operator<<(std::ostream& os, pair<A, S> const & p)
{
    os << "(";
    os << p.first << ", " << p.second;
    os << ")";
    return os;
}

template<class A, class B, class C>
std::ostream& operator<<(std::ostream& os, tuple<A, B, C> const & t)
{
    os << "(";
    os << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t);
    os << ")";
    return os;
}
/******************************************************************************/
//#include "StateList.h"
#include <initializer_list>
#include <vector>
#include <string>
using namespace std;

template<class A>
PList<List<A>, A> select(List<A> lst)
{
    if (lst.isEmpty())
        return PList<List<A>, A>();

    A       x  = lst.front();
    List<A> xs = lst.popped_front();

    auto result = List<pair<A, List<A>>>();
    forEach(select(xs), [x, &result](pair<A, List<A>> const & p)
    {
        A       y = p.first;
        List<A> ys = p.second;
        auto y_xys = make_pair(y, ys.pushed_front(x));
        result = result.pushed_front(y_xys);
    });

    return result.pushed_front(make_pair(x, xs));
}

template<class T>
std::ostream& operator<<(std::ostream& os, List<T> const & lst)
{
    using namespace std;
    os << "[";
    forEach(lst, [&os](T v) {
        os << v << " ";
    });
    os << "]";
    return os;
}

int asNumber(std::initializer_list<int> const & v)
{
    int acc = 0;
    for (auto i : v)
    {
        acc = 10 * acc + i;
    }
    return acc;
}

/******************************************************************************/
// Monad:
template<typename State>
struct StateLM
{
    template<typename T>
    struct apply
    {
        using type = StateL<State, T>;
    };
};

// Adaptation:
template<typename State>
struct MonadUnit<StateLM<State>>
{
    template<typename T> auto operator()(T x) const
    {
        return mreturn<State>(x);
    }
};

template<typename State>
struct MonadGuard<StateLM<State>>
{
    auto operator()(bool x) const
    {
        return mguard<State>(x);
    }
};

template<class State, class A, class F>
auto operator>>=(StateL<State, A> g, F k)
{
    return mbind(g, k);
}
/******************************************************************************/
auto solve()
{
    using StateLI = StateLM<List<int>>;
    StateLI::apply<int>::type sel = &select<int>;
    return DO(StateLI,
            (s, sel)
            (e, sel)
            (n, sel)
            (d, sel)
            (m, sel)
            (o, sel)
            (r, sel)
            (y, sel)
            (_, guard(s != 0 && m != 0))
            (_, [=]{
                auto send  = asNumber({s, e, n, d});
                auto more  = asNumber({m, o, r, e});
                auto money = asNumber({m, o, n, e, y});
                return DO(StateLI,
                            (_, guard(send + more == money))
                            (_, unit(make_tuple(send, more, money)))
                );
            }())
    );
}

int main()
{
    List<int> lst{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cout << evalStateL(solve(), lst);
    return 0;
}