#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>

struct Person {
    Person(int id, std::string name):
        m_id(id),
        m_name(name)
    {
    }

    int m_id;
    std::string m_name;
};

namespace bmi = boost::multi_index;

typedef boost::multi_index_container<
    Person,
    bmi::indexed_by<
        bmi::ordered_unique<
            bmi::member<Person, int, &Person::m_id>
        >,
        bmi::ordered_unique<
            bmi::composite_key<
                Person,
                bmi::member<Person, std::string, &Person::m_name>,
                bmi::member<Person, int, &Person::m_id>
            >
         >,
        bmi::ordered_unique<bmi::tag<struct by_name>, bmi::member<Person, std::string, &Person::m_name>
        >
    >
> Roster;

#include <iostream>

int main()
{
    Roster r;
    r.insert(Person(1, "Tom"));
    r.insert(Person(2, "Jack"));
    r.insert(Person(3, "Tom"));
    r.insert(Person(4, "Leo"));

    /* The distinct count of name must be 3 */
    std::cout << r.get<by_name>().size();
}
