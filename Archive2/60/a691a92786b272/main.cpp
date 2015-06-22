#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <future>
#include <sstream>
#include <chrono>
#include <ctime>
#include <limits>
#include <cassert>
#include <type_traits>
#include <typeinfo>
#include <array>
#include <tuple>
#include <queue>
#include <functional>
#include <atomic>
#include <algorithm>
#include <map>
#include <cstdint>
#include <unordered_map>
#include <cfloat>
#include <cstring>
#include <list>
#include <climits>

#include <stdio.h>
#include <stdlib.h>
#include <fnmatch.h>
#include <glob.h>

#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>
#include <new>

#include <signal.h>

struct A : public std::string {
    A(const char* s): std::string(s) {
    }
    
    ~A() {
        std::cout << "~A()" << std::endl;
    }
};

void func(const char* s) {
    std::cout << "func" << std::endl;
    std::cout << std::string(s) << std::endl;
}

int main(int argc, char **argv) {
    func(A("abc").c_str() + 1);
}