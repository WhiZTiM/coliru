#include <random>
#include <iostream>

int main() {
    using namespace std;

    random_device rng;
    uniform_int_distribution<int> random(1, 10);
    cout << random(rng) << endl;
}