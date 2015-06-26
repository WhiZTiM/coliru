#include <iostream>

class Thisthing
{
    public:
        virtual ~Thisthing() {} // = default ; // http://www.stroustrup.com/C++11FAQ.html#default

        virtual void Eatsomething() const // const
        {
            std::cout << "He is being eaten\n" ; // << endl;
        }
    private:
        // int Dont_Eat_Him = 0 ; // http://www.stroustrup.com/C++11FAQ.html#member-init
};

class Bringit : public Thisthing // note: public
{
    public:
        virtual void Eatsomething() const // override // http://www.stroustrup.com/C++11FAQ.html#override
        {
            std::cout << "He's going to be ate\n" ; // << endl;
        }
};

int main()
{
    Thisthing* pointer = 0 ; // = nullptr; // http://www.stroustrup.com/C++11FAQ.html#nullptr

    Bringit bring_it ;
    pointer = &bring_it ; // = std::addressof(bring_it); // http://en.cppreference.com/w/cpp/memory/addressof
    pointer->Eatsomething();

    Thisthing this_thing ;
    pointer = &this_thing ; // = std::addressof(this_thing);
    pointer->Eatsomething();
}
