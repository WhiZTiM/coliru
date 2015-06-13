#include <iostream>
#include <vector>

class MyArray : public std::vector < double >
{
public:
    virtual double& operator[](const size_type& index)
    {
        #ifdef DEBUG_ENABLED
            return this->at(index);
        #else
            return std::vector<double>::operator[](index);
        #endif
    }
};

int main()
{
    MyArray x;
    x.resize(4);
    x[5] = 10;
}