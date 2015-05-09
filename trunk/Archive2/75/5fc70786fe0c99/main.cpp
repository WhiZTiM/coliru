#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

template<class Cont, class Pred>
bool anyOf(Cont&& c, Pred p) {
    using std::begin; using std::end;
    return std::any_of(begin(c), end(c), p);
}

template<class Cont, class F1, class... Rest>
bool anyOf(Cont&& c, F1 f, Rest... rest) {
    return anyOf(std::forward<Cont>(c), [&](auto&& a){ 
        return anyOf(std::ref(f)(std::forward<decltype(a)>(a)), rest...); 
    });
}

struct Animal { virtual ~Animal() = default; };
struct Dog : Animal {};

struct Person {
    std::vector<struct Toddler*> children;
    const std::vector<Toddler*>& getChildren() const {return children;}
};

struct Toddler : Person {
    std::vector<Animal*> pets;
    const std::vector<Animal*>& getPets() const {return pets;}
};

int main() {
    Person* bob = new Person;
    Toddler* tom = new Toddler;
    tom->pets.push_back(new Dog);
    bob->children.push_back(tom);
    std::vector<Person*> people = {tom, bob};

    // Output: Does anybody in 'people' have a child that has a pet that is a dog?
    std::cout << std::boolalpha << anyOf (people, &Person::getChildren, &Toddler::getPets,
    [](const Animal* a) {return dynamic_cast<const Dog*>(a) != nullptr;}) << std::endl;
}