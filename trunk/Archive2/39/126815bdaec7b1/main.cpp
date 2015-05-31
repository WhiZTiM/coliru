#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>

#include <iostream>
#include <vector>

struct X : boost::enable_shared_from_this<X> {
    int i = rand()%100;

    using Ptr = boost::shared_ptr<X>;
    void hold() {
        _hold = shared_from_this();
    }

    void unhold() { _hold.reset(); }

    ~X() {
        std::cout << "~X: " << i << "\n";
    }
  private:
    Ptr _hold;
};

int main() {
    X* raw_pointer = nullptr; // we abuse this for demo

    {
        auto some_x = boost::make_shared<X>();

        // not lets addref from inside X:
        some_x->hold();

        // now we can release some_x without destroying the X pointed to:
        raw_pointer = some_x.get(); // we'll use this to demo `unhold()`
        some_x.reset();
    }

    raw_pointer->unhold(); // now it's gone ("self-delete")
}
