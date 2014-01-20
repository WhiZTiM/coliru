#include <nonius/benchmarks.hpp>

#include <string>

NONIUS_BENCHMARK("to_string ints") -> std::string {
    return std::to_string(42);
}

NONIUS_BENCHMARK("to_string doubles") -> std::string {
    return std::to_string(42.0);
}
