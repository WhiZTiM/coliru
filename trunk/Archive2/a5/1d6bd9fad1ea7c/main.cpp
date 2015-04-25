#include <iostream>
#include <stdio.h>
#include <chrono>

const int N = 1000000;

std::string make_long_string() {
    std::string s;
    for (int i = 0; i < N; ++i)
        s += "1 ";
    return s;
}

int main(int argc, char** argv) {
    std::string arg = argv[1];
    if (arg == "generate") {
        std::cout << make_long_string() << std::endl;
    } else if (arg == "iostream") {
        auto t1 =  std::chrono::high_resolution_clock::now();
        int sum = 0;
        for (int i = 0; i < N; ++i) {
            int a;
            std::cin >> a;
            sum += a;
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = t2 - t1;
        std::cout << "iostreams: sum = " << sum << ", time = " << diff.count() << std::endl;
    } else if (arg == "scanf") {
        auto t1 =  std::chrono::high_resolution_clock::now();
        int sum = 0;
        for (int i = 0; i < N; ++i) {
            int a;
            scanf("%d", &a);
            sum += a;
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = t2 - t1;
        std::cout << "scanf: sum = " << sum << ", time = " << diff.count() << std::endl;
    }
}