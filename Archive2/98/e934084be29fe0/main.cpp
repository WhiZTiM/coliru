#include <range/v3/all.hpp>
#include <vector>
#include <tuple>
#include <iostream>

struct Example
{
    void sortByMarks(){
        ranges::sort(ranges::view::zip(marks, ids));
    }
    
    std::vector<int> ids = {1,2,3,4,5};
    std::vector<int> marks = {47,44,88,52,46};
};


int main() {
    Example e;
    e.sortByMarks();
    std::cout << (e.ids | ranges::view::all) << '\n';
    std::cout << (e.marks | ranges::view::all) << '\n';
}
