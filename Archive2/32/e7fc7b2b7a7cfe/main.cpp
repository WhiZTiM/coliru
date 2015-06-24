#include <exception>
#include <iostream>
#include <sstream>
#include <vector>
#include <boost/algorithm/string/join.hpp>

auto bar() -> void try {
    throw std::runtime_error("couldn't open something for some reason or whatever");
} catch (...) {
    std::throw_with_nested(std::runtime_error(__func__));
}

auto foo() -> void try { 
    bar();
} catch (...) {
    std::throw_with_nested(std::runtime_error(__func__));
}

auto nested_whats(std::exception const& e) -> std::vector<std::string> {
    std::vector<std::string> whats;
    whats.emplace_back(e.what());
    
    try {
        std::rethrow_if_nested(e);
    } catch (const std::exception& e) {
        auto nested = nested_whats(e);
        std::move(nested.begin(), nested.end(), std::back_inserter(whats));
    }
    
    return whats;
}

int main() try {
    foo();
} catch (std::exception const& e) {
    std::cout << boost::algorithm::join(nested_whats(e), ": ") << std::endl;
}