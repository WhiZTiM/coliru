#include <iostream>
#include <stdlib.h>

using namespace std;


void randtest(unsigned int seed, int* output, int count)
{
    srand (seed);
    
    for(int i = 0; i < count; i++)
    {
        output[i] = rand() % 100 + 1;
        cout << output[i] << " ";
    }
    
    cout << "\n";

}

int main()
{
    unsigned int seed;
    const int count = 5;
    int num[count];

    seed = 1;    
    cout << "seed = 1 , first:  ";
    randtest(seed, num, count);
    
    cout << "seed = 1 , second: ";
    randtest(seed, num, count);

    seed = 2;
    cout << "\nseed = 2 , first:  ";
    randtest(seed, num, count);
    
    cout << "seed = 2 , second: ";
    randtest(seed, num, count);

}
