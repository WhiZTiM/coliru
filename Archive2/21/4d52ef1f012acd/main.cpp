#include <type_traits>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <chrono>
#include <atomic>
#include <iostream>
#include <future>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <cassert>
using namespace std;

struct data_map_hash {
    size_t operator()(const tuple<int,int>& t) const {
        std::size_t h1 = std::hash<int>()(get<0>(t));
        std::size_t h2 = std::hash<int>()(get<1>(t));
        return h1 ^ (h2 << 1);
    }
};
unordered_map<tuple<int, int>, int, data_map_hash> map;

int main() {
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 20; ++j)
            map[make_tuple(i, j)] = i * j;
    assert(map.size() == 201);
}