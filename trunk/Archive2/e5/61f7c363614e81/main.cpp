#include <stdio.h>
#include <vector>

class base_type {
public:
    base_type(base_type&& other)
    {
        std::swap(value_, other.value_);
    }

    virtual ~base_type()
    {
        printf("Destroying with value %d\n", value_);
    }

protected:
    base_type()
        : value_(1234)
    {
    }
    
    int value_;
}; /* class base_type */

class derived_type : public base_type {
public:
    derived_type()
    {
        value_ = 4321;
    }
}; /* class derived_type */

int main(int argc, char* argv[])
{
    std::vector<base_type> container;
    container.reserve(1);

    derived_type item;
    container.push_back(std::move(item));
    return 0;
}