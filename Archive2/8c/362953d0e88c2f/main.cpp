#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>

using namespace boost::multi_index;

struct struct1{};
struct struct2{};
struct struct3{};
struct struct4{};

typedef multi_index_container<
 int,
 indexed_by<
  ordered_unique<tag<struct1>,identity<int>>,
  ordered_unique<tag<struct2,struct3>,identity<int>>,
  ordered_unique<tag<struct4>,identity<int>>
 >
> multi_t;

#include <boost/mpl/at.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>

template<typename Map,typename Index>
struct add_to_iterator_to_tag_map:
  boost::mpl::fold<
    typename Index::tag_list,
    Map,
    boost::mpl::insert<
      boost::mpl::_1,
      boost::mpl::pair<typename Index::iterator,boost::mpl::_2>
    >
  >
{};
  
template<typename MultiIndexContainer>
struct iterator_to_tag_map:
  boost::mpl::fold<
    typename MultiIndexContainer::index_type_list,
    boost::mpl::map<>,
    add_to_iterator_to_tag_map<boost::mpl::_1,boost::mpl::_2>
  >
{};

template<typename MultiIndexContainer,typename Iterator>
struct tag_from_iterator:
  boost::mpl::at<
    typename iterator_to_tag_map<MultiIndexContainer>::type,
    Iterator
  >
{};
  
#include<iostream>

int main()
{
  using iterator1=multi_t::nth_index<0>::type::iterator;
  using iterator2=multi_t::nth_index<1>::type::iterator;
  using iterator3=multi_t::nth_index<2>::type::iterator;
  
  std::cout<<typeid(tag_from_iterator<multi_t,iterator1>::type).name()<<"\n";
  std::cout<<typeid(tag_from_iterator<multi_t,iterator2>::type).name()<<"\n";
  std::cout<<typeid(tag_from_iterator<multi_t,iterator3>::type).name()<<"\n";
}
