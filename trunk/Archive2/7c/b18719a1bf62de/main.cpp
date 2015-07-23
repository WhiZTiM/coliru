/*
Finds the sum of all inputed multipliers below a certain number
For example, it could find the sum of all the multiples of 3 and 5 less than
or equal to 1000

Written By Jay Schauer
*/

// Data Declarations
#include <iostream>
#include <algorithm>
#include <vector>

int main() {

    std::cout << "Enter the number of multipliers you would like to use (up to 50)" << std::endl;
    //std::cout << "(for example, enter '2' if you would like to use two multipliers, maybe 3 and 5?)" << std::endl;
    int number_of_multipliers; // Stores the number of multipliers being used

    std::vector<int> multipliers;
    if (std::cin >> number_of_multipliers)
    {
        std::cout << "Next, you will enter the mutliples you want to use." << std::endl;
        std::cout << "(for example, if you want to find the sum of the multipliers of 3 and\n5 below a given amount, enter 3 as 'multiplier 1' and 5 as 'multiplier 2')" << std::endl;

        while (number_of_multipliers) {
            std::cout << "Enter 'multiplier " << (multipliers.size() + 1) << "'" << std::endl;
            int multiplier;
            if (std::cin >> multiplier) {
                number_of_multipliers -= 1;
                multipliers.push_back(multiplier);
            } else {
                if (!std::cin.eof()) {
                    std::cout << "Oops. Input couldn't be parsed. Try again";
                    std::cin.clear();
                    std::cin.ignore(1ul<<20, '\n');
                } else {
                    std::cout << "Goodbye\n";
                    return 255;
                }
            }
        }

        std::cout << "Enter the the limit for how high you want to add the multipliers" << std::endl;
        std::cout << "(for example, you could set the limit to 1000 to find the sum of the\nmultipliers of 3 and 5 (if you entered those) less than and or equal to 1000)" << std::endl;

        int limit; // Stores the limit
        if (std::cin >> limit) {
            std::cout 
                << "The sum is " << std::accumulate(
                    multipliers.begin(), multipliers.end(), 0ul,
                    [limit](unsigned long accum, int multiplier) { return (limit + multiplier) * (limit / multiplier) / 2; })
                << std::endl;
        }
    }

}
