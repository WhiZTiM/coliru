#include <boost/multi_index_container_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/front.hpp>

template<typename Value,typename Index>
using mono_index_container=
boost::multi_index_container<
  Value,
  boost::multi_index::indexed_by<Index>
>;

template<typename T>
struct void_t
{
  typedef void type;
};

template<typename MultiIndexContainer,typename=void>
struct is_first_index_key_based:boost::mpl::false_{};

template<typename MultiIndexContainer>
struct is_first_index_key_based<
  MultiIndexContainer,
  typename void_t<
    typename mono_index_container<
      typename MultiIndexContainer::value_type,
      typename boost::mpl::front<
        typename MultiIndexContainer::index_specifier_type_list
      >::type
    >::key_type
  >::type
>:boost::mpl::true_{};

/* testing */

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/identity.hpp>

int main()
{
  using namespace boost::multi_index;
  
  static_assert(is_first_index_key_based<
    multi_index_container<
      int,
      indexed_by<
        ordered_unique<identity<int>>
      >
    >
  >::value,"");
  static_assert(is_first_index_key_based<
    multi_index_container<
      int,
      indexed_by<
        ordered_non_unique<identity<int>>,
        sequenced<>
      >
    >
  >::value,"");
  static_assert(is_first_index_key_based<
    multi_index_container<
      int,
      indexed_by<
        hashed_unique<identity<int>>
      >
    >
  >::value,"");
  static_assert(is_first_index_key_based<
    multi_index_container<
      int,
      indexed_by<
        hashed_non_unique<identity<int>>,
        random_access<>
      >
    >
  >::value,"");
  static_assert(!is_first_index_key_based<
    multi_index_container<
      int,
      indexed_by<
        sequenced<>
      >
    >
  >::value,"");
  static_assert(!is_first_index_key_based<
    multi_index_container<
      int,
      indexed_by<
        random_access<>,
        ordered_unique<identity<int>>
      >
    >
  >::value,"");
}
