#include <type_traits>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

struct safe_tag {};

template<class T, class P = void>
struct safe : public safe_tag {
    T m_t;
    typedef P PromotionPolicy;
};

template<class T>
struct is_safe : public
    //std::is_arithmetic<T>
    std::is_base_of<safe_tag, T>
{};

template<class T, class U>
struct common_policies {
    static_assert(
        boost::mpl::or_<
            is_safe<T>,
            is_safe<U>
        >::value,
        "at least one type must be a safe type"
    );

    template<typename Z>
    struct get_promotion_policy {
        static_assert(
            is_safe<Z>::value,
            "only safe types have promotion policies"
        );
        typedef typename Z::PromotionPolicy type;
    };


    // if both types are safe, the policies have to be the same!
    static_assert(
        boost::mpl::eval_if<
            boost::mpl::and_<
                is_safe<T>,
                is_safe<U>
            >,
            std::is_same<
                typename boost::mpl::eval_if<is_safe<T>, get_promotion_policy<T>, boost::mpl::identity<void>>::type,
                typename boost::mpl::eval_if<is_safe<U>, get_promotion_policy<U>, boost::mpl::identity<void>>::type
            >,
            boost::mpl::identity<boost::mpl::true_>
        >::type::value,
        "if both types are safe, the policies have to be the same!"
    );

    // now we've verified that there is no conflict between policies
    // return the one from the first safe type
    typedef typename boost::mpl::if_<
        is_safe<T>,
        T,
    typename boost::mpl::if_<
        is_safe<U>,
        U,
    //
        boost::mpl::void_
    >::type
    >::type safe_type;

    typedef typename get_promotion_policy<safe_type>::type promotion_policy;

};

common_policies<int, safe<int> > t;

int main(){
    return 0;
}