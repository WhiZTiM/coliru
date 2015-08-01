#include <iostream>
#include <vector>

class ref {
    int a, b;
public:
	ref(int a, int b) : a(a), b(b) {}
	size_t pos(size_t width) const { return a * width + b; }
};

class row_id {
	int row;
public:
	row_id(int row) : row(row) {}

	row_id &operator++() {
		++row; 
		return *this; 
	}
	bool operator<(int i) { return row < i; }
	ref operator,(int column) { return ref(row, column); }
};

template<class T>
class matrix {
	std::vector<T> data;
	size_t width;
public:
	matrix(size_t w, size_t h) : data(w*h), width(w) {}
	T &operator[](ref const &r) { return data[r.pos(width)]; }
};

int main() { 
	matrix<int> m(2, 2);

	row_id i(0);
	int j = 0;

	m[i, j] = 3;
	m[++i, ++j] = 2;

	for (row_id i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j)
			std::cout << m[i, j] << "\t";
		std::cout << "\n";
	}
}
