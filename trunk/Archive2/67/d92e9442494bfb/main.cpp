#include <iostream>
#include <vector>

int main()
{
    std::vector<int> integer_list; //vector is the best fit for container in your case until proved otherwise
    constexpr int max_count = 111;
    for(int count = 0; count < max_count; ++count) {
        if(count % 10 == 0)
            integer_list.push_back(count); //Adds a new integer to the end of integer_list container
    }
    for(int i : integer_list)
        std::cout << i << ' ';
}