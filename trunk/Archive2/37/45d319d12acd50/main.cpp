#include <iostream>
#include <chrono>
#include <random>

template <bool Bound=false, typename F>
auto test(F f) {
    using clock = std::chrono::high_resolution_clock;
	auto best = clock::duration::max();
	u128 res;
	for (int outer = 1; outer < OUTER; ++outer) {

		std::mt19937_64 engine(45678456);
		res=engine();

		auto now = clock::now();
		res += f(-1, -1, -1); // Test for extreme values
		for (int inner = 1; inner < INNER; ++inner) {
			u128 arr[3];
			for (auto& a : arr)
				a = engine() + (u128(engine()) << 64);

			if (Bound) {
				arr[0] %= arr[2];
				arr[1] %= arr[2];
			}

			res += f(arr[0], arr[1], arr[2]);
		}
		auto time = clock::now()-now;

		if (time < best) {
			best = time;
			outer = 1;
		}
	}
	std::cout << std::right << "Checksum: " << std::hex << std::uppercase << res << "! Time: " << std::dec << best.count();
	return best.count();
}