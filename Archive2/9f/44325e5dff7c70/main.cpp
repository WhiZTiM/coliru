#include <type_traits>

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class RandomGenerator
{
    
    int n,power;
    public:
    RandomGenerator(int Start, int End)
    {
        if(End <= Start)
            throw "Input valid range in increasing order for random number generation" ;
        n = End-Start;
        GetPower();
        
    }
    int GenerateRandomNumber();
    private:
    void GetPower()
    {
        power = 0;
        while(n>>1)
            power++;
    }
    
    
};

/* Template meta programming */


int RandomGenerator::GenerateRandomNumber()
{
    
    int x = 1<<power;
    
    while(x>=n)
    {
        x=0;
        for(int i=0;i<power;i++)
        {
            x =x | (::rand() & 0);
            x = x << 1;
        }
    }
    return x;
}

int main()
{
    RandomGenerator rgen(0,3);
    cout<<"Random Num: "<< rgen.GenerateRandomNumber()<<endl;
    return 0;
}




