#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <array>
#include <thread>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <mutex>
using namespace std;

constexpr int N = 10;
mutex m;
array<int, N> accounts;

struct chronometer {
    chronometer()
        { start_time_ = chrono::steady_clock::now(); }
    ~chronometer() {
        cout << chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start_time_).count() << "ms" << endl;
    }
    chrono::steady_clock::time_point start_time_;
};
    
void transfer(unsigned int from, unsigned int to, unsigned int amount) {
//    lock_guard<mutex> lock(m);
    accounts[from] -= amount;
    accounts[to] += amount;
}

int get_rand() {
    static random_device rd;
    static uniform_int_distribution<unsigned int> dist(0, N-1);
    return dist(rd);
}

void test() {
    accounts.fill(0);
    vector<thread> threads;
    for (int i = 0; i < 30; ++i) {
        threads.push_back(thread([]() { 
            for (int j = 0; j < 10000; ++j) {
                auto from = get_rand();
                auto to = get_rand();
                transfer(from, to, 1);
            }
        }));
    }
    for_each(threads.begin(), threads.end(), [](thread& t) { t.join(); });
    for (auto& a : accounts) { cout << a << ", "; } cout << endl;
    cout << accumulate(accounts.begin(), accounts.end(), 0) << endl;
}

int main() {
    chronometer _;
    for (int i = 0; i < 1; ++i) {
        test();
    }
    return 0;
}
