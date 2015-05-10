#include <cstdlib>
#include <iostream>
#include <ctime>
 
int main()
{
    std::srand(std::time(0)); //use current time as seed for random generator
    int uniform_random_variable = std::rand();
    std::cout << "Uniform random value on [0 " << RAND_MAX << "]: "
              << uniform_random_variable << '\n';
}