#include<type_traits>
#include<iostream>

    template<int N> void runSimulation() { std::cout<<"runSimulation " << N<<std::endl; }
    
    //overload for maximum index
    constexpr size_t max_index = 100;
    void callSimulation_impl(size_t i, std::integral_constant<size_t, max_index>) {}
    
    template<size_t N>
    void callSimulation_impl(size_t i, std::integral_constant<size_t, N>)
    {
        if(i==N)
        {
            runSimulation<N>();
        }
        else
        {
            callSimulation_impl(i, std::integral_constant<size_t, N+1>());
        }
    }
    
    void callSimulation(size_t i)
    {
        callSimulation_impl(i, std::integral_constant<size_t, 0>());
    }


    int main(int argc, char *argv[])
    {
        callSimulation(10);   // calls runSimulation<10>();

        //or also:

        callSimulation(rand()%max_index);
    }
    