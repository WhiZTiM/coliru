#include <chrono>
#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <type_traits>

template <typename Func, typename... Args>
auto waitFor(int milliseconds, Func &&func, Args&&... args)
{
	auto future = std::async(std::launch::async, std::forward<Func>(func), std::forward<Args>(args)...);
	auto status = future.wait_for(std::chrono::milliseconds(milliseconds));

	if (status == std::future_status::ready)
		return future.get();

	throw std::runtime_error{"timeout occured"};
}

int main()
{
	using namespace std::chrono_literals;

	try {
		waitFor(3000, [] () -> int {
			std::this_thread::sleep_for(5s);

			return 123;
		});
	} catch (const std::exception &ex) {
		std::cerr << ex.what() << std::endl;
	}

	return 0;
}