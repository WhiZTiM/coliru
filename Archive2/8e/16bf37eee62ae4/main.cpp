#include <vector>

int main(){
    std::vector<int> v;

    for (auto&& e : v) try {} catch (...) {}
}