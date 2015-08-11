#include <iostream>
#include <string>

class Animal {

    public:

        std::string voice = ".";

        Animal() = default ; // default voice

        void speak() const {
            std::cout << voice << ' ' << this->voice << ' '
                      << Animal::voice << ' ' << this->Animal::voice << '\n' ;
        }

    // the constructor of a derived class can specify what its voice is
    protected: Animal( const std::string& its_voice ) : voice(its_voice) {}
};

class Dog : public Animal {

    public: Dog() : Animal( "Whoof!" ) {} // this animal's voice is  "Whoof!"
};

int main() {

    const Animal a{} ; const Animal& a1 = a ; const Animal* pa1 = std::addressof(a) ;
    const Dog d ; const Animal& a2 = d ; const Animal* pa2 = std::addressof(d) ;

    a.speak() ; a1.speak() ; pa1->speak(); // Prints . . . . three times
    d.speak() ; a2.speak(); pa2->speak() ; // Prints "Whoof!" "Whoof!" "Whoof!" "Whoof" thrice
}
