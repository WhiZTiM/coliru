#include <iostream>
#include <random>
#include <array>
#include <algorithm>

using namespace std;

template <typename T>
static inline constexpr signed char signum(T k)
{
    return 1 + (k < 0 ? -2 : !!k - 1);
}

int main() {

	struct {
		signed char operator () (int a, int b) { return signum(a - b) == -1; }
	} f;
	
	std::array<int, 10> a;
    std::random_device rd;
    std::mt19937 gen {rd()};
    std::uniform_int_distribution<> dis {1, 1000};
    
    for (decltype(a)::size_type i = 0; i < 10; ++i)
        a[i] = dis(gen);
    
    for (auto k : a)
        cout << k << endl;
        
    cout << "\nSorted\n======\n" << endl;
    
    std::sort(a.begin(), a.end(), f);
    
    for (auto k : a)
        cout << k << endl;

	return 0;
}