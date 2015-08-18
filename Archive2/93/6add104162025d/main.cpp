#include <boost/multi_index/ordered_index_fwd.hpp>
#include <boost/multi_index/hashed_index_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/front.hpp>

template<typename Index>
struct is_key_based_index:boost::mpl::false_{};

template<typename... Args>
struct is_key_based_index<
  boost::multi_index::ordered_unique<Args...>
>:boost::mpl::true_{};

template<typename... Args>
struct is_key_based_index<
  boost::multi_index::ordered_non_unique<Args...>
>:boost::mpl::true_{};

template<typename... Args>
struct is_key_based_index<
  boost::multi_index::hashed_unique<Args...>
>:boost::mpl::true_{};

template<typename... Args>
struct is_key_based_index<
  boost::multi_index::hashed_non_unique<Args...>
>:boost::mpl::true_{};

template<typename MultiIndexContainer>
struct is_first_index_key_based:
  is_key_based_index<
    typename boost::mpl::front<
      typename MultiIndexContainer::index_specifier_type_list
    >::type
  >
{};

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
