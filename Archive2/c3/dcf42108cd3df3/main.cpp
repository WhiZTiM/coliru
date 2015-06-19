#include <iostream>
#include <string>
#include <cstdlib>

using uint = uint32_t;

template<uint SceneInstance, typename T>
struct Counter
{
    static uint const index;
};

template<uint SceneInstance>
struct SharedCount
{
    template<typename T>
    static uint getNext()
    {
        uint c = counter;
        counter++;

        return c;
    }

    static uint counter;
};

template<uint SceneInstance>
uint SharedCount<SceneInstance>::counter = 0;


template<uint SceneInstance,typename T>
uint const Counter<SceneInstance,T>::index(
        SharedCount<SceneInstance>::getNext<T>());
        
        
int main()
{
    
    return 0;
}