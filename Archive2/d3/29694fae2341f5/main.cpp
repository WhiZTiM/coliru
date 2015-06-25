//#include <type_traits>
//#include <functional>
//#include <iostream>
//#include <string>
//#include <vector>
//#include <queue>
//#include <thread>
//#include <chrono>
//#include <atomic>
#include <iostream>
#include <fstream>
//#include <future>
//#include <thread>
//#include <mutex>
//#include <unordered_map>
//#include <cassert>
//#include <sstream>
//#include <type_traits>
using namespace std;
#include <stdio.h>
#include <stdlib.h>

int main() {
    ofstream f("test.txt");
    if (f.rdstate() == std::ios_base::badbit) {
        cout << "failed" << endl;
    }
    f << "test" << endl;
}