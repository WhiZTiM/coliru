#include <vector>
#include <chrono>
#include <iostream>
#include <string>
#include <stdexcept>

// RAII timer
struct Timer {
    using clock = std::chrono::high_resolution_clock;
	using time_point = std::chrono::time_point<clock>;
	time_point start = clock::now();
    
	std::string name;

	Timer(std::string name_) : name(name_) {}

	double get_duration(){
		return std::chrono::duration<double>{clock::now() - start}.count();
	}

	~Timer(){
		std::cout << name << " took: " << get_duration() << " seconds" << std::endl;
	}
};


class Day {
    public:
    unsigned day = 0;
};

int main(){
    #define TYPE unsigned
    std::vector<TYPE> numbers;
    
    unsigned days_to_create = 10'000'000;
    numbers.reserve(days_to_create);

    for(unsigned i = 0; i < days_to_create; ++i){
		auto number = 1 + (i % 31);
        numbers.push_back(TYPE{number});
    }
    
    for(int i = 0; i < 10; ++i){
        {
            Timer t("Copying");
            auto copy = numbers;
        }
    }
}
