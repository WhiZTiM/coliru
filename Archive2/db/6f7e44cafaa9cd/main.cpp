#include <iostream>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <atomic>
#include <chrono>
#include <numeric>

std::atomic_bool thread_switch;
std::mutex mutex;
std::unordered_map<std::thread::id, int> results;

void fight_for_mutex() {
    auto this_id = std::this_thread::get_id();
	while(!thread_switch) {} // wait until thread_switch is flipped
	while(thread_switch) {
		mutex.lock();
		++results[this_id];
		mutex.unlock();
	}
}

int main(int argc, char const *argv[]) {
	if(argc < 2) {
		std::cout << "error: no argument provided" << std::endl;
		std::cout << "\targument: number of threads to use" << std::endl;
	} else {
		std::cout << "using " << std::atoi(argv[1]) << " threads…" << std::endl;
		thread_switch = false;
		std::vector<std::thread> threads;
		for(int i = 0; i < std::atoi(argv[1]); ++i) {
			threads.emplace_back(fight_for_mutex);
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
		thread_switch = true;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		thread_switch = false;
		for(auto& thread : threads) {
			thread.join();
		}
		auto mutex_sum = std::accumulate(results.begin(), results.end(), 0,
			                             [] (int a, const std::pair<std::thread::id, int>& b) {return a + b.second;});
		std::cout << "mutex sum: " << mutex_sum << std::endl;
		std::cout << "thread id | percentage | mutex count" << std::endl << std::endl;
		for(auto& pair : results) {
			std::cout << pair.first << " | " << std::to_string(static_cast<float>(pair.second) / mutex_sum * 100.0f).substr(0, 5) << "% | " << std::to_string(pair.second) << std::endl;
		}
	}
	return 0;
}
