#include<set>
#include<functional>
#include<algorithm>
#include<memory>
#include<iostream>

    struct Person {
        // lots of other values
        Person(std::string n) : name(n) {}
        std::string name;
    };


    auto set_order = [](auto const& p, auto const& q) { return p->name < q->name; };

    std::set<std::shared_ptr<Person>, decltype(set_order) > people(set_order);

    void insertPerson(std::shared_ptr<Person>& p) {
        people.insert(p);
    }

    std::shared_ptr<Person> lookupPerson(std::string const& s)
    {
        auto comp =  [](auto const& p, auto const& s) { return p->name < s; };
        return *std::lower_bound(std::begin(people), std::end(people), s, comp);
    }

int main()
{
    people.emplace(std::make_shared<Person>("Paul"));
    people.emplace(std::make_shared<Person>("Mary"));
    
    std::cout<<lookupPerson("Mary")->name<<std::endl;
}