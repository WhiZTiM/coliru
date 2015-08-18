#include <boost/signals2.hpp>
#include <boost/make_shared.hpp>
#include <boost/weak_ptr.hpp>
#include <iostream>

class Foo : public boost::signals2::trackable {
public:
    void bar() {
        printf("Fire!\n");
    }
};

int main() {
    boost::signals2::signal<void()> signal;
    {
        auto test = boost::make_shared<Foo>();
        auto weak = boost::weak_ptr<Foo>(test);

        signal.connect([weak] 
                { 
                    if (auto sp = weak.lock()) 
                        sp->bar(); 
                    else
                        std::cout << "expired\n";
                }
            );

        signal();
    }
    signal();
}
