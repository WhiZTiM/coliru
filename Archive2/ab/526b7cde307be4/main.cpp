#include <cstdlib>
#include <iostream>
#include <ctime>
 
int main() 
{
    std::srand(43); // use current time as seed for random generator
    int random_variable = 12+std::rand()%100;
    std::cout << "Random value on [0 " << RAND_MAX << "]: " 
              << random_variable << '\n';
}