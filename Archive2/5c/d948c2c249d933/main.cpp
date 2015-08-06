#include <iostream>
#include <functional>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>

#if 1

namespace experimental {
    /* std::experimental::apply */
	namespace detail {
		template <class F, class Tuple, std::size_t... I>
		constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>) {
			return __invoke(std::forward<F>(f), std::get<I>(std::forward<Tuple>(t))...);
		}
	}

	template <class F, class Tuple>
	constexpr decltype(auto) apply(F&& f, Tuple&& t) {
		return detail::apply_impl(std::forward<F>(f), std::forward<Tuple>(t), std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{});
	}
}
/* std::experimental::apply */
#endif

template<typename Signature>
struct event;

template<typename R, typename... Args>
struct event<R(Args...)> {
	using Signature = R(Args...);

	using callable_t = std::function<Signature>;

	std::vector<callable_t> callbacks;
	std::mutex              mutex;

	template<typename F>
	void register_callback(F callable) {
		std::lock_guard<std::mutex> lock(mutex);
		callbacks.push_back( [fun = callable] (Args... args) { return fun(args...); });
	}

	void signal(Args... args) {
		std::lock_guard<std::mutex> lock(mutex);
		for (auto&& callback : callbacks) callback(args...);
	}
};

template<typename Signature>
struct deferred_event;

template<typename R, typename... Args>
struct deferred_event<R(Args...)> : public event<R(Args...)> {

	using base = event<R(Args...)>;
	

	using args_t = std::tuple<Args...>;
	std::vector<args_t>     args;
	std::mutex              args_mutex;

	void signal(Args... arguments) {
		args.emplace_back(arguments...);
	}

	void deliver_deferred() {
		std::vector<args_t> args_temp;
		{
			std::lock_guard<std::mutex> lock_args(args_mutex);
			std::exchange(args, args_temp);
		}

		std::lock_guard<std::mutex> lock(base::mutex);
		for (auto&& callback : base::callbacks) 
			for (auto&& args : args_temp)
				experimental::apply(callback, args);
	}

};



int main()
{
	deferred_event<void(char)> input;

	input.register_callback(
		[](char c) {
			std::cout << "got char '" << c << "'\n";
		}
	);

	std::thread application{
		[&] {
			int c = 0;
			do {
				c = std::getchar();
				input.signal(static_cast<char>(c));
			} while (c != EOF);
		}
	};


    input.deliver_deferred();
	application.join();


}