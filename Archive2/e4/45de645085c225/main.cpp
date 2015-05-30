#include <iostream>
 
template<int N>
struct flag {
  friend constexpr int adl_flag (flag<N>);
};

template<int N>
struct writer {
  friend constexpr int adl_flag (flag<N>) {
    return N;
  }

  static constexpr int value = N;
};
 
template<int N, int = adl_flag (flag<N> {})>
int constexpr reader (int, flag<N>) {
  return N;
}

template<int N>
int constexpr reader (float, flag<N>, int R = reader (0, flag<N-1> {})) {
  return R;
}

int constexpr reader (float, flag<0>) {
  return 0;
}

template<int N = 1>
int constexpr next (int R = writer<reader (0, flag<32> {}) + N>::value) {
  return R;
}

int main() {
	constexpr int value1 = next();
	constexpr int value2 = next();
	constexpr int value3 = next();
	std::cout << value1 << " " << value2 << " " << value3;
	return 0;
}