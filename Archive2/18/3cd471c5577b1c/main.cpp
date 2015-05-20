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
    std::vector<Day> days;
    std::vector<unsigned> numbers;
    
    unsigned days_to_create = 10'000'000;
    days.reserve(days_to_create);
    numbers.reserve(days_to_create);
    
    std::cout << "Unsigned in bytes: " << sizeof(unsigned) << " Day size in bytes: " << sizeof(Day) << std::endl;
    std::cout << "Creating " << days_to_create << " days" << std::endl;
    {
        Timer t("Creating days");
        for(unsigned i = 0; i < days_to_create; ++i){
			auto number = 1 + (i % 31);
            days.push_back(Day{number});
            numbers.push_back(number);
        }
    }
    
    {
        Timer t("Copying days");
        auto days_copy = days;
    }
    
    {
        Timer t("Copying numbers");
        auto numbers_copy = numbers;
    }
}
