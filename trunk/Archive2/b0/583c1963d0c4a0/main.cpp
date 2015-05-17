#include <random>
#include <iostream>

int main() {
    using namespace std;

    mt19937 prng{random_device()()};
    uniform_int_distribution<int> random(1, 10);
    cout << random(prng) << endl;
    cout << random(prng) << endl;
}