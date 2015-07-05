#include <vector>
#include <iostream>
#include <string>
#include <sstream>


int parent(int i) {
    return i/2;
}

int left(int i) {
	return 2*i;
}

int right(int i) {
	return 2*i+1;
}

template<typename T>
void heapify(std::vector<T>& A, int i, int heap_size) {
	typename std::vector<T>::size_type l = left(i);
	typename std::vector<T>::size_type r = right(i);
	typename std::vector<T>::size_type largest;
	if (l <= heap_size && A.at(l) > A.at(r)) {
		largest = l;
	}
	else {
		largest = i;
	}
	if (r <= heap_size && A.at(r) > A.at(largest)) {
		largest = r;
	}
	if (largest != i) {
		std::swap(A.at(i), A.at(largest));
		heapify(A, largest, heap_size);
	}
}

template<typename T>
void build_heap(std::vector<T>& A) {
	int heap_size = (A.size() - 1);
	for(int i = ((A.size() - 1) / 2); i >= 1; i--) {
		heapify(A, i, heap_size);
	}
}

template<typename T>
void heapsort(std::vector<T>& A) {
	int heap_size = (A.size() - 1);
	build_heap(A);
	for(int i = (A.size() - 1); i >= 2; i--) {
		std::swap(A[1], A[i]);
		heap_size--;
		heapify(A, 1, heap_size);
	}
}

int main() {
	std::cout << "Heapsort. Type in numbers to sort, separated by spaces." << std::endl;
	std::vector<int> v;
	std::string s;
	std::getline(std::cin, s);
	std::istringstream iss(s);
	int t = 0;
	while (iss >> t) {v.push_back(t);}
	heapsort(v);
	for (std::vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter) {
		std::cout << *iter << ' ';
	}
	std::cout << std::endl;
}
