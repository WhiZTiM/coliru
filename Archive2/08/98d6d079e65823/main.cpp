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
#include <fstream>
#include <future>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <cassert>
#include <sstream>
#include <type_traits>
using namespace std;
#include <stdio.h>
#include <stdlib.h>

int main() {
    constexpr auto size = 101u;
    constexpr auto num_threads = 5u;
    constexpr auto num_frames = 10u;
    using atomic_matrix = array<array<atomic<int>, size>, num_threads>;
    using matrix = array<array<int, size>, num_threads>;
    
    matrix data;
    for (auto& row : data) {
        for (auto& c : row) {
            c = 0;
        }
    }

    array<atomic<bool>, num_threads> init_flag;
    for (auto& f : init_flag)
        { f = false; }

    atomic<bool> start_flag(false);
    
    vector<matrix> history[5];
    
    auto f = [&start_flag, &data, &init_flag, &history](int idx) {
        init_flag[idx] = true;
        while (!start_flag);
        
        for (auto f = 0u; f < num_frames; ++f) {
            for (auto i = 1u; i < size; ++i) {
                ++data[idx][i];
                ++data[idx][0];
            }
            matrix sample;
            for (auto i = 0u; i < num_threads; ++i) {
                for (auto j = 0u; j < size; ++j) {
                    sample[i][j] = data[i][j];
                }
            }
            history[idx].push_back(sample);
        }
    };
    
    array<future<void>, num_threads> tasks;
    for (auto i = 0u; i < num_threads; ++i) {
        tasks[i] = async(launch::async, f, i);
    }

    while(true) {
        bool should_start = true;
        for (auto i = 0u; i < num_threads; ++i) {
            should_start = should_start && init_flag[i];
        }
        if (should_start) {
            break;
        }
    }
    start_flag = true;
    for (auto& t : tasks) {
        t.get();
    }
    
    auto prnt = [](matrix& data) {
        for (auto idx = 0u; idx < num_threads; ++idx) {
            for (auto i = 0u; i < size; ++i) {
                cout << data[idx][i] << " ";
            }
            cout << endl;
        }
    };
    
    for (auto f = 0u; f < num_frames; ++f) {
        cout << "In frame " << f << ":" << endl;
        for (auto idx = 0u; idx < num_threads; ++idx) {
            cout << "   Thread " << idx << " saw:" << endl;
            prnt(history[idx][f]);
        }
    }
}