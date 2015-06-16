#include <vector>
#include <iostream>

using namespace std;

struct Inner
{
public:
    float A;
    unsigned short B;    

    Inner()
        :A(0.0F), B(0)
    {
    }

    Inner(const float& valA, const unsigned short& valB)
        : A(valA), B(valB){}        
};

class Outer
{
private:
    const vector<Inner> CollectionOfInner;

public:
    Outer(const vector<Inner> initialVal = { Inner(1.0F, 4), Inner(9.0F, 4), Inner(81.0F, 18) })
        : CollectionOfInner(initialVal)
    {
        cout << "Values" << '\n';
        //for each (Inner value in CollectionOfInner)
        for (Inner value : CollectionOfInner)
        {
            cout << "A: " << value.A << " B: " << value.B << '\n';
        }
    }    
};

int main() {
    
    Outer var;
    
}