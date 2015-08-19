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

	copy(reinterpret_cast<const char*>(&*bar.data()), reinterpret_cast<const char*>(&*bar.data() + bar.size()), ostreambuf_iterator<char>(foo));
	foo.close();

	ifstream file_read("foo.txt", ios::binary);
	vector<decltype(bar)::value_type> output(bar.size());

	copy(istreambuf_iterator<char>(file_read), istreambuf_iterator<char>(), reinterpret_cast<char*>(&*output.data()));

	cout << "First element: " << output.front() << "\nLast element: " << output.back() << "\nAny non-consecutive elements: " << (output.cend() == mismatch(output.cbegin(), prev(output.cend()), next(output.cbegin()), [](auto first1, auto first2) { return first1 + 1 == first2; }).second ? "no\n" : "yes\n");

	return 0;
}