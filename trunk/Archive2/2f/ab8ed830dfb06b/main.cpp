#include <iostream> 
#include <sstream>

const int SENTINEL = 0;

/* Main Program */
int main()
{
    std::cout << "This program finds the largest integer in a list.";
    std::cout << "\nEnter " << SENTINEL << " to signal the end of the input.\n";
    std::istringstream in("8 !");
    int largest = SENTINEL;

    while (true)
    {
        int value; 
        std::cout << "\nPlease enter an integer: ";  
        in >> value;

        if (value == SENTINEL) 
            break;
        largest = (value > largest) ? value : largest; 
    }

    std::cout << "\nThe largest value is " << largest << ".\n\n";
}