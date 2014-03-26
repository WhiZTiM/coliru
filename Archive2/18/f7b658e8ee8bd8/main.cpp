#include <chrono>
#include <thread>
#include <iostream>

template<typename timer_T = std::chrono::steady_clock>
class my_timer {
public:

    using timer_type = timer_T;
	using time_point = std::chrono::time_point<my_timer, typename timer_T::time_point::duration >;
	using duration   = typename timer_T::duration;
	using rep		 = typename duration::rep;
	using period	 = typename duration::period;

	static const bool is_steady = timer_T::is_steady;

	static time_point now() {
		return time_point(timer_T::now() - epoch_);
	}

private:
	static typename timer_T::time_point epoch_;
};

template<typename T>
typename T::time_point my_timer<T>::epoch_ = T::now();


int main(int, char*[]) {
    for(int i=0; i<5; i++) {
        std::cout << my_timer<>::now().time_since_epoch().count() << "\n";
        std::this_thread::sleep_until( my_timer<>::now() + std::chrono::seconds(3) );
    }
}