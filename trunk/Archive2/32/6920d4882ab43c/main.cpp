#include <iostream>
#include <chrono>


template < class duration_t >
std::chrono::system_clock::time_point next_time_aligned_on(const std::chrono::system_clock::time_point & tp, const duration_t & step)
{
    const std::chrono::system_clock::duration d = tp.time_since_epoch();
    const auto step2 = std::chrono::duration_cast<std::chrono::system_clock::duration>(step);

    const auto elapsed_since_last = d % step2;

    return tp - elapsed_since_last + step;      
} 

int main() {
    auto now = std::chrono::system_clock::now();
	std::chrono::seconds step(123);
	next_time_aligned_on(now, step);
	return 0;
}