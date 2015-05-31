#include <iostream>
#include <string>
#include <list>
#include <functional>
#include <algorithm>

using namespace std;

struct Person {
    string name;
    ostream& print(ostream& out) const {
        return out << name;
    }
};
int main(int argc, char* argv[])
{
    Person p = { "Mark" };
    list<Person> l;
    l.push_back(p);
    for_each(l.begin(), l.end(), bind(&Person::print, std::placeholders::_1, std::ref(std::cout))); // this placeholder is not a pointer so it can't work anyways

    // I also tried something with lambdas like: for_each(l.begin(), l.end(), bind([](Person& p, ostream& out) { (p.*)(out); }, std::placeholders::_1, cout); but it doesn't work either
    //for_each(l.begin(), l.end(), bind([](Person& p, ostream& out) { mem_fun(&Person::print)(&p, out); }, std::placeholders::_1, cout));

    // it doesn't even work that way
    //for_each(l.begin(), l.end(), bind([](Person& p, ostream& out) { p.print(out); }, std::placeholders::_1, cout));
return 0;
}