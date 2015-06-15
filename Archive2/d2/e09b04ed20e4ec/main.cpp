#include <memory>
#include <iostream>

struct some_type
{
    some_type(int k ) : value(k) {}

    int get_value() const { return value; }

private:
    int value;
};

void function(std::shared_ptr<some_type>& tp)
{
    int val = tp->get_value();
    std::cerr <<  val  << std::endl;
}

int main(int argc, char* argv[])
{
    auto some = std::make_shared<some_type>(10);
    function(some);
    return 0;
}

