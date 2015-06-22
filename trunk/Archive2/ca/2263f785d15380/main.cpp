#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <iostream>

using namespace std;
using namespace boost::multi_index;

struct Person {
    Person(int id, string name):
        m_id(id),
        m_name(name)
    {
    }

    int m_id;
    string m_name;
};

typedef multi_index_container<
    Person,
    indexed_by<
        ordered_unique<
            member<Person, int, &Person::m_id>
        >,
        ordered_unique<
            composite_key<
                Person,
                member<Person, string, &Person::m_name>,
                member<Person, int, &Person::m_id>
            >
         >
    >
> Roster;

template<typename Index,typename KeyExtractor>
std::size_t distinct(const Index& i,KeyExtractor key)
{
  std::size_t res=0;
  for(auto it=i.begin(),it_end=i.end();it!=it_end;){
    ++res;
    it=i.upper_bound(key(*it));
  }
  return res;
}

int main()
{
    Roster r;
    r.insert(Person(1, "Tom"));
    r.insert(Person(2, "Jack"));
    r.insert(Person(3, "Tom"));
    r.insert(Person(4, "Leo"));
    
    auto d=distinct(r.get<1>(),[](const Person& p){return std::cref(p.m_name);});
    std::cout<<d<<"\n";
}
