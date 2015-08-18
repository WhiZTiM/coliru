#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <limits>
#include <numeric>
using namespace std;

int main(void) {
    ofstream foo("foo.txt", ios::binary);
	vector<int> bar(numeric_limits<unsigned char>::max() + 1);

	iota(bar.begin(), bar.end(), 0);

	copy(reinterpret_cast<const char*>(&*bar.cbegin()), reinterpret_cast<const char*>(&*bar.cbegin() + bar.size()), ostream_iterator<char>(foo));
	foo.close();

	ifstream file_read("foo.txt", ios::binary);
	vector<decltype(bar)::value_type> output(bar.size());

	for (unsigned int i = 0U; i < output.size() && file_read; ++i) {
		file_read.read(reinterpret_cast<char*>(&output[i]), sizeof(decltype(output)::value_type));
	}

	cout << "First element: " << output.front() << "\nLast element: " << output.back() << "\nAny non-consecutive elements: " << (output.cend() == mismatch(output.cbegin(), prev(output.cend()), next(output.cbegin()), [](auto first1, auto first2) { return first1 + 1 == first2; }).second ? "no\n" : "yes\n");

	return 0;
}