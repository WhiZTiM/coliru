#include <iostream>
#include <boost/circular_buffer.hpp>

int main() {
    boost::circular_buffer<int> cb(10); // [tag:cb-so-fixedsize] obviously

    for (int msg : { 3, 5, 6, 9, 2, 8, 6, 7 }) {
        cb.push_back(msg);
    }

    // should be 2
    std::cout << "t0-5: " << cb[4] << "\n";
    std::cout << "t0-5: " << *std::next(cb.begin(), 4) << "\n";
    
    // should be 9
    std::cout << "t0-5: " << cb[3] << "\n";
    std::cout << "t0-5: " << *std::next(cb.begin(), 3) << "\n";

    while (!cb.empty()) {
        std::cout << cb.front() << " ";
        cb.pop_front();
    }
}
