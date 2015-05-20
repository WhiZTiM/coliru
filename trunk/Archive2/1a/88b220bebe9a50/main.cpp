#include <iostream>
#include <algorithm>
  
class Array {
public:
    int size;
    int* data;
 
    Array(int sz) : size(sz), data(new int[size])
    {
    }
    
    Array(const Array& other) : size(other.size), 
                                data(new int[other.size]) 
    {
        std::copy(other.data, other.data + other.size, data); 
    }
    
    Array & operator= (const Array & other)
    {
        if (this != &other) // protect against invalid self-assignment
        {
            // 1: allocate new memory and copy the elements
            int* new_data = new int[other.size];
            std::copy(other.data, other.data + other.size, new_data);
 
            // 2: deallocate old memory
            delete [] data;
 
            // 3: assign the new memory to the object
            data = new_data;
            size = other.size;
        }
        // by convention, always return *this
        return *this;
    }
 
    ~Array() 
    {
        delete[] this->data;
    }
};
 
int main() 
{
    Array first(20);
    first.data[0] = 25;
 
    {
        Array copy = first;
        std::cout << first.data[0] << " " << copy.data[0] << std::endl;
    }    // (1)
 
    first.data[0] = 10;    // (2)
}