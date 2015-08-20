// method-based FSA implementation
// (C) eugene@hutorny.in.ua
#include <iostream>

template<class C, typename T>
struct fsa {
    struct state_t {
		typedef state_t (C::*type)(T);
		inline state_t(type f) : state(f) {}
		type state;
	};

	fsa(state_t init) : state(init) {}

	inline bool next(T val) {
		state = (static_cast<C*>(this)->*state.state)(val);
		return state.state != nullptr;
	}
private:
	state_t state;
};

struct myfsa : fsa<myfsa,char> {
    inline myfsa() : fsa<myfsa, char>(&myfsa::start) {}
	state_t start(char) {
		std::cout << "start" << std::endl;
		return &myfsa::state1;
	}
	state_t state1(char) {
		std::cout << "state1" << std::endl;
		return &myfsa::state2;
	}
	state_t state2(char) {
		std::cout << "state2" << std::endl;
		return nullptr;
	}
	char get() { return ' '; }
	void run() {
		while(next(get()));
	}
};

int main(int, char**) {
    myfsa fsa;
	fsa.run();
	return 0;
}
