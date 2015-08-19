#include <functional>
#include <iostream>
#include <memory>

template<typename T>
struct id {
    using type = T;
};

template<typename T>
auto clone(const std::unique_ptr<T> &p) -> std::unique_ptr<T> {
    return p
        ? std::make_unique<T>(*p)
        : nullptr;
}

template<typename>
struct Maybe;

template<typename T>
auto operator>>=(Maybe<T>, typename id<std::function<auto(T) -> Maybe<T>>>::type) -> Maybe<T>;

template<typename T>
auto Just(T) -> Maybe<T>;

template<typename T>
auto Nothing() -> Maybe<T>;

template<typename T>
struct Maybe {
    friend auto Just<>(T) -> Maybe;
	friend auto Nothing<>() -> Maybe;
	friend auto operator>>=<>(Maybe, typename id<std::function<auto(T) -> Maybe<T>>>::type) -> Maybe;
    
    Maybe(const Maybe<T> &other) : data_{clone(other.data_)} {}
    Maybe &operator=(const Maybe<T> &other) {data_ = clone(other.data_); return *this;}

	auto print() const -> void {
		if (isNothing()) {
			std::cout << "Nothing";
		} else if (isJust()) {
			std::cout << "Just " << *data_;
		} else {
			throw;
		}
	}

private:
	std::unique_ptr<T> data_;

	Maybe() : data_{} {}
	Maybe(T t) : data_{std::make_unique<T>(t)} {}

	auto isNothing() const -> bool {return !data_;}
	auto isJust() const -> bool {return !isNothing();}
};

template<typename T>
auto Just(T t) -> Maybe<T> {
	return {t};
}

template<typename T>
auto Nothing() -> Maybe<T> {
	return {};
}

template<typename T>
auto return_(T t) -> Maybe<T> {
	return Just(t);
}

template<typename T>
auto operator>>=(Maybe<T> m, typename id<std::function<auto(T) -> Maybe<T>>>::type f) -> Maybe<T> {
	return m.isNothing() 
		? Nothing<T>()
		: m.isJust() 
			? f(*m.data_)
			: throw;
}

template<typename T>
auto add(Maybe<T> mx, Maybe<T> my) -> Maybe<T> {
	return mx >>= [my](T x) {
		return my >>= [x](T y) {
			return return_(x + y);
		};
	};
}

int main() {
	Maybe<int> m1 = Just(2);
	Maybe<int> m2 = Just(5);

	Maybe<int> mres = add(m1, m2);
	std::cout << "add(Just 2, Just 5) = ";
	mres.print();
	std::cout << '\n';

	m1 = Nothing<int>();
	mres = add(m1, m2);
	std::cout << "add(Nothing, Just 5) = ";
	mres.print();
	std::cout << '\n';
}